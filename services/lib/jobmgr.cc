/**
 * File : jobmgr.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of the parallel object JobMgr (POP-C++ Global Services)
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 * clementval   2010/04/19  All code added for the semester project begins with this comment //Added by clementval, ends
 *with //End of add
 * clementval   2010/04/19  All code modified during the semester project begins with //Modified by clementval, ends
 *with //End of modification
 * clementval  2010/04/29   Functionnal version with the new parclass POPCSearchNode that is in charge of the ressource
 *discovery
 * clementval   2010/05/02  Better distribution of parallel object on discovered ressources
 * Wyssen      2010/08/04  Modified code that it works with virtual machines. If virtual mode is activated, the objects
 *will run in
 *                         a virtual machine and not on the machine where this JobMgr runs.
 *                         All modified code is marked with
 *                         Begining -> ### Added by Wyssen ###
 *                         Ending   -> ### End ###
 * clementval  2010/11/04  Read ESX variables from the jobmgr.conf file.
 * clementval  2010/11/08  Add the POPAppID in the resource discovery and in the reservation
 */

#include "popc_intface.h"

#include <numeric>
#include <list>
#include <cstring>
#include <algorithm>
#include <mutex>
#include <vector>

#include "codemgr.ph"
#include "timer.h"
#include "jobmgr.ph"
#include "pop_thread.h"

/**
 * ViSaG : clementval
 * Added vor ViSaG
 */
#include "appservice.ph"

#define min(a, b) ((a) < (b) ? (a) : (b))

class paroc_timerthread : public pop_thread {
public:
    paroc_timerthread(int parent_update, int service_timeout, IMPLEMENT_TYPE(JobMgr) * myjobmgr);
    virtual void start();

private:
    int parent_update;
    int service_timeout;
    IMPLEMENT_TYPE(JobMgr) * jobmgr;
};

paroc_timerthread::paroc_timerthread(int myparent_update, int myservice_timeout, IMPLEMENT_TYPE(JobMgr) * myjobmgr)
    : pop_thread(true) {
    parent_update = myparent_update;
    service_timeout = myservice_timeout;
    jobmgr = myjobmgr;
}

void paroc_timerthread::start() {
    if ((parent_update <= 0 && service_timeout <= 0) || jobmgr == nullptr) {
        return;
    }
    while (1) {
        int nextwakeup;
        bool updateaction;

        if (service_timeout <= 0 || parent_update < service_timeout) {
            updateaction = true;
            nextwakeup = parent_update;
            if (service_timeout > parent_update) {
                service_timeout -= parent_update;
            }
        } else {
            updateaction = false;
            nextwakeup = service_timeout;
        }

        while ((nextwakeup = popc_sleep(nextwakeup)) > 0)
            ;
        if (updateaction) {
            jobmgr->SelfRegister();
        } else {
            popc__exit(1);
        }
    }
}

// CLASS NEIGHBOR NODE: IMPLEMENT THREAD-SAFE NEIGHBOR NODE ACCESS BASED ON KEYS
NodeInfoMap::NodeInfoMap() {
    // keycount=0;
}

std::vector<std::string> NodeInfoMap::GetContacts() {
    std::vector<std::string> contacts;

    std::vector<double> h;

    std::unique_lock<pop_mutex> lock(maplock);

    for (auto& t : hashmap) {
        double heuristic = t.second.heuristic;

        auto hpos = h.begin();
        auto cpos = contacts.begin();
        while (hpos != h.end()) {
            auto old = hpos;
            auto& tmp = *hpos++;

            if (tmp >= heuristic) {
                contacts.insert(cpos, std::string(t.first));
                h.insert(old, heuristic);
                break;
            }

            ++cpos;
        }

        if (cpos == contacts.end()) {
            contacts.push_back(std::string(t.first));
            h.push_back(heuristic);
        }
    }

    return contacts;
}

bool NodeInfoMap::HasContact(const std::string& contact) {
    std::unique_lock<pop_mutex> lock(maplock);

    for (auto& v : hashmap) {
        if (pop_utils::SameContact(std::string(v.first), contact)) {
            return true;
        }
    }

    return false;
}

bool NodeInfoMap::GetInfo(const std::string& contact, NodeInfo& info) {
    std::unique_lock<pop_mutex> lock(maplock);

    if (hashmap.count(contact)) {
        info = hashmap[contact.c_str()];
        return true;
    } else {
        return false;
    }
}

int NodeInfoMap::GetCount() {
    std::unique_lock<pop_mutex> lock(maplock);
    return hashmap.size();
}

bool NodeInfoMap::Update(const std::string& contact, NodeInfo& info) {
    std::unique_lock<pop_mutex> lock(maplock);

    if (hashmap.count(contact)) {
        hashmap[contact.c_str()] = info;
        return true;
    }

    return false;
}

bool NodeInfoMap::Remove(const std::string& contact) {
    std::unique_lock<pop_mutex> lock(maplock);
    auto erased = hashmap.erase(contact);
    return erased > 0;
}

bool NodeInfoMap::Add(const std::string& contact, NodeInfo& info) {
    std::unique_lock<pop_mutex> lock(maplock);

    if (!hashmap.count(contact)) {
        hashmap[contact.c_str()] = info;
        return true;
    }

    return false;
}

//*********************    JobMgr implementation    *********************

/**
 * JobMgr constructor
 * @param daemon     If true, the parallel object will run as a daemon
 * @param conf       Path of the jobmgr configuration file
 * @param challenge  Challenge string used to stop the service
 * @param url
 * @param nodeAccess Access Point of the PSN
 * @param localPSM   Access Point of the PSM
 */
JobMgr::JobMgr(bool daemon, const std::string& conf, const std::string& challenge, const std::string& url,
               const pop_accesspoint& nodeAccess, const pop_accesspoint& localPSM)
    : JobCoreService(challenge) {
    // Added by clementval
    // Save the POPCSearchNode's access point for future communication
    _localPSN = nodeAccess;
    // Create interface to communicate with the local POPCSearchNode
    POPCSearchNode psn(_localPSN);
    // Set a reference of this JobMgr to the POPCSearchNode
    psn.setJobMgrRef(GetAccessPoint());
    _localPSM = localPSM;
    // End of add

    counter = 1;
    requestCounter = 1;
    modelearn = true;
#ifndef __WIN32__
    popc_signal(popc_SIGCHLD, popc_SIG_IGN);
#endif
    // Find service ID (pairs IP-port for tracing

    std::vector<std::string> acc;
    popc_tokenize(acc, GetAccessPoint().GetAccessString(), ":");

    unsigned int seed = time(nullptr);

    int ret = pop_system::GetIP(serviceID, 1);
    if (ret != 1) {
        LOG_ERROR("[JM] Can't find IP address");
        serviceID[0] = rand_r(&seed);
    }

    if (sscanf(acc.at(1).c_str(), "%d", serviceID + 1) != 1) {
        serviceID[1] = rand_r(&seed);
    }

    LOG_DEBUG("MyID=%d:%d", serviceID[0], serviceID[1]);

    LOG_DEBUG_IF(ret <= 0, "[JM] Can not find IP address of %s for resource discovery tracking",
                 GetAccessPoint().GetAccessString().c_str());

    int service_timeout = 0;
    int parent_timeout = SELFREGISTER_TIMEOUT;  // default: one-day long in seconds

    localuid = -1;
    service_timer.Start();

    reserve_timeout = RESERVE_TIMEOUT;
    alloc_timeout = ALLOC_TIMEOUT;

    // Start deamon....redirect stdin/out/err to file...

    //  close(0);
    //  close(1);
    //  close(2);
    //  int fd0=popc_open("/dev/null",O_RDONLY);
    //  int fd1=popc_open("/tmp/JobMgr.stdout",O_WRONLY | O_CREAT,S_IRWXU);
    //  int fd2=popc_open("/tmp/JobMgr.stderr",O_WRONLY | O_CREAT,S_IRWXU);
    //  assert(fd0==0 && fd1==1 && fd2==2);

    FILE* f = fopen(conf.c_str(), "rt");
    char val[256];
    if (f == nullptr) {
        LOG_WARNING("Open config file [%s] fail", conf.c_str());
        pop_exception::pop_throw(errno, conf.c_str());
    }

    maxjobs = 100;

    maxdynamicnodes = 0;
    dynamicnodes = 0;

    LOG_INFO("[JM] Loading information from %s", conf.c_str());

    char str[1024];

    const char* mycontact = GetAccessPoint().GetAccessString().c_str();
    LOG_DEBUG("[JM] jobmgr access string %s", mycontact);
    while (!feof(f)) {
        if (fgets(str, 1023, f) == nullptr) {
            break;
        }

        char* name = str;
        while (isspace(*name)) {
            name++;
        }
        if (*name == 0 || *name == '#') {
            continue;
        }

        char* val = name;
        while ((!isspace(*val)) && *val != 0) {
            *val = tolower(*val);
            val++;
        }
        if (*val == 0) {
            continue;
        }
        *val = 0;
        val++;
        while (isspace(*val)) {
            val++;
        }
        if (*val == 0) {
            continue;
        }
        char* tmp = val + strlen(val) - 1;
        while (isspace(*tmp)) {
            tmp--;
        }
        tmp[1] = 0;
        if (pop_utils::isEqual(name, "node")) {
            if (strchr(val, ':') == nullptr) {
                strcat(val, ":");
                strcat(val, DEFAULT_PORT);
            }
            if (pop_utils::SameContact(mycontact, val)) {
                continue;
            }
            NodeInfo tmp;
            std::string contact(val);
            tmp.nodetype = NODE_STATIC;
            tmp.stoptime = -1;
            tmp.heuristic = 0;

            neighbors.Add(contact, tmp);
        } else if (pop_utils::isEqual(name, "parent")) {
            if (strchr(val, ':') == nullptr) {
                strcat(val, ":");
                strcat(val, DEFAULT_PORT);
            }
            if (pop_utils::SameContact(mycontact, val)) {
                continue;
            }
            pop_accesspoint t;
            t.SetAccessString(val);
            LOG_DEBUG("add parent %s", val);
            parents.push_back(t);
        } else if (pop_utils::isEqual(name, "maxjobs")) {
            if (sscanf(val, "%d", &maxjobs) != 1 || maxjobs < 0) {
                maxjobs = 100;
            }
        } else if (pop_utils::isEqual(name, "timeout")) {
            if (sscanf(val, "%d", &service_timeout) == 1 && service_timeout > 0) {
                LOG_DEBUG("[JM] JobMgr Timeout: %ds", service_timeout);

            } else {
                service_timeout = 0;
            }
        } else if (pop_utils::isEqual(name, "checkpoint")) {
            if (sscanf(val, "%d", &parent_timeout) == 1 && parent_timeout > 0) {
                LOG_DEBUG("[JM] Checkpoint every: %d seconds", parent_timeout);
            } else {
                parent_timeout = 0;
            }
        } else if (pop_utils::isEqual(name, "exec_timeout")) {
            if (sscanf(val, "%d", &alloc_timeout) != 1 || alloc_timeout < 0) {
                alloc_timeout = ALLOC_TIMEOUT;
            }
        } else if (pop_utils::isEqual(name, "reserve_timeout")) {
            if (sscanf(val, "%d", &reserve_timeout) != 1 || reserve_timeout < 0) {
                reserve_timeout = RESERVE_TIMEOUT;
            }
        } else if (pop_utils::isEqual(name, "platform")) {
            pop_system::platform = val;
        } else {
            info.push_back({name, val});
        }
    }
    fclose(f);

    SelfRegister();
    std::string tmpstr;

    if (Query("power", tmpstr)) {
        total.flops = atof(tmpstr.c_str());
    } else {
        // We do benchmark now to find the computing power of the machine...
        total.flops = pop_utils::benchmark_power();
        snprintf(val, sizeof(val), "%g", total.flops);
        info.push_back({"power", val});
    }

    if (Query("ram", tmpstr)) {
        total.mem = atoi(tmpstr.c_str());
    }
    if (Query("bandwidth", tmpstr)) {
        total.bandwidth = atoi(tmpstr.c_str());
    }

    // Note(BW): This seems like a bad idea since Resources contains
    // a class with a vtable (pop_accesspoint)
    memcpy(static_cast<void*>(&limit), static_cast<void*>(&total), sizeof(Resources));

    if (Query("np", tmpstr)) {
        int n = atoi(tmpstr.c_str());
        if (n > 0) {
            total.flops *= n;
        }
    }

    if (Query("degree", tmpstr)) {
        if (sscanf(tmpstr.c_str(), "%d", &maxdynamicnodes) != 1 || maxdynamicnodes < 0) {
            maxdynamicnodes = 0;
        }
    }

    if (Query("learn", tmpstr)) {
        if (popc_strcasecmp(tmpstr.c_str(), "false") == 0) {
            modelearn = false;
        }
    }

    if (Query("localuser", tmpstr)) {
#ifndef __WIN32__
        passwd* t = popc_getpwnam(tmpstr.c_str());
        if (t != nullptr) {
            localuid = t->pw_uid;
        }
        LOG_INFO("localuid=%d", localuid);
#endif
    }

    // Note(BW): This seems like a bad idea since Resources contains
    // a class with a vtable (pop_accesspoint)
    memcpy(static_cast<void*>(&available), static_cast<void*>(&total), sizeof(Resources));

    LOG_DEBUG("[JM] Total resource power=%g, max per job=%g", total.flops, limit.flops);

    // Added by clementval

    // Setting POPCSearchNode informations. Thoses informations are known by the JobMgr
    LOG_DEBUG("[JM] Setting the Node info for JobMgr");

    // Setting the POPCSearchNode ID (its access point)
    psn.setPOPCSearchNodeId(_localPSN.GetAccessString());
    LOG_DEBUG("[JM] Node ID : %s", psn.getPOPCSearchNodeId().c_str());

    // Setting the current operating system (The one of the JobMgr's machine)
    psn.setOperatingSystem(pop_system::platform);
    LOG_DEBUG("[JM] Node opertating system : %s", psn.getOperatingSystem().c_str());

    // Setting the total computing power of this JobMgr
    psn.setPower(total.flops);
    LOG_DEBUG("[JM] Node power : %f", psn.getPower());

    // Setting the total RAM of this JobMgr
    psn.setMemorySize(total.mem);
    LOG_DEBUG("[JM] Node memory size : %d", psn.getMemorySize());

    // Setting the total network bandwith of this JobMgr
    psn.setNetworkBandwidth(total.bandwidth);
    LOG_DEBUG("[JM] Node bandwidth : %f", psn.getNetworkBandwidth());

    psn.setMaxJobs(maxjobs);
    LOG_DEBUG("[JM] Node max jobs : %d", psn.getMaxJobs());
    // End of add

    // Check and set environment variables....
    if (Query("env", tmpstr)) {
        std::vector<std::string> tokens;
        popc_tokenize(tokens, tmpstr, "()");
        char var[1024], val[1024], str[1024];
        for (auto tok : tokens) {
            if (sscanf(tok.c_str(), "%s %s", var, val) != 2) {
                LOG_ERROR("[JM] can not parse the environment variable string [%s]", tok.c_str());
            } else {
                snprintf(str, sizeof(str), "%s=%s", var, val);
                putenv(popc_strdup(str));
            }
        }
    }

    if (daemon) {
        Start();
    }

    if (parent_timeout > 0 || service_timeout > 0) {
        paroc_timerthread* timeinfo = new paroc_timerthread(parent_timeout, service_timeout, this);
        timeinfo->create();
    }
}

JobMgr::~JobMgr() {
    // Added by clementval

    // Delete neighbors references
    POPCSearchNode psn(_localPSN);
    psn.deleteNeighbors();

    // End
    dump();
}

// Added by clementval

// Return the local POPCSearchNode Access Point
pop_accesspoint JobMgr::GetNodeAccessPoint() {
    return _localPSN;
}

// End of add

// Other service methods....

void JobMgr::RegisterNode(const pop_accesspoint& url) {
    LOG_DEBUG("Register node %s", url.GetAccessString().c_str());
    pop_accesspoint tmp(url);
    tmp.SetAsService();
    // Create a POPCSearchNode interface to communicate with the remote POPCSearchNode
    POPCSearchNode remoteNode(tmp);

    // Create a POPCSearchNode interface to communicate with the local POPCSearchNode
    POPCSearchNode localPSN(_localPSN);

    // Communicate with the local POPCSearchNode to add the remote POPCSearchNode as a direct neighbor
    localPSN.addNeighbor(remoteNode);
}

//  Added by clementval, This method is used to unregister a node temporarily
void JobMgr::UnregisterNode(const pop_accesspoint& url) {
    pop_accesspoint tmp(url);
    tmp.SetAsService();
    // Create a POPCSearchNode interface to communicate with the remote POPCSearchNode
    POPCSearchNode remoteNode(tmp);

    // Create a POPCSearchNode interface to communicate with the local POPCSearchNode
    POPCSearchNode psn(_localPSN);

    // Communicate with the local POPCSearchNode to remove the remote POPCSearchNode from the neighbor's list
    psn.removeNeighbor(remoteNode);
}
// End of add

int JobMgr::Query(const std::string& type, std::string& val) {
    char tmp[1024];
    if (type == "platform") {
        val = pop_system::platform;
        return 1;
    }
    if (type == "host") {
        val = pop_system::GetHost();
        return 1;
    }
    if (type == "jobs") {
        Update();
        mutex {
            snprintf(tmp, sizeof(tmp), "%zu/%d", jobs.size(), maxjobs);
            val = tmp;
        }
        return 1;
    }
    if (type == "joblist") {
        Update();
        val = "";

        mutex {
            for (auto& r : jobs) {
                if (r.contact.IsEmpty() || r.appservice.IsEmpty()) {
                    continue;
                }

                snprintf(tmp, sizeof(tmp), "APP=%s/JOB=%s\n", r.appservice.GetAccessString().c_str(),
                         r.contact.GetAccessString().c_str());
                val += tmp;
            }
        }
        return 1;
    }

    if (type == "pausejobs") {
        Update();
        mutex {
            snprintf(tmp, sizeof(tmp), "%zu", pause_apps.size());
            val = tmp;
        }
        return 1;
    }

    if (type == "power_available") {
        Update();
        snprintf(tmp, sizeof(tmp), "%g/%g", available.flops, total.flops);
        val = tmp;
        return 1;
    }

    if (type == "neighbors") {
        snprintf(tmp, sizeof(tmp), "%u", neighbors.GetCount());
        val = tmp;
        return 1;
    }


    for (auto& t : info) {
        if (type == t.name) {
            val = t.val;
            return 1;
        }
    }
    return 0;
}

int JobMgr::CreateObject(pop_accesspoint& localservice, const std::string& objname, const pop_od& od, int howmany,
                         pop_accesspoint* objcontacts, int howmany2, pop_accesspoint* remotejobcontacts) {
    if (howmany <= 0) {
        return 0;
    }
    int count = 0;
    int ret = 0;
    int retry = 3;
    try {
        int traceip[MAX_HOPS];
        std::vector<pop_accesspoint> jobcontacts(howmany);
        std::vector<int> reserveIDs(howmany);
        std::vector<float> fitness(howmany);

        int requestInfo[3];

        while (count < howmany && retry > 0) {
            memcpy(requestInfo, serviceID, 2 * sizeof(int));
            mutex {
                requestInfo[2] = requestCounter;
                requestCounter++;
            }

            for (int i = 0; i < howmany; i++) {
                fitness[i] = 0;
                jobcontacts[i].SetAccessString("");
            }

            if (!AllocResource(localservice, objname, od, howmany - count, fitness.data() + count,
                               jobcontacts.data() + count, reserveIDs.data() + count, requestInfo, traceip, 0)) {
                LOG_DEBUG("[JM] AllocResource failed");
                ret = OBJECT_NO_RESOURCE;
                break;
            }
            bool nocancel = true;
            for (int i = count; i < howmany; i++)
                if (fitness[i] <= 0) {
                    LOG_DEBUG("[JM] fitness is below zero");
                    nocancel = false;
                    break;
                }
            if (!nocancel) {
                // Cancel reservations...
                for (int i = count; i < howmany; i++)
                    if (!jobcontacts[i].IsEmpty() && fitness[i] > 0) {
                        try {
                            pop_accesspoint ac(jobcontacts[i]);
                            std::string acstr(ac.GetAccessString());
                            JobMgr jobmgr(ac);

                            jobmgr.CancelReservation(reserveIDs.data() + i, 1);
                            for (int j = i + 1; j < howmany; j++)
                                if (fitness[j] > 0 && acstr == jobcontacts[j].GetAccessString()) {
                                    jobcontacts[j].SetAccessString("");
                                    fitness[j] = 0;
                                    jobmgr.CancelReservation(reserveIDs.data() + j, 1);
                                }
                        } catch (std::exception& e) {
                            LOG_WARNING("Exception while canceling reservations: %s", e.what());
                        }
                    }
                ret = OBJECT_NO_RESOURCE;
                break;
            }
            // Now we will call ExecObj...
            std::vector<int> tmpids(howmany);
            int sz;

            for (int i = count; i < howmany; i++) {
                if (!jobcontacts[i].IsEmpty()) {
                    try {
                        pop_accesspoint ac(jobcontacts[i]);
                        std::string acstr(ac.GetAccessString());
                        JobMgr jobmgr(ac);
                        sz = 0;
                        tmpids[sz++] = reserveIDs[i];
                        for (int j = i + 1; j < howmany; j++)
                            if (acstr == jobcontacts[j].GetAccessString()) {
                                jobcontacts[j].SetAccessString("");
                                tmpids[sz++] = reserveIDs[j];
                            }
                        *(remotejobcontacts + count) = jobcontacts[i];
                        int execRet = jobmgr.ExecObj(objname, od, sz, tmpids.data(), localservice, objcontacts + count);
                        if (execRet != 0) {
                            // Added by clementval
                            LOG_ERROR("[JM] EXEC_FAILED");
                            // End of add
                            jobmgr.CancelReservation(tmpids.data(), sz);
                        } else {
                            count += sz;
                        }
                    } catch (std::exception& e) {
                        LOG_ERROR("[JM] Exception caught in ExecObj: %s", e.what());
                    }
                }
            }

            retry--;

        }  // End While

    }  // End try

    catch (std::exception& e) {
        LOG_WARNING("Exception in JogMgr::CreateObject: %s", e.what());
        Pause(localservice, SLEEP_TIME_ON_ERROR);
        ret = POP_JOBSERVICE_FAIL;
    }

    LOG_INFO("Object count=%d, require=%d\n", count, howmany);
    if (count >= howmany) {
        return 0;
    }

    // Can not create all object -> kill the already allocated object
    for (int i = 0; i < count; i++) {
        try {
            pop_interface obj(objcontacts[i]);
            obj.Kill();
        } catch (std::exception& e) {
            LOG_WARNING("Exception while killing objects: %s", e.what());
        }
    }
    if (ret == 0) {
        ret = POP_EXEC_FAIL;
    }
    return ret;
}

bool JobMgr::AllocResource(const pop_accesspoint& localservice, const std::string& objname, const pop_od& od,
                           int howmany, float* fitness, pop_accesspoint* jobcontacts, int* reserveIDs,
                           int requestInfo[3], int iptrace[MAX_HOPS], int tracesize) {
    bool ret = false;
    // Added by clementval

    if (!od.isSearchSet()) {
        // End of add
        if (howmany < 1) {
            return false;
        }

        if (!AddRequest(requestInfo)) {
            LOG_DEBUG("[JM] Local resource has already been traversed!");
            return false;
        }

        std::string codefile;

        // MATCHING LOCALLY
        LOG_DEBUG("[JM] Resource discovery request: obj=%s, local service: %s (trace=%d)", objname.c_str(),
                  localservice.GetAccessString().c_str(), tracesize);
        try {
            if (CheckPauseList(localservice)) {
                LOG_DEBUG("[JM] Local resource matching is temporary paused due to previous errors!");
            } else if (MatchUser(localservice)) {
                CodeMgr codemgr(localservice);
                if (codemgr.QueryCode(objname, pop_system::platform, codefile)) {
                    if (MatchAndReserve(od, fitness, jobcontacts, reserveIDs, howmany)) {
                        ret = true;
                    }
                }
            }
        } catch (std::exception& e) {
            LOG_ERROR("[JM] Exception on resource discovery: %s", e.what());
            return false;
        }

        if (ret) {
            bool allok = true;
            for (int i = 0; i < howmany && allok; i++)
                if (fitness[i] < 1) {
                    allok = false;
                }
            if (allok) {
                return true;
            }
        }

        if (tracesize < 0 || tracesize >= MAX_HOPS) {
            LOG_DEBUG("[JM] Stop forwarding due to trace size (value=%d)", tracesize);
            return ret;
        }
        AddTrace(iptrace, tracesize);
    }

    // Added by clementval, Creation of a request to find the appropriate resources on the grid

    // Create an interface to communicate with the local POPCSearchNode
    POPCSearchNode psn(_localPSN);

    // Create the request of resource discovery
    Request r;

    // Set the request's node identifier
    r.setNodeId(psn.getPOPCSearchNodeId());

    // Recover the od Max depth or env var POPC_SEARCHMAXHOP. If both are not set, MAXHOP constant is defined in
    // JobMgr.ph
    int maxhopint = 0;
    if ((maxhopint = od.getSearchMaxDepth()) > 0) {
        r.setMaxHops(maxhopint);
    } else {
        // Recover the max Hop env variable
        char* maxhop;
        if ((maxhop = getenv("POPC_SEARCHMAXHOP"))) {
            maxhopint = atoi(maxhop);
        } else {
            maxhopint = MAXHOP;
        }
    }

    // Setting the value of max hop in the request
    r.setMaxHops(maxhopint);

    // Recover the maximum size of the request. This is not implemented yet
    int maxsizeint;
    if ((maxsizeint = od.getSearchMaxReqSize()) > 0) {
        // To be implemented
    }

    // Recover the od waiting time or env var POPC_SEARCHTIMEOUT. If both are not set, TIMEOUT constant is defined in
    // JobMgr.ph
    int timeoutint = 0;
    if ((timeoutint = od.getSearchWaitTime()) >= 0) {
    } else {
        // Recover the timeout in the POPC_SEARCHTIMEOUT env variable
        char* timeout;
        if ((timeout = getenv("POPC_SEARCHTIMEOUT"))) {
            timeoutint = atoi(timeout);

        } else {
            timeoutint = TIMEOUT;
        }
    }

    // Set operating system
    std::string r_arch = od.getArch();
    if (!r_arch.empty()) {
        r.setOperatingSystem(r_arch);
    }

    // Set min and expected mem
    float r_minMem, r_expMem;
    od.getMemory(r_minMem, r_expMem);
    if (r_minMem > 0) {
        r.setMinMemorySize(r_minMem);
    }
    if (r_expMem > 0) {
        r.setExpectedMemorySize(r_expMem);
    }

    // Set min and expected bandwidth
    float r_minB, r_expB;
    od.getBandwidth(r_expB, r_minB);
    if (r_minB > 0) {
        r.setMinNetworkBandwidth(r_minB);
    }
    if (r_expB > 0) {
        r.setExpectedNetworkBandwidth(r_expB);
    }

    // Set min and expected power
    float r_minPower, r_expPower;
    od.getPower(r_expPower, r_minPower);
    if (r_minPower > 0) {
        r.setMinPower(r_minPower);
    }
    if (r_expPower > 0) {
        r.setExpectedPower(r_expPower);
    }

    Update();

    /**
     * ViSaG : clementval
     * Retrieve the POPAppID and set it in the request
     */
    AppCoreService appservice(localservice);
    std::string popAppId = appservice.GetPOPCAppID();
    r.setPOPAppId(popAppId);

    std::string reqID = psn.getUID();
    r.setUniqueId(reqID);
    // Launch the discovery and recover the responses
    POPCSearchNodeInfos responses = psn.launchDiscovery(r, timeoutint);

    // Check if there is any responses
    if (responses.getNodeInfos().size() == 0) {
        pop_exception::pop_throw("No ressource found for execution");
    }

    // Distribute object creation request on responses
    std::list<POPCSearchNodeInfo> nodes;
    nodes = responses.getNodeInfos();
    int n_response = responses.getNodeInfos().size();
    int failedReservation = 0;
    auto ni = nodes.begin();
    for (int jobindex = 0; jobindex < howmany; jobindex++) {
        pop_accesspoint n_ac;
        n_ac.SetAccessString(ni->nodeId.c_str());
        // Contact the POPSearchNode
        POPCSearchNode n(n_ac);
        pop_accesspoint jm_ap = n.getJobMgrRef();
        // Contact the JobMgr
        JobMgr jobmgr(jm_ap);
        float t = 0;
        // Try to reserve on remote JobMgr
        reserveIDs[jobindex] = jobmgr.Reserve(od, t, popAppId, reqID);
        // if reserve ID is egal to 0, the reservation process failed. If we can't reserver on any responding machine,
        // we trow an exception
        if (reserveIDs[jobindex] == 0) {
            jobindex--;
            LOG_ERROR("[JM] UNABLE TO RESERVE ON %s", jm_ap.GetAccessString().c_str());
            failedReservation++;
            if (failedReservation == n_response) {
                return false;
            }
        } else {
            // Reservation process succeed

            // setting the remote JobMgr info to execute the parallel object
            jobcontacts[jobindex].SetAccessString(jm_ap.GetAccessString());
            LOG_DEBUG("[JM] RESID;%d;NODEID;%s", reserveIDs[jobindex], jm_ap.GetAccessString().c_str());
            // Setting the fitness
            fitness[jobindex] = t;
        }
        ni++;
        // Back to the beginning if we are at the end of the list
        if (ni == nodes.end()) {
            ni = nodes.begin();
        }
        ret = true;
    }

    // End of add
    return ret;
}

void JobMgr::CancelReservation(int* req, int howmany) {
    if (howmany <= 0) {
        return;
    }
    mutex {
        auto pos = jobs.begin();
        while (pos != jobs.end()) {
            auto oldpos = pos;
            auto& t = *pos++;
            for (int i = 0; i < howmany; i++) {
                if (t.Id == req[i] && t.contact.IsEmpty()) {
                    available.flops += t.flops;
                    available.mem += t.mem;
                    available.bandwidth += t.bandwidth;
                    jobs.erase(oldpos);
                    POPCSearchNode psn(_localPSN);
                    psn.removeJob(t.flops, t.mem, t.bandwidth, 1);
                }
            }
        }
    }
}

/**
 * ViSaG : clementval
 * Reserve the resource. Add the POPAppID for the reservation
 * @param od The Object Description for the parallel object requierments
 * @param inoutfitness The fitness computed for this resource
 * @param popAppID The POP Application ID
 * @return The reservation ID
 */
int JobMgr::Reserve(const pop_od& od, float& inoutfitness, std::string popAppId, std::string reqID) {
    Update();   //Called to see if there are jobs to be released

    float flops = 0;
    float walltime = 0;
    float mem = 0;
    float bandwidth = 0;

    float require, min;

    mutex {
        if (jobs.size() >= maxjobs) {
            return 0;
        }

        float fitness = 1;

        if (!od.IsEmpty()) {
            od.getPower(require, min);
            if (require > 0) {
                if (min < 0) {
                    min = require;
                }

                if (require > available.flops || require > limit.flops) {
                    flops = min(available.flops, limit.flops);
                    fitness = flops / require;
                } else {
                    fitness = min(available.flops, limit.flops) / require;
                    flops = require;
                }
                if (fitness < inoutfitness) {
                    return 0;
                }
            }
            od.getMemory(require, min);
            if (require > 0) {
                LOG_DEBUG("Require memory %f, at least: %f (available: %f)", require, min, available.mem);
                if (min < 0) {
                    min = require;
                }
                if (min > available.mem) {
                    LOG_ERROR("[JM] Local Match Failed (reason: memory)");
                    return 0;
                }
                float fitness1;
                if (require > available.mem) {
                    mem = available.mem;
                    fitness1 = mem / require;
                } else {
                    mem = require;
                    fitness1 = mem / available.mem;
                }
                if (fitness1 < fitness) {
                    if (fitness1 < inoutfitness) {
                        return 0;
                    }
                    fitness = fitness1;
                }
            }

            walltime = od.getWallTime();
            if (walltime < 0) {
                walltime = 0;
            }

            std::string walltime_str;
            if (Query("walltime", walltime_str)) {
                int walltime_l[4];
                int n = sscanf(walltime_str.c_str(), "%d:%d:%d:%d", walltime_l, walltime_l + 1, walltime_l + 2,
                               walltime_l + 3);
                if (n <= 0) {
                    LOG_ERROR("[JM] Bad walltime expression");
                } else {
                    if (n != 4) {
                        for (int i = n - 1; i >= 0; i--) {
                            walltime_l[i + 4 - n] = walltime_l[i];
                        }
                        for (int i = 3 - n; i >= 0; i--) {
                            walltime_l[i] = 0;
                        }
                    }
                    float maxwalltime =
                        walltime_l[3] + 60 * walltime_l[2] + 3600 * (walltime_l[1] + 24 * walltime_l[0]);

                    if ((walltime <= 0 && maxwalltime > 0) || walltime > maxwalltime) {
                        return 0;
                    }
                }
            }
        }
        inoutfitness = fitness;
        Resources t;
        t.Id = counter;
        t.flops = flops;
        t.mem = mem;
        t.bandwidth = bandwidth;
        t.start = time(nullptr);
        t.walltime = walltime;
        jobs.push_back(t);

        /**
         * ViSaG : clementval
         * Add the POPAppID into the resources
         */
        t.popAppId = popAppId;
        t.reqID = reqID;
        try {
            POPCSearchNode psn(_localPSN);
            psn.addJob(t.flops, t.mem, t.bandwidth);
        } catch (std::exception& e) {
            LOG_ERROR("[JM] Can't add job to PSN: %s", e.what());
            return 0;
        }
        available.flops -= flops;
        available.mem -= mem;
        available.bandwidth -= bandwidth;
        counter = (counter % 1000000000) + 1;
        LOG_INFO("[JM] Local Match OK (fitness=%f, reserveID=%d)", fitness, t.Id);
        LOG_INFO("[JM] GIVE_RESID;%d:MEM:%f:POW:%f:BAN:%f", t.Id, t.mem, t.flops, t.bandwidth);
        return t.Id;
    }
}

// This method return the reservation ID on success

int JobMgr::MatchAndReserve(const pop_od& od, float& inoutfitness) {
    float flops = 0;
    float walltime = 0;
    float mem = 0;
    float bandwidth = 0;

    float require, min;

    mutex {
        if (jobs.size() >= maxjobs) {
            return 0;
        }

        float fitness = 1;
        if (!od.IsEmpty()) {
            od.getPower(require, min);
            if (require > 0) {
                LOG_DEBUG("Require %f, at least: %f (available: %f)", require, min, available.flops);
                if (min < 0) {
                    min = require;
                }
                if (min > available.flops || min > limit.flops) {
                    LOG_ERROR("[JM] Local Match Failed (reason: power)");
                    return 0;
                }
                if (require > available.flops || require > limit.flops) {
                    flops = min(available.flops, limit.flops);
                    fitness = flops / require;
                } else {
                    fitness = min(available.flops, limit.flops) / require;
                    flops = require;
                }
                if (fitness < inoutfitness) {
                    return 0;
                }
            }
            od.getMemory(require, min);
            if (require > 0) {
                LOG_DEBUG("Require memory %f, at least: %f (available: %f)", require, min, available.mem);
                if (min < 0) {
                    min = require;
                }
                if (min > available.mem) {
                    LOG_ERROR("[JM] Local Match Failed (reason: memory)");
                    return 0;
                }
                float fitness1;
                if (require > available.mem) {
                    mem = available.mem;
                    fitness1 = mem / require;
                } else {
                    mem = require;
                    fitness1 = mem / available.mem;
                }
                if (fitness1 < fitness) {
                    if (fitness1 < inoutfitness) {
                        return 0;
                    }
                    fitness = fitness1;
                }
            }

            walltime = od.getWallTime();
            if (walltime < 0) {
                walltime = 0;
            }

            std::string walltime_str;
            if (Query("walltime", walltime_str)) {
                int walltime_l[4];
                int n = sscanf(walltime_str.c_str(), "%d:%d:%d:%d", walltime_l, walltime_l + 1, walltime_l + 2,
                               walltime_l + 3);
                if (n <= 0) {
                    LOG_ERROR("[JM] Bad walltime expression");
                } else {
                    if (n != 4) {
                        for (int i = n - 1; i >= 0; i--) {
                            walltime_l[i + 4 - n] = walltime_l[i];
                        }
                        for (int i = 3 - n; i >= 0; i--) {
                            walltime_l[i] = 0;
                        }
                    }
                    float maxwalltime =
                        walltime_l[3] + 60 * walltime_l[2] + 3600 * (walltime_l[1] + 24 * walltime_l[0]);

                    if ((walltime <= 0 && maxwalltime > 0) || walltime > maxwalltime) {
                        return 0;
                    }
                }
            }
        }
        inoutfitness = fitness;
        Resources t;
        t.Id = counter;
        t.flops = flops;
        t.mem = mem;
        t.bandwidth = bandwidth;
        t.start = time(nullptr);
        t.walltime = walltime;
        jobs.push_back(t);

        available.flops -= flops;
        available.mem -= mem;
        available.bandwidth -= bandwidth;
        counter = (counter % 1000000000) + 1;
        LOG_DEBUG("[JM] MatchAndReserve Match OK (fitness=%f, reserveID=%d)", fitness, t.Id);
        return t.Id;
    }
}

bool JobMgr::MatchAndReserve(const pop_od& od, float* fitness, pop_accesspoint* jobcontacts, int* reserveIDs,
                             int howmany) {
    if (howmany <= 0) {
        return false;
    }
    Update();
    bool ret = false;

    // Sort by the fitness
    std::vector<int> index(howmany);
    std::iota(index.begin(), index.end(), 0);

    for (int i = 0; i < howmany; i++) {
        for (int j = howmany - 1; j > i; j--) {
            if (fitness[index[j]] > fitness[index[j - 1]]) {
                int t = index[j];
                index[j] = index[j - 1];
                index[j - 1] = t;
            }
        }
    }

    for (int i = howmany - 1; i >= 0; i--) {
        int pos = index[i];
        float t = fitness[pos];
        if (t >= 1) {
            return ret;
        }
        int id = MatchAndReserve(od, fitness[pos]);
        if (id <= 0) {
            return ret;
        } else {
            ret = true;
        }

        if (t > 0 && !(jobcontacts[pos].IsEmpty())) {
            // Cancel previous reservation
            try {
                JobMgr res(jobcontacts[pos]);
                res.CancelReservation(reserveIDs + pos, 1);
            } catch (std::exception& e) {
                LOG_ERROR("[JM] Fail to cancel reservation #%d on %s %s", reserveIDs[pos],
                          jobcontacts[pos].GetAccessString().c_str(), e.what());
            }
        }
        reserveIDs[pos] = id;
        jobcontacts[pos] = GetAccessPoint();
    }
    return ret;
}

void JobMgr::Update() {
    mutex {
        // Check if a reservation timeout/job termination....then reget the resource...
        auto pos = jobs.begin();
        POPCSearchNode psn(_localPSN);
        while (pos != jobs.end()) {
            auto old = pos;
            Resources& t = *pos++;

            time_t now = time(nullptr);

            if (t.contact.IsEmpty()) {
                if (reserve_timeout > 0 && now - t.start > reserve_timeout) {
                    available.flops += t.flops;
                    available.mem += t.mem;
                    available.bandwidth += t.bandwidth;
                    pos = jobs.erase(old);
                    psn.removeJob(t.flops, t.mem, t.bandwidth, 1);
                }
            } else if (now - t.start > 5) {  // Do not check twice within 5 seconds
                if (ObjectAlive(t.contact)) {
                    t.start = now;
                } else {
                    available.flops += t.flops;
                    available.mem += t.mem;
                    available.bandwidth += t.bandwidth;
                    pos = jobs.erase(old);
                    psn.removeJob(t.flops, t.mem, t.bandwidth, 1);
                }
            }
        }
    }
}

bool JobMgr::Forward(const pop_accesspoint& localservice, const std::string& objname, const pop_od& od, int howmany,
                     float* fitness, pop_accesspoint* jobcontacts, int* reserveIDs, int requestInfo[3],
                     int iptrace[MAX_HOPS], int tracesize) {
    // The local host is not fully qualified! Find on other hosts....
    // Since this method can be invoked concurently,
    // we need to copy the data to local memony stack and process on these data

    Timer watch;
    watch.Start();
    bool ret = false;

    for (auto& contact : neighbors.GetContacts()) {
        NodeInfo info;
        if (!neighbors.GetInfo(contact, info)) {
            LOG_WARNING("Cannot get info of contact %s", contact.c_str());
            continue;
        }

        if (info.stoptime >= 0) {
            if (service_timer.Elapsed() - info.stoptime < PAUSE_FORWARD_TIMEOUT) {
                continue;
            }
            info.stoptime = -1;
        }

        // Check if the next IP is in the trace or not. If not, add...
        try {
            watch.Reset();
            LOG_DEBUG("\tForward request to %s (trace=%d)", contact.c_str(), tracesize);

            pop_accesspoint childaddr;
            childaddr.SetAccessString(contact.c_str());

            if (NodeInTrace(iptrace, tracesize, childaddr)) {
                continue;
            }

            // Separate the Fitness into 2 parts. Only forward the parts whose fitness<1...
            int good = 0;
            int nswap = 0;
            for (int j = 0; j < howmany; j++) {
                if (fitness[j] < 1) {
                    for (int k = howmany - 1 - nswap; k > j; k--) {
                        if (fitness[k] >= 1) {
                            float f = fitness[k];
                            fitness[k] = fitness[j];
                            fitness[j] = f;

                            int r = reserveIDs[k];
                            reserveIDs[k] = reserveIDs[j];
                            reserveIDs[j] = r;

                            pop_accesspoint ac(jobcontacts[k]);
                            jobcontacts[k] = jobcontacts[j];
                            jobcontacts[j] = ac;
                            nswap++;
                            break;
                        }
                    }

                    if (fitness[j] < 1) {
                        break;
                    }

                    good++;
                } else {
                    good++;
                }
            }

            int count = howmany - good;
            if (count <= 0) {
                break;
            }
            JobMgr child(childaddr);

            std::vector<float> oldfitness;
            std::copy(fitness + good, fitness + good + count, std::back_inserter(oldfitness));

            if (child.AllocResource(localservice, objname, od, count, fitness + good, jobcontacts + good,
                                    reserveIDs + good, requestInfo, iptrace, tracesize)) {
                ret = true;
                double seconds = watch.Elapsed();
                float sumfitness = 0;
                float* tmp = fitness + good;
                for (int j = 0; j < count; j++)
                    if (tmp[j] != oldfitness[j]) {
                        sumfitness += tmp[j];
                    }

                if (sumfitness > 0) {
                    info.heuristic = (info.heuristic + seconds / sumfitness) / 1.9;
                } else {
                    info.heuristic += seconds;
                }

                if (info.heuristic > MAX_HEURISTICS) {
                    info.heuristic = MAX_HEURISTICS;
                }
            } else {
                info.heuristic += watch.Elapsed();
                if (info.heuristic > MAX_HEURISTICS) {
                    info.heuristic = MAX_HEURISTICS;
                }
            }
        } catch (std::exception& e) {
            LOG_CORE("[JM] Exception on contact %s: %s", contact.c_str(), e.what());

            if (info.nodetype != NODE_STATIC) {
                neighbors.Remove(contact);
                continue;
            } else {
                info.heuristic = 2 * MAX_HEURISTICS;
                info.stoptime = service_timer.Elapsed();
            }
        }
        neighbors.Update(contact, info);
    }

    if (modelearn) {
        std::vector<int> index(howmany);
        for (int i = 0; i < howmany; i++) {
            index[i] = (fitness[i] <= 0) ? 1 : -1;
        }

        int total = 0;
        std::string local = GetAccessPoint().GetAccessString();
        for (int i = 0; i < howmany; i++) {
            if (index[i] == -1) {
                index[i] = 1;
                std::string t(jobcontacts[i].GetAccessString());
                if (t.empty() || t == local) {
                    continue;
                }
                NodeInfo info;
                info.nodetype = NODE_LEARNT;
                info.stoptime = -1;
                info.heuristic = 0;
                if (neighbors.Add(t, info)) {
                    total++;
                }

                for (int j = i + 1; j < howmany; j++) {
                    if (index[j] == -1 && jobcontacts[i].GetAccessString() == jobcontacts[j].GetAccessString()) {
                        index[j] = 1;
                    }
                }
            }
        }
    }

    // Now remove dynamic nodes to keep balance....
    // TO DO....
    return ret;
}

void JobMgr::SelfRegister() {
    static double lasttime = -500;

    if ((service_timer.Elapsed() - lasttime) < 300) {
        return;
    }
    lasttime = service_timer.Elapsed() + 36000;

    LOG_DEBUG("Updating my contact to parent nodes...");
    for (auto& tmp : parents) {
        try {
            tmp.SetAsService();
            JobMgr remote(tmp);
            // Added by clementval
            // Register the local POPCSearchNode to its neighbors and add neighbor in the neighbors list
            remote.RegisterNode(_localPSN);
            POPCSearchNode remoteNode(remote.GetNodeAccessPoint());
            POPCSearchNode psn(_localPSN);
            psn.addNeighbor(remoteNode);
            // End of add
        } catch (std::exception& e) {
            LOG_ERROR("[JM] can not register the local job service [%s] to %s: %s",
                      GetAccessPoint().GetAccessString().c_str(), tmp.GetAccessString().c_str(), e.what());
        }
    }
    lasttime = service_timer.Elapsed();
}

void JobMgr::Start() {
    JobCoreService::Start();

    popc_close(0);
    popc_close(1);
    popc_close(2);
    popc_open("/dev/null", O_RDONLY);

    char* tmp = getenv("POPC_TEMP");
    int pid = popc_getpid();
    char filename[256];
#ifndef NDEBUG
    if (tmp != nullptr) {
        snprintf(filename, sizeof(filename), "%s/jobmgr_stdout_%d", tmp, pid);
    } else {
        snprintf(filename, sizeof(filename), "/tmp/jobmgr_stdout_%d", pid);
    }

    popc_open(filename, O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP);

    if (tmp != nullptr) {
        snprintf(filename, sizeof(filename), "%s/jobmgr_stderr_%d", tmp, pid);
    } else {
        snprintf(filename, sizeof(filename), "/tmp/jobmgr_stderr_%d", pid);
    }

    popc_open(filename, O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP);

#else
    popc_open("/dev/null", O_WRONLY);
    popc_open("/dev/null", O_WRONLY);
#endif

    if (tmp != nullptr) {
        snprintf(filename, sizeof(filename), "%s/jobmgr.pid", tmp);
    } else {
        strcpy(filename, "/tmp/jobmgr.pid");
    }

    FILE* f = fopen(filename, "w+");
    if (f != nullptr) {
        fprintf(f, "%d", pid);
        fclose(f);
    }
}

/**
 * ViSag : clementval (modification)
 * Execute a parallel object
 * - Add the POPAppId and reqID to manage virtual machine
 * @param arguments
 * @param env[]
 * @param pid
 * @param popAppId   The POP Application ID associated with the parallel object to be executed
 * @return
 */
int JobMgr::Exec(char** arguments, char* env[], int& pid, std::string popAppId, std::string reqID) {
    std::vector<std::string> argv;
    char* first = nullptr;
    char sep[] = " \n\r\t";
    std::string str;

    char java_exec[100];
    char* pt_java_exec;
    if (!(pt_java_exec = getenv("POPJAVA_JAVA"))) {
        strcpy(java_exec, "/usr/bin/java");
        pt_java_exec = java_exec;
    }

    if (*arguments != nullptr) {
        first = *arguments;
    }

    if (strcmp(first, pt_java_exec) != 0) {
        if (Query("jobmgr", str) && !str.empty()) {
            popc_tokenize_r(argv, str, sep);
        }
    }
    int n = 0;
    while (*arguments != nullptr && n < 1023) {
        argv.push_back(*arguments);
        arguments++;
        n++;
    }

    if (argv.empty()) {
        return ENOENT;
    }
    const std::string& file = argv[0];

#ifndef UC_LINUX
    pid = popc_fork();
    if (pid == -1) {
        LOG_ERROR("[JM] Execute command fail. Pause on error...");
        pop_accesspoint empty;
        Pause(empty, SLEEP_TIME_ON_ERROR);
        return errno;
    } else if (pid == 0) {
        /* Note LW: Commented since this stops "segfault" messages to be logged in terminal. What is the purpose of
        these lines ?
        int nf=popc_getdtablesize();
        for(int fd=3; fd<nf; fd++) {
            popc_close(fd);
        }
        */
        if (localuid >= 0) {
            int ret = popc_setuid(localuid);
            if (ret != 0) {
                perror("ERROR: can not setuid");
            }
        }

        if (env != nullptr) {
            while (*env != nullptr) {
                putenv(popc_strdup(*env));
                env++;
            }
        }

        // Child process
        char** argvc = popc_createArgsFromVect(argv);
        popc_execvp(file.c_str(), argvc);
        popc_freeArgs(argvc);
        LOG_ERROR("[JM] Execution of [%s] fail", file.c_str());
        popc__exit(-1);
    }
#else
    pid = popc_vfork();
    if (pid == -1) {
        LOG_ERROR("[JM] Execute command fail. Pause on error...");
        pop_accesspoint empty;
        Pause(empty, SLEEP_TIME_ON_ERROR);
        return errno;
    } else if (pid == 0) {
        execve(file, argv, env);
        LOG_ERROR("[JM] Execution of [%s] fail (popc_vfork)", file);
        popc__exit(-1);
    }
#endif
    return 0;
}

int JobMgr::ExecObj(const std::string& objname, const pop_od& od, int howmany, int* reserveIDs,
                    const pop_accesspoint& localservice, pop_accesspoint* objcontacts) {
    if (howmany <= 0) {
        LOG_ERROR("[JM] Exec failed because howmany is less or equal to 0");
        return EINVAL;
    }
    char* env[32];
    char** curenv = env;
    char env_np[256];
    char env_walltime[256];
    *env_walltime = 0;
    const std::string& cwd = od.getCwd();
    snprintf(env_np, sizeof(env_np), "POPC_NP=%d", howmany);
    *curenv = env_np;
    curenv++;
    // Visag 1l
    std::string crtPopAppId;
    std::string crtReqID;

    mutex {
        for (int i = 0; i < howmany; i++) {
            Resources* r = VerifyReservation(reserveIDs[i], true);
            // Visag 1l
            crtPopAppId = (*r).popAppId;
            crtReqID = (*r).reqID;
            if (r == nullptr) {
                CancelReservation(reserveIDs, howmany);
                LOG_ERROR("[JM] Exec failed because reservation is null");
#ifndef __WIN32__
                return ECANCELED;
#endif
                return -1;
            }

            if (r->walltime > 0 && *env_walltime == 0) {
                int hours   = static_cast<int>(r->walltime / 3600);
                int minutes = static_cast<int>((r->walltime - hours * 3600) / 60);
                float sec = r->walltime - hours * 3600 - minutes * 60;
                snprintf(env_walltime, sizeof(env_walltime), "POPC_JOB_WALLTIME=%d:%d:%g", hours, minutes, sec);
                *curenv = env_walltime;
                curenv++;
            }
        }
    }

    *curenv = nullptr;
    std::string mycodefile;
    try {
        CodeMgr code(localservice);
        if (!code.QueryCode(objname, pop_system::platform, mycodefile) || mycodefile.empty()) {
            CancelReservation(reserveIDs, howmany);
            std::string tmpObjname = objname;
            std::string tmpPlatform = pop_system::platform;
            LOG_ERROR("[JM] Exec failed: CodeMgr was looking for %s on platform %s", tmpObjname.c_str(),
                      tmpPlatform.c_str());
            return ENOENT;
        }
    } catch (std::exception& e) {
        CancelReservation(reserveIDs, howmany);
        LOG_ERROR("[JM] Exec failed. CodeMgr cannot be contacted: %s", e.what());
        return ENOENT;
    }

    std::vector<std::string> argv;
    int n = 0;
    // char *code=mycodefile.c_str();
    popc_tokenize_r(argv, mycodefile, " \t\n");
    std::string obj_arg("-object=");
    obj_arg += objname;
    argv.push_back(obj_arg);

    // Setup Global job service
    std::string jobservice_arg("-jobservice=");
    jobservice_arg += GetAccessPoint().GetAccessString();
    argv.push_back(jobservice_arg.c_str());
    // Setup application specific services...
    std::string localservice_arg("-appservice=");
    if (!localservice.IsEmpty()) {
        localservice_arg += localservice.GetAccessString();
        argv.push_back(localservice_arg);
    }

    pop_combox_socket tmpsock;
    if (!tmpsock.Create(0, true)) {
        CancelReservation(reserveIDs, howmany);
        LOG_ERROR("[JM] Exec failed. Socket cannot be created.");
        return errno;
    }

    auto cburl = tmpsock.GetUrl();
    char tmpstr[1024];
    snprintf(tmpstr, sizeof(tmpstr), "-callback=%s", cburl.c_str());
    argv.push_back(tmpstr);

#ifdef OD_DISCONNECT
    if (od.getCheckConnection()) {
        argv.push_back("-checkConnection");
    }
#endif

    // Add the working directory as argument
    if (!cwd.empty()) {
        snprintf(tmpstr, sizeof(tmpstr), "-cwd=%s", cwd.c_str());
        argv.push_back(tmpstr);
    }
#ifndef NDEBUG
    std::stringstream ss;
    ss << "--->";
    for (int i = 0; i < argv.size(); i++) {
        ss << argv[i] << " ";
    }
    LOG_DEBUG("Launching a new object with command : %s", ss.str().c_str());
#endif
    int pid;
    /* Visag add crtPopAppId */

    char** argvc = popc_createArgsFromVect(argv);
    int ret = Exec(argvc, env, pid, crtPopAppId, crtReqID);
    popc_freeArgs(argvc);

    if (ret != 0) {
        Pause(localservice, SLEEP_TIME_ON_ERROR);
        CancelReservation(reserveIDs, howmany);
        LOG_ERROR("[JM] Exec failed. Exec return value is not 0");
        return ret;
    }

    // Receive the object accesspoint from object broker....
    tmpsock.SetTimeout(alloc_timeout * 1000);

    for (int i = 0; i < howmany; i++) {
        pop_buffer_xdr buf1;
        pop_buffer& buf = buf1;

        if (!buf.Recv(tmpsock)) {
            int err = errno;
            if (pid > 0) {
                popc_kill(pid, popc_SIGKILL);
            }
            Pause(localservice, SLEEP_TIME_ON_ERROR);
            CancelReservation(reserveIDs, howmany);
            LOG_ERROR("[JM] Exec failed for accesspoint.");
            return err;
        }

        int n;
        buf.Push("status", "int", 1);
        buf.UnPack(&n, 1);
        buf.Pop();

        if (n != 0) {
            if (pid > 0) {
                popc_kill(pid, popc_SIGKILL);
            }
            Pause(localservice, SLEEP_TIME_ON_ERROR);
            CancelReservation(reserveIDs, howmany);
            return n;
        }

        buf.Push("address", "pop_accesspoint", 1);
        objcontacts[i].Serialize(buf, false);
        buf.Pop();

        if (!ValidateReservation(reserveIDs[i], objcontacts[i], localservice)) {
            if (pid > 0) {
                popc_kill(pid, popc_SIGKILL);
            }
            CancelReservation(reserveIDs, howmany);
#ifndef __WIN32__
            return ECANCELED;
#else
            return -1;
#endif
        }
    }
    return 0;
}

bool JobMgr::MatchUser(const pop_accesspoint& localservice) {
    return true;
}

void JobMgr::dump() {
#ifndef NDEBUG
    FILE* f;
    char str[256];
    snprintf(str, sizeof(str), "%s/JobMgr_%d", DUMP_PATH, popc_getpid());
    char* tmp = str;
    for (char* tmp = str; *tmp != 0; tmp++)
        if (*tmp == ':') {
            *tmp = '_';
        }
    f = fopen(tmp, "w+t");
    if (!f) {
        return;
    }

    auto keys = neighbors.GetContacts();
    fprintf(f, "Neighbour nodes (%zu)\n", keys.size());

    for (std::size_t i = 0; i < keys.size(); ++i) {
        auto& t = keys[i];
        NodeInfo info;
        if (neighbors.GetInfo(t, info)) {
            fprintf(f, "%zu: %s\t%g\t%d\n", i, t.c_str(), info.heuristic, static_cast<int>(info.nodetype));
        }
    }
    fclose(f);
#endif
}

void JobMgr::Pause(const pop_accesspoint& app, int duration) {
    LOG_DEBUG("[JM] Pause %d seconds", duration);
    mutex {
        pause_apps.emplace_back();
        auto& t = pause_apps.back();
        t.until_time = service_timer.Elapsed() + duration;
        t.app = app;
    }
}

bool JobMgr::CheckPauseList(const pop_accesspoint& app) {
    double now = service_timer.Elapsed();
    mutex {
        auto it = pause_apps.begin();
        auto end = pause_apps.end();

        while (it != end) {
            auto& t = *it;

            if (now > t.until_time) {
                it = pause_apps.erase(it);
                end = pause_apps.end();
            } else if (t.app.IsEmpty() || t.app == app) {
                LOG_DEBUG("CheckPauseList return true (app=%s)", t.app.GetAccessString().c_str());
                return true;
            }
        }
    }

    return false;
}

bool JobMgr::AddRequest(int reqId[3]) {
    double oldest = service_timer.Elapsed();
    if (reserve_timeout > 0) {
        oldest -= 2 * reserve_timeout;
    } else {
        oldest -= 300;
    }

    mutex {
        for (auto& t : tracelist) {
            if (memcmp(t.requestID, reqId, 3 * sizeof(int)) == 0) {
                return false;
            }
        }

        tracelist.erase(std::remove_if(tracelist.begin(), tracelist.end(),
                                       [oldest](RequestTrace& t) { return t.timestamp < oldest; }),
                        tracelist.end());

        tracelist.emplace_back();

        auto& t = tracelist.back();
        memcpy(t.requestID, reqId, 3 * sizeof(int));
        t.timestamp = service_timer.Elapsed();

        if (tracelist.size() > 100) {
            LOG_INFO("[JM] Warning: job trace list is too big (%d items)", tracelist.size());
        }

        return true;
    }
}

bool JobMgr::AddTrace(int trace[MAX_HOPS], int& tracesize) {
    if (tracesize < 0 || tracesize >= MAX_HOPS) {
        return false;
    }
    if (pop_system::GetIP(trace + tracesize, 1) == 1) {
        tracesize++;
        return true;
    }
    return false;
}

bool JobMgr::NodeInTrace(int trace[MAX_HOPS], int tracesize, pop_accesspoint& contact) {
    if (tracesize < 0 || tracesize >= MAX_HOPS || contact.IsEmpty()) {
        return false;
    }
    char host[1024];
    strcpy(host, contact.GetAccessString().c_str());

    char* hostname = host;

    char* t = strstr(host, "socket://");
    if (t != nullptr) {
        hostname = t + 9;
    } else {
        t = strstr(host, "http://");
        if (t != nullptr) {
            hostname = t + 7;
        }
    }

    t = strchr(hostname, ':');

    if (t != nullptr) {
        *t = 0;
    }
    int ip;
    if (pop_system::GetIP(hostname, &ip, 1) != 1) {
        return false;
    }

    for (int i = 0; i < tracesize; i++, trace++)
        if (*trace == ip) {
            return true;
        }
    return false;
}

bool JobMgr::ObjectAlive(pop_accesspoint& t) {
    try {
        pop_interface test(t);
        return true;
    } catch (std::exception& e) {
        LOG_WARNING("Exception in JobMgr::ObjectAlive: %s", e.what());
        return false;
    }
}

Resources* JobMgr::VerifyReservation(int reserveId, bool updatetime) {
    mutex {
        for (auto& tmp : jobs) {
            if (tmp.Id == reserveId) {
                if (updatetime) {
                    tmp.start = time(nullptr);
                }
                return &tmp;
            }
        }
    }
    return nullptr;
}

bool JobMgr::ValidateReservation(int id, const pop_accesspoint& objcontact, const pop_accesspoint& appserv) {
    mutex {
        for (auto& tmp : jobs) {
            if (tmp.Id == id) {
                tmp.contact = objcontact;
                tmp.appservice = appserv;
                tmp.start = time(nullptr);
                return true;
            }
        }
    }
    return false;
}

bool JobMgr::ReleaseJob(int id) {
    if (id <= 0) {
        return false;
    }
    mutex {
        auto pos = jobs.begin();
        while (pos != jobs.end()) {
            auto oldpos = pos;
            auto& t = *pos++;
            if (t.Id == id && !t.contact.IsEmpty()) {
                available.flops += t.flops;
                available.mem += t.mem;
                available.bandwidth += t.bandwidth;
                jobs.erase(oldpos);
                POPCSearchNode psn(_localPSN);
                psn.removeJob(t.flops, t.mem, t.bandwidth, 1);
                return true;
            }
        }
    }
    return false;
}

/**
 * ViSaG : clementval
 * All the code after this comment is additional code for the ViSaG project
 */

/**
 * ViSaG : clementval
 * Method called when an application is finished
 * @param popAppId The POP Application ID of the application
 */
void JobMgr::ApplicationEnd(std::string popAppId, bool initiator) {
    /* If this node is the Main Node of the application, it should send the End Signal to other node. The End Signal is
     * propagated
      * by the resource discovery mechanism
      */
    if (initiator) {
        Request r;
        r.setAsEndRequest();
        r.setPOPAppId(popAppId);
        POPCSearchNode psn(_localPSN);
        std::string reqID = psn.getUID();
        r.setUniqueId(reqID);
        psn.launchDiscovery(r, 1);
    }
    // Update the resource node and free reservation for this POPAppID
    bool hasRemoved = false;
    int nbJob = 0;
    mutex {
        auto pos = jobs.begin();
        while (pos != jobs.end()) {
            auto oldpos = pos;
            auto& t = *pos++;

            if (strcmp(t.popAppId.c_str(), popAppId.c_str()) == 0) {
                available.flops += t.flops;
                available.mem += t.mem;
                available.bandwidth += t.bandwidth;
                nbJob++;
                pos = jobs.erase(oldpos);
                hasRemoved = true;
            }
        }
    }

    // Update PSN if resource change
    if (hasRemoved) {
        try {
            POPCSearchNode psn(_localPSN);
            psn.removeJob(available.flops, available.mem, available.bandwidth, nbJob);
        } catch (std::exception& e) {
            LOG_ERROR("[JM] can't update PSN resource: %s", e.what());
        }
    }
}

/**
 * ViSaG : clementval
 * Set the reference of the local Security Manager running on the same node as this Job Manager
 * @param Access Point to the local POPC Security Manager
 */

void JobMgr::setPSMRef(pop_accesspoint secmgr) {
    _localPSM = secmgr;
}

/**
 * ViSaG : clementval
 * Get the reference of the local Security Manager running on the same node as this Job Manager
 * @return Access Point to the local JobMgr
 */

pop_accesspoint JobMgr::getPSMRef() {
    return _localPSM;
}
