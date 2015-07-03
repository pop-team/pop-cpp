/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Parallel object description implementation.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_ObjectDescription instead of pop_od
 */

#include "pop_intface.h"
#include "pop_od.h"
#include "pop_utils.h"

bool pop_od::defaultLocalJob = false;

pop_od::pop_od() {
    mflops = min_mflops = ram = min_ram = net = min_net = time = -1;
#ifdef OD_DISCONNECT
    time_alive = time_control = -1;
#endif
    isManual = false;
    char* tmp = getenv("POPC_BATCH");
    if (tmp != nullptr) {
        batchSystem = tmp;
        hostname = batchSystem;  // To avoid letting the hostname empty
    }
    isLocalJob = defaultLocalJob;
    sameDirectory(true);  // Set the working directory to the current one by default
    secureSet = false;
    searchSet = false;
    serviceSet = false;
    max_depth = 100;
    max_size = 0;
    wait_time = 0;
    node_value = -1;
    core_value = -1;
}

pop_od::~pop_od() {
}

/**
 * ViSaG : clementval
 * Set the value of the od service
 * @param serv Boolean value to set to the od service
 */
void pop_od::service(bool serv) {
    serviceSet = serv;
}

/**
 * ViSaG : clementval
 * Check is the od service is set
 * @return TRUE is the od service is set
 */
bool pop_od::isServiceSet() const {
    return serviceSet;
}

/**
 * Get the node identifier
 * @return Node value defined by the developer or -1 is no node value was defined
 */
int pop_od::get_node() const {
    return node_value;
}

/**
 * Get the core identifier
 * @return Core value defined by the developer or -1 is no core value was defined
 */
int pop_od::get_core() const {
    return core_value;
}

/**
 * Define the node on which the parallel object should be allocated
 * @param An integer value between 0 and N-1. N is the number of available nodes.
 */
void pop_od::node(int value) {
    node_value = value;
}

/**
 * Define the core on which the parallel object should be allocated
 * @param value An integer value between 0 and N-1. N is the number of available core.
 */
void pop_od::core(int value) {
    core_value = value;
}

void pop_od::power(float require, float min) {
    if (min > require) {
        float t = min;
        min = require;
        require = t;
    }
    mflops = require;
    min_mflops = min;
}

void pop_od::memory(float require, float min) {
    if (min > require) {
        float t = min;
        min = require;
        require = t;
    }
    ram = require;
    min_ram = min;
}

void pop_od::bandwidth(float require, float min) {
    if (min > require) {
        float t = min;
        min = require;
        require = t;
    }
    net = require;
    min_net = min;
}

void pop_od::walltime(float t) {
    time = t;
}

void pop_od::url(const std::string& str) {
    char h[256];
    char* tmpstr;
    strcpy(h, str.c_str());

    // Read if user specified for rsh/ssh
    if ((tmpstr = strchr(h, '@'))) {
        *tmpstr = 0;
        hostuser = h;
        strcpy(h, tmpstr + 1);
    }

    // Read if core specified
    if ((tmpstr = strchr(h, '{'))) {
        *tmpstr = 0;
        char* tmpstr2;
        if ((tmpstr2 = strchr(tmpstr + 1, '}')) != nullptr) {
            *tmpstr2 = 0;
            hostcore = tmpstr + 1;
        } else {
            LOG_INFO("Error in object description. user@ip(core):port");
        }
    }

    hostname = h;
    if (hostname == "localhost") {
        runLocal(true);
    }
}

void pop_od::url(const std::string& h, const std::string& arch) {
    hostarch = arch;
    url(h);
}

void pop_od::manual(bool a) {
    url("localhost");
    isManual = a;
}

void pop_od::runLocal(bool isLocal) {
    isLocalJob = isLocal;
}

// Set working dir to the current dir on interface side
void pop_od::sameDirectory(bool a) {
    if (a) {
        char tmp[256];
        if (popc_getcwd(tmp, sizeof(tmp)) != nullptr) {
            cwd = tmp;
        }
    }
}

// Added by clementval
// set resource discovery parameter
void pop_od::search(int maxdepth, int maxsize, int waittime) {
    searchSet = true;
    max_depth = maxdepth;
    max_size = maxsize;
    wait_time = waittime;
}

// Return max depth
int pop_od::getSearchMaxDepth() const {
    return max_depth;
}

// Return max requst size
int pop_od::getSearchMaxReqSize() const {
    return max_size;
}

// Return discovery request waiting time
int pop_od::getSearchWaitTime() const {
    return wait_time;
}

// Return true if the od.search is set
bool pop_od::isSearchSet() const {
    return searchSet;
}
// End of add

// Used to specify if the used protocol is secure
void pop_od::secure(int /*foo*/) {
    secureSet = true;
}

bool pop_od::isSecureSet() const {
    return secureSet;
}

// Methods used by Runtime system
void pop_od::getPower(float& require, float& min) const {
    require = mflops;
    min = min_mflops;
}

void pop_od::getMemory(float& require, float& min) const {
    require = ram;
    min = min_ram;
}

void pop_od::getBandwidth(float& require, float& min) const {
    require = net;
    min = min_net;
}

float pop_od::getWallTime() const {
    return time;
}

bool pop_od::getIsManual() const {
    return isManual;
}

#ifdef OD_DISCONNECT
void pop_od::getCheckConnection(int& my_time_alive, int& my_time_control) const {
    my_time_alive = time_alive;
    my_time_control = time_control;
}
bool pop_od::getCheckConnection() const {
    int time_alive;
    int time_control;
    getCheckConnection(time_alive, time_control);
    if (time_alive != -1 && time_control != -1) {
        return true;
    }
    return false;
}
void pop_od::checkConnection(int t_a, int t_c) {
    if (t_a == -1 && t_c == -1) {
        time_alive = -1;
        time_control = -1;
    } else {
        if (t_a > 0) {
            time_alive = t_a;
        } else {
            time_alive = TIME_ALIVE;
        }
        if (t_c > 0) {
            time_control = t_c;
        } else {
            time_control = TIME_CONTROL;
        }
    }
}

void pop_od::checkConnection(bool doCheck) {
    if (doCheck) {
        checkConnection(TIME_ALIVE, TIME_CONTROL);
    }
}
#endif

pop_od& pop_od::operator=(const pop_od& od) {
    if (&od != this) {
        od.getPower(mflops, min_mflops);
        od.getMemory(ram, min_ram);
        od.getBandwidth(net, min_net);
        time = od.getWallTime();
        hostname = od.getURL();
        jobcontact = od.getJobURL();
        codefile = od.getExecutable();
        proto = od.getProtocol();
        encode = od.getEncoding();
#ifdef OD_DISCONNECT
        od.getCheckConnection(time_alive, time_control);
#endif
        runLocal(od.IsLocal());
    }
    return *this;
}

bool pop_od::IsEmpty() const {
    return (mflops < 0 && min_mflops < 0 && ram < 0 && min_ram < 0 && net < 0 && min_net < 0 && time < 0 &&
            hostname.empty() /*&& time_alive < 0 && time_control < 0*/);
}

bool pop_od::IsLocal() const {
    return isLocalJob;
}

void pop_od::setValue(const std::string& key, const std::string& val) {
    keys.emplace_back(key);
    values.emplace_back(val);
}

void pop_od::getValue(const std::string& key, std::string& val) {
    for (std::size_t i = 0; i < keys.size(); ++i) {
        auto& t1 = keys[i];
        auto& t2 = values[i];
        if (t1 == key) {
            val = t2;
            return;
        }
    }

    val = nullptr;
}

void pop_od::Serialize(pop_buffer& buf, bool pack) {
    float val[2];
    int valInt[2];
    int valSearch[3];
    std::string t;
    if (pack) {
        getPower(val[0], val[1]);
        buf.Push("power", "float", 2);
        buf.Pack(val, 2);
        buf.Pop();

        getMemory(val[0], val[1]);
        buf.Push("memory", "float", 2);
        buf.Pack(val, 2);
        buf.Pop();

        getBandwidth(val[0], val[1]);
        buf.Push("bandwidth", "float", 2);
        buf.Pack(val, 2);
        buf.Pop();

        val[0] = getWallTime();
        buf.Push("walltime", "float", 1);
        buf.Pack(val, 1);
        buf.Pop();

        valInt[0] = getIsManual();
        buf.Push("manual", "int", 1);
        buf.Pack(valInt, 1);
        buf.Pop();

        t = getCwd();
        buf.Push("cwd", "std::string", 1);
        buf.Pack(&t, 1);
        buf.Pop();

        // Added by clementval
        valSearch[0] = getSearchMaxDepth();
        valSearch[1] = getSearchMaxReqSize();
        valSearch[2] = getSearchWaitTime();
        buf.Push("search", "int", 3);
        buf.Pack(valSearch, 3);
        buf.Pop();
        // End of add

        t = getURL();
        buf.Push("url", "std::string", 1);
        buf.Pack(&t, 1);
        buf.Pop();

        t = getUser();
        buf.Push("user", "std::string", 1);
        buf.Pack(&t, 1);
        buf.Pop();

        t = getCore();
        buf.Push("core", "std::string", 1);
        buf.Pack(&t, 1);
        buf.Pop();

        t = getArch();
        buf.Push("arch", "std::string", 1);
        buf.Pack(&t, 1);
        buf.Pop();

        t = getBatch();
        buf.Push("batch", "std::string", 1);
        buf.Pack(&t, 1);
        buf.Pop();

        t = getJobURL();
        buf.Push("joburl", "std::string", 1);
        buf.Pack(&t, 1);
        buf.Pop();

        t = getExecutable();
        buf.Push("executable", "std::string", 1);
        buf.Pack(&t, 1);
        buf.Pop();

        t = getPlatforms();
        buf.Push("platforms", "std::string", 1);
        buf.Pack(&t, 1);
        buf.Pop();

        t = getProtocol();
        buf.Push("protocol", "std::string", 1);
        buf.Pack(&t, 1);
        buf.Pop();

        t = getEncoding();
        buf.Push("encoding", "std::string", 1);
        buf.Pack(&t, 1);
        buf.Pop();

        // Pack additional attributes
        int count = keys.size();
        buf.Push("attributes", "vector", count);

        buf.Push("count", "int", 1);
        buf.Pack(&count, 1);
        buf.Pop();

        if (count) {
            for (std::size_t i = 0; i < keys.size(); ++i) {
                auto& t1 = keys[i];
                auto& t2 = values[i];

                buf.Push("element", "std::string", 2);

                buf.Push("key", "std::string", 1);
                buf.Pack(&t1, 1);
                buf.Pop();

                buf.Push("value", "std::string", 1);
                buf.Pack(&t2, 1);
                buf.Pop();

                buf.Pop();  // element
            }
        }

        buf.Pop();  // vector
#ifdef OD_DISCONNECT
        getCheckConnection(valInt[0], valInt[1]);
        buf.Push("checkConnection", "int", 2);
        buf.Pack(valInt, 2);
        buf.Pop();
#endif
    } else {
        buf.Push("power", "float", 2);
        buf.UnPack(val, 2);
        buf.Pop();
        power(val[0], val[1]);

        buf.Push("memory", "float", 2);
        buf.UnPack(val, 2);
        buf.Pop();
        memory(val[0], val[1]);

        buf.Push("bandwidth", "float", 2);
        buf.UnPack(val, 2);
        buf.Pop();
        bandwidth(val[0], val[1]);

        buf.Push("walltime", "float", 1);
        buf.UnPack(val, 1);
        buf.Pop();
        walltime(val[0]);

        buf.Push("manual", "int", 1);
        buf.UnPack(valInt, 1);
        buf.Pop();
        valInt[0] = isManual;

        buf.Push("cwd", "std::string", 1);
        buf.UnPack(&cwd, 1);
        buf.Pop();

        // Added by clementval
        buf.Push("search", "int", 3);
        buf.UnPack(valSearch, 3);
        buf.Pop();
        search(valSearch[0], valSearch[1], valSearch[2]);
        // End of add

        buf.Push("url", "std::string", 1);
        buf.UnPack(&hostname, 1);
        buf.Pop();
        // url(t);

        buf.Push("user", "std::string", 1);
        buf.UnPack(&hostuser, 1);
        buf.Pop();

        buf.Push("core", "std::string", 1);
        buf.UnPack(&hostcore, 1);
        buf.Pop();

        buf.Push("arch", "std::string", 1);
        buf.UnPack(&hostarch, 1);
        buf.Pop();

        buf.Push("batch", "std::string", 1);
        buf.UnPack(&batchSystem, 1);
        buf.Pop();

        buf.Push("joburl", "std::string", 1);
        buf.UnPack(&t, 1);
        buf.Pop();
        joburl(t);

        buf.Push("executable", "std::string", 1);
        buf.UnPack(&t, 1);
        buf.Pop();
        executable(t);

        buf.Push("platforms", "std::string", 1);
        buf.UnPack(&t, 1);
        buf.Pop();
        setPlatforms(t);

        buf.Push("protocol", "std::string", 1);
        buf.UnPack(&t, 1);
        buf.Pop();
        protocol(t);

        buf.Push("encoding", "std::string", 1);
        buf.UnPack(&t, 1);
        buf.Pop();
        encoding(t);

        // Unpack additional attributes
        int count = 0;
        buf.Push("attributes", "vector", count);

        buf.Push("count", "int", 1);
        buf.UnPack(&count, 1);
        buf.Pop();

        keys.clear();
        values.clear();

        for (std::size_t i = 0; i < static_cast<std::size_t>(count); i++) {
            std::string t1, t2;
            buf.Push("element", "std::string", 2);

            buf.Push("key", "std::string", 1);
            buf.UnPack(&t1, 1);
            buf.Pop();

            buf.Push("value", "std::string", 1);
            buf.UnPack(&t2, 1);
            buf.Pop();

            buf.Pop();  // element

            setValue(t1, t2);
        }

        buf.Pop();  // vector

#ifdef OD_DISCONNECT
        buf.Push("checkConnection", "int", 2);
        buf.UnPack(valInt, 2);
        buf.Pop();
        checkConnection(valInt[0], valInt[1]);
#endif
    }
}
