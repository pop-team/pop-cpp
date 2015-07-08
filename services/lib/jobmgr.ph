/**
 * File : jobmgr.ph
 * Author : Tuan Anh Nguyen
 * Description : Declaration of the parallel object JobMgr (POP-C++ Global Services)
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 * clementval   2010/04/19  All code added for the semester project begins with this comment //Added by clementval, ends with
 *                         //End of add
 * clementval   2010/04/19  All code modified during the semester project begins with //Modified by clementval, ends with
 *                         //End of modification
 * clementval   2010/04/29  Full functionnal version with the new POPSearchNode that is in charge of the resource discovery.
 *                         Biggest change are in the method AllocResource.
 *                              Add new method UnregisterNode, Reserve, GetNodeAccessPoint
 * clementval   2010/05/02  Better distribution of parallel object on discovered ressources
 * Wyssen      2010/08/04  Added the prototypes for the virtual version of POP-C++. All modified code is marked with
 *                         Begining -> ### Added by Wyssen ###
 *                         Ending   -> ### End ###
 */

#ifndef JOBMGR_PH
#define JOBMGR_PH

#include <unordered_map>
#include <time.h>
#include <sys/time.h>
#include "service_base.ph"
#include "pop_timer.h"
#include "pop_accesspoint.h"

/**
 * ViSaG : clementval
 */

//Added by clementval
#include <list>
#include "pop_request.h"
#include "pop_response.h"
#include "pop_exploration_list.h"
#include "pop_search_node_info.h"
#include "search_node.ph"

// note LW: changed the timer from 0 to 3: avoid collisions if the local node is full
#define TIMEOUT 3;                  // Waiting time of the resources discovery algorithm
#define MAXHOP 1000;                    // Maximum depth for a discovery request
#define SELFREGISTER_TIMEOUT 84600  //Time before between two self-registration (default one day)
//End

/* ### Added by Wyssen ### */
//#include "ESXWrapper.h"
//#include "WrapperFactory.h"
/* ### End ### */



#define PAUSE_FORWARD_TIMEOUT 300

#define MAX_CONTACT_LENGTH 64

#define DEFAULT_PORT "2711"
#define DUMP_PATH "/tmp"

#define MAX_HEURISTICS 200

#define SLEEP_TIME_ON_ERROR 120

#define MAX_HOPS 20

#define HASH_SIZE 101

#define NODE_STATIC -1
#define NODE_LEARNT 0
#define NODE_REGISTERED 2

struct Resources {
    int Id;
    float flops;
    float mem;
    float bandwidth;
    float walltime;
    /**
     * ViSaG : clementval
     * Add the popAppId into the Resources struct
     * Add the reqID into the Resources struct
     */
    std::string popAppId;
    std::string reqID;

    time_t start;
    pop_accesspoint contact;
    pop_accesspoint appservice;
};


struct NodeInfo {
    double heuristic;
    int id;
    double stoptime;
    bool fixnode;
    int nodetype;
};

struct PauseInfo {
    double until_time;
    pop_accesspoint app;
};

struct HostInfo {
    std::string  name;
    std::string val;
};

struct RequestTrace {
    int requestID[3];
    double timestamp;
};

typedef std::vector<HostInfo> HostInfoDB;
typedef std::vector<NodeInfo> NodeInfoList;
typedef std::vector<Resources> ResourceList;
typedef std::vector<PauseInfo> PauseList;
typedef std::vector<RequestTrace> TraceList;

/**
 * @class NodeInfoMap
 * @brief (to be written), used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 */
class NodeInfoMap {
public:
    NodeInfoMap();
//Manipulate neighbor nodes (thread safe)
    std::vector<std::string> GetContacts();
    bool HasContact(const std::string &contact);

    bool GetInfo(const std::string &contact, NodeInfo &info);
    int GetCount();

    bool Update(const std::string &contact, NodeInfo &info);
    bool Remove(const std::string &key);
    bool Add(const std::string &contact, NodeInfo &info);
private:
    std::unordered_map<std::string, NodeInfo> hashmap;
    pop_mutex maplock;
};

/**
 * @class JobMgr
 * @brief Parclass : Manages the execution of jobs, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 */
parclass JobMgr :
public JobCoreService {
public:
    /* ViSaG : clementval : Add reference to the PSM */
    JobMgr(bool daemon, [in] const std::string &conf, [in] const std::string &challenge, const std::string &url, const pop_accesspoint &nodeAccess, const pop_accesspoint &localPSM) @{ od.url(url); od.runLocal(true); od.service(true);};
    /* End */

    ~JobMgr();  //Method ID 11

    conc async void RegisterNode([in] const pop_accesspoint &url);  //Method ID 12


    /**
     * @brief Returns information about the job manager : power, jobs, ...
     * @param type input
     * @param val output
     */
    sync seq virtual int Query([in] const std::string &type, [out] std::string &val); //Method ID 13

//Global service...
    sync conc virtual int CreateObject(pop_accesspoint &localservice, const std::string &objname, const pop_od &od, int howmany, [in, out,size=howmany] pop_accesspoint *jobcontacts,  int howmany2, [in, out, size=howmany2] pop_accesspoint *remotejobcontacts); //Method ID 14


    sync conc virtual bool  AllocResource(const pop_accesspoint &localservice, const std::string &objname, const pop_od &od, int howmany, [in,out, size=howmany] float *fitness, [in,out, size=howmany] pop_accesspoint *jobcontacts, [in,out, size=howmany] int *reserveIDs, [in] int requestInfo[3], [in] int trace[MAX_HOPS], [in] int tracesize); //method ID 15

    /**
     * ViSaG : clementval
     * Reserve the resource. Add the POPAppID for the reservation
     * @param od The Object Description for the parallel object requierments
     * @param inoutfitness The fitness computed for this resource
     * @param popAppID The POP Application ID
     * @return The reservation ID
     */
    sync conc virtual int Reserve(const pop_od &od, float &inoutfitness, std::string popAppId, std::string reqID); //16

    seq async virtual void CancelReservation([in, size=howmany] int *req, int howmany); //17

    conc sync virtual int ExecObj(const std::string &objname, const pop_od &od, int howmany, [in, size=howmany] int *reserveIDs, const pop_accesspoint &localservice,  [out, size=howmany] pop_accesspoint *objcontacts);

    seq async void dump();

    virtual void Start();

    async void SelfRegister();

//  async conc virtual void ApplicationEnd(std::string popAppId);

    //Added by clementval

    //Return the access point for the local POPCSearchNode parclass
    conc sync pop_accesspoint GetNodeAccessPoint();

    //Allow the unregistration of a specific node
    conc async void UnregisterNode([in] const pop_accesspoint &url);


    /**
     * ViSaG : clementval
     * Method called when an application is finished
     */
    async conc virtual void ApplicationEnd(std::string popAppId, bool initiator);
    //End of add

    /**
    * ViSaG : clementval
    * Method to get and set the POPCSecurityManager reference
    */
    async seq void setPSMRef(pop_accesspoint secmgr);
    sync conc virtual pop_accesspoint getPSMRef();

    classuid(15);
protected:
    virtual void Update();
    virtual int Exec(char **arguments, char **env, int &pid, std::string popAppId, std::string reqID);
    virtual int MatchAndReserve(const pop_od &od, float & fitness);
    virtual bool MatchAndReserve(const pop_od &od, float *fitness, pop_accesspoint *jobcontacts, int *reserveIDs, int howmany);
    virtual bool Forward(const pop_accesspoint &localservice, const std::string &objname, const pop_od &od, int howmany, float *fitness,       pop_accesspoint *jobcontacts, int *reserveIDs, int requestInfo[3], int iptrace[MAX_HOPS], int tracesize);

    virtual bool MatchUser(const pop_accesspoint &localservice);

    virtual void Pause(const pop_accesspoint &app, int duration);
    virtual bool CheckPauseList(const pop_accesspoint &app);

    bool AddRequest(int reqId[3]);

    bool AddTrace(int trace[MAX_HOPS], int &tracesize);
    bool NodeInTrace([in,size=tracesize]int trace[MAX_HOPS], int tracesize, pop_accesspoint &contact);


    bool ObjectAlive(pop_accesspoint &t);
    Resources* VerifyReservation(int reserveId, bool updatetime);
    bool ValidateReservation(int id, const pop_accesspoint &objcontact, const pop_accesspoint &appserv);
    bool ReleaseJob(int id);

    HostInfoDB info;

    NodeInfoMap neighbors;

    //Added by clementval

    //Access Point of the local POPCSearchNode
    //pop_accesspoint localNode;
    //End of add

    TraceList tracelist;
    int requestCounter;


    int dynamicnodes; //number of current nodes that are dynamically updated
    int maxdynamicnodes; //max number of dynamic updated nodes

    ResourceList jobs;

    int maxjobs;
    Resources available;
    Resources limit;
    Resources total;


    int myjobs;
    int counter;

    int serviceID[2]; //pair (IP,port) at most

    int myPID;

    int reserve_timeout;
    int alloc_timeout;

    int localuid;

    Timer service_timer;
    pop_accesspoint_list parents;

    PauseList pause_apps;

    bool modelearn;

    /* ViSaG : clementval */

    pop_accesspoint _localPSN;  //reference to the local POPCSearchNode
    pop_accesspoint _localPSM;  //reference to the local POPCSecurityManager

};

int paroc_service_log(const char *format,...);

//Added by clementval
//To write in POPSearchNode log file
int popc_node_log(const char *format,...);
//End of add

#endif //JOBMGR_PH

