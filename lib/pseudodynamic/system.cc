/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief System stuffs and declarations used by the runtime.
 *
 *
 * Modifications :
 * Authors    Date      Comment
 * L.Winkler  2008-2009   for version 1.3
 * P.Kuonen   02/2010     (GetHost, getIp, add POPC_Host_Name, ...) for version 1.3m (see comments 1.3m)
 * P.Kuonen   02/2011      define default IP for version 1.3.1m (see comments 1.3.1m)
 * P.Kuonen   25/3/2011    Cosmetic changes
 */

/*
  Deeply need refactoring:
    POPC_System instead of pop_system
 */
#include "popc_intface.h"

//#include <stdio.h>
//#include <netdb.h>
//#include <unistd.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <ctype.h>

#include "pop_system_mpi.h"
#include "pop_buffer_factory_finder.h"
#include "pop_utils.h"
#include "pop_combox_factory.h"
#include "pop_exception.h"
#include "pop_od.h"

pop_accesspoint pop_system::appservice;
pop_accesspoint pop_system::jobservice;
int pop_system::pop_current_local_address;

int pop_system::popc_local_mpi_communicator_rank;

int pop_system_mpi::current_free_process;
bool pop_system_mpi::is_remote_object_process;
bool pop_system_mpi::mpi_has_to_take_lock;
pop_condition pop_system_mpi::mpi_unlock_wait_cond;
pop_condition pop_system_mpi::mpi_go_wait_cond;

std::string pop_system::platform;
std::ostringstream pop_system::_popc_cout;

// V1.3m
std::string pop_system::pop_hostname;
#define LOCALHOST "localhost"
// End modif

AppCoreService* pop_system::mgr = nullptr;
std::string pop_system::challenge;

pop_system::pop_system() {
    // Call the singleton to precreate the objects
    pop_combox_factory::get_instance();
    pop_buffer_factory_finder::get_instance();

    char* tmp = getenv("POPC_PLATFORM");
    if (tmp != nullptr) {
        platform = tmp;
    } else {
        char str[128];
#ifndef POP_ARCH
        char arch[64], sysname[64];
#ifndef __WIN32__
// popc_sysinfo(SI_SYSNAME,sysname,64);
// popc_sysinfo(SI_ARCHITECTURE,arch,64);
#endif
        sprintf(str, "%s-%s", sysname, arch);
#else
#ifndef __WIN32__
        strcpy(str, POP_ARCH);
#else
        strcpy(str, "win32");
#endif
#endif
        platform = str;
    }
    pop_hostname = std::string("");
}

pop_system::~pop_system() {
    // Release the singletons
    pop_combox_factory::release_instance();
    pop_buffer_factory_finder::release_instance();
}

// V1.3m
// Try to determine the Host Name of the machine and put it in POPC_Host_Name
// IF env. variable POPC_HOST is defined THEN use POPC_HOST
// ELSE IF try to use gethostname() and possibly env. variable POPC_DOMAIN
// ELSE call GetIP()
//----------------------------------------------------------------------------
std::string pop_system::GetHost() {
    if (pop_hostname.empty()) {
        char str[128];
        char* t = getenv("POPC_HOST");
        if (t == nullptr || *t == 0) {
            popc_gethostname(str, 127);
            if (strchr(str, '.') == nullptr || strstr(str, ".local\0") != nullptr) {
                int len = strlen(str);
                char* domain = getenv("POPC_DOMAIN");
                if (domain != nullptr && domain != 0) {
                    str[len] = '.';
                    strcpy(str + len + 1, domain);
                    pop_hostname = str;
                } else {  //(domain!=nullptr && domain!=0)
                    pop_hostname = GetIP();
                }
            } else {  //(strchr(str,'.')==nullptr || strstr(str,".local\0")!=nullptr)
                pop_hostname = str;
            }
        } else {  //(t==nullptr || *t==0)
            pop_hostname = t;
        }
    }
    LOG_DEBUG("GetHost returns %s", pop_hostname.c_str());
    return pop_hostname;
}

// V1.3m
// Try to determine the IP address of the machine.
// If fail return the localhost IP = LOCALHOST
//------------------------------------------------------
std::string pop_system::GetIP() {
#ifndef __WIN32__
    std::string iface, ip;
    char* tmp;
    ip = std::string(LOCALHOST);

    tmp = getenv("POPC_IP");
    if (tmp != nullptr) {  // Env. variable POPC_IP is defined
        ip = tmp;
    } else {  // Env. variable POPC_IP is not defined
        tmp = getenv("POPC_IFACE");
        if (tmp != nullptr) {  // Env. Variable POP_IFACE is defined
            iface = tmp;       // Try to determine IP from network interface name
            if (!(GetIPFromInterface(iface, ip))) {
                // Not found
                setenv("POPC_IP", LOCALHOST, 0);  // V1.3.1m define LOCALHOST as IP
                LOG_WARNING("Cannot find an IP for interface %s, using '%s' as IP address.", iface.c_str(), LOCALHOST);
            }
        } else {  // Env. Variable POP_IFACE is not defined
            iface = GetDefaultInterface();
            if (!iface.empty()) {
                if (!(GetIPFromInterface(iface, ip))) {
                    setenv("POPC_IP", LOCALHOST, 0);  // V1.3.1m define LOCALHOST as IP
                    LOG_WARNING("host IP not found, using '%s' as IP address.", LOCALHOST);
                }
            } else {
                setenv("POPC_IP", LOCALHOST, 0);  // V1.3.1m define LOCALHOST as IP
                LOG_WARNING("no default network interface found, using '%s' as IP address.", LOCALHOST);
            }
        }
    }
    return ip;
#else
    char ipaddr[64];
    char hostname[256];
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (popc_gethostname(hostname, 256) != 0) {
        return std::string("127.0.0.1");
    }
    struct hostent* hp = gethostbyname(hostname);
    unsigned ip = (unsigned(127) << 24) + 1;

    if (hp == nullptr || *(hp->h_addr_list) == nullptr) {
        return std::string("127.0.0.1");
    }

    char** p = hp->h_addr_list;
    while (*p != nullptr) {
        memcpy(&ip, *p, sizeof(unsigned));
        ip = ntohl(ip);
        if (ip != (unsigned(127) << 24) + 1) {
            break;
        }
        p++;
    }
    int n1, n2, n3, n4;
    n1 = ip & 255;
    ip = ip >> 8;

    n2 = ip & 255;
    ip = ip >> 8;

    n3 = ip & 255;
    ip = ip >> 8;

    n4 = ip & 255;
    sprintf(ipaddr, "%d.%d.%d.%d", n4, n3, n2, n1);
    WSACleanup();
    return ipaddr;
#endif
}

int pop_system::GetIP(const char* hostname, int* iplist, int listsize) {
    /* This method should normally not be used to return more than one ip*/
    assert(listsize == 1);
#ifdef __WIN32__
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    struct hostent* hp;
    int n;
    char** p;
    int addr;
    if ((int)(addr = popc_inet_addr(hostname)) == -1) {
        hp = gethostbyname(hostname);
    } else {
        if (listsize > 0) {
            *iplist = popc_ntohl(addr);
            return 1;
        }
        return 0;
    }
    if (hp == nullptr) {
        return 0;
    }
    n = 0;
    for (p = hp->h_addr_list; *p != 0 && n < listsize; p++) {
        memcpy(iplist, *p, sizeof(int));
        *iplist = popc_ntohl(*iplist);
        if (*iplist == (int(127) << 24) + 1) {
            continue;
        }
        n++;
        iplist++;
    }
    popc_endhostent();
    if (n == 0) {
        n = 1;
    }
#ifdef __WIN32__
    WSACleanup();
#endif
    return n;
}

int pop_system::GetIP(int* iplist, int listsize) {
    assert(listsize == 1); /* This method cannot return more than one ip*/
    char* parocip = popc_strdup(GetIP().c_str());
    int n;
    int addr;
    std::vector<std::string> tokens;
    popc_tokenize_r(tokens, parocip, " \n\r\t");
    n = 0;
    for (auto tok : tokens) {
        if (n >= listsize)
            break;
        if ((int)(addr = popc_inet_addr(tok.c_str())) != -1) {
            *iplist = popc_ntohl(addr);
            iplist++;
            n++;
        }
    }
    return n;
}

std::string pop_system::GetDefaultInterface() {
    char buff[1024], iface[16], net_addr[128];
    // char flags[64], mask_addr[128], gate_addr[128];
    // int iflags, metric, refcnt, use, mss, window, irtt;
    bool found = false;
    FILE* fp = fopen("/proc/net/route", "r");

    if (fp != nullptr) {  // else
        while (fgets(buff, 1023, fp) && !found) {
            // num = sscanf(buff, "%16s %128s %128s %X %d %d %d %128s %d %d %d",
            //       iface, net_addr, gate_addr, &iflags, &refcnt, &use, &metric, mask_addr, &mss, &window, &irtt);
            int num = sscanf(buff, "%16s %128s", iface, net_addr);
            if (num < 2) {
                pop_exception::pop_throw("GetDefaultInterface failed: num < 2");
            }
            // LOG_DEBUG("iface %s, net_addr %s, gate_addr %s, iflags %X, &refcnt %d, &use %d, &metric %d, mask_addr %s,
            // &mss %d, &window %d, &irtt %d\n\n",iface, net_addr, gate_addr,iflags, refcnt, use, metric, mask_addr,
            // mss, window, irtt);

            if (!strcmp(net_addr, "00000000")) {
                LOG_DEBUG("Default gateway : %s", iface);
                found = true;
            }
        }
        fclose(fp);
    }
    if (!found) {
        iface[0] = '\0';  // if not found iface = ""
    }
    return std::string(iface);
}

// TODO LW: Should probably be in intface
bool pop_system::GetIPFromInterface(std::string& iface, std::string& str_ip) {
#ifndef __WIN32__
    (void)iface;
    (void)str_ip;
    /*struct ifaddrs *addrs, *iap;
    struct sockaddr_in *sa;
    char str_ip_local[32];

    getifaddrs(&addrs);

    LOG_DEBUG("Looking for interface: %s --->",iface.c_str());
    for(iap = addrs; iap != nullptr; iap = iap->ifa_next) {
        LOG_DEBUG("name=%s, addr=%p, flag=%d (%d), familly=%d (%d)",iap->ifa_name, iap->ifa_addr, iap->ifa_flags,
    IFF_UP, iap->ifa_addr->sa_family, AF_INET);
      if ( iap->ifa_addr &&
           (iap->ifa_flags & IFF_UP) &&
           (iap->ifa_addr->sa_family == AF_INET) &&
                !strcmp(iap->ifa_name, iface.c_str())) {
        sa = (struct sockaddr_in *)(iap->ifa_addr);
        inet_ntop(iap->ifa_addr->sa_family,
                  (void *)&(sa->sin_addr),
                  str_ip_local,
                  sizeof(str_ip_local) );
            LOG_DEBUG("The IP of interface %s is %s",iap->ifa_name,str_ip_local);
        str_ip=str_ip_local;
        freeifaddrs(addrs);
        return true;
      }
    }
    freeifaddrs(addrs);*/
    return false;
#else
    (void)iface;
    (void)str_ip;
#endif
}

/**
 * Initialize the base system to run a POP-C++ application
 * @param   argc    Number of arguments (passed from the main)
 * @param   argv    Arguments (passed from the main)
 * @return  TRUE if the system is initialized. FALSE in any others cases.
 */
bool pop_system::Initialize(int* argc, char*** argv) {
    // Get access point address of the Job Manager
    const char* info = pop_utils::checkremove(argc, argv, "-jobservice=");
    if (info == nullptr) {
        LOG_ERROR("missing -jobservice argument");
        return false;
    }
    pop_system::jobservice.SetAccessString(info);
    pop_system::jobservice.SetAsService();

    // Get path of the application service executable
    const char* codeser = pop_utils::checkremove(argc, argv, "-appservicecode=");
    // const char *proxy=pop_utils::checkremove(argc,argv,"-proxy=");

    // Check if need to run on local node only
    if (pop_utils::checkremove(argc, argv, "-runlocal")) {
        pop_od::defaultLocalJob = true;
    }

    // Get application service contact address
    const char* appcontact = pop_utils::checkremove(argc, argv, "-appservicecontact=");

    if (codeser == nullptr && appcontact == nullptr) {
        LOG_ERROR("missing -appservicecontact=... or -appservicecode=... argument");
        return false;
    }
    try {
        if (appcontact == nullptr) {
            char url[1024];
            strcpy(url, codeser);

        } else {
            challenge = "";
            pop_accesspoint app;
            app.SetAccessString(appcontact);
            app.SetAsService();
        }
        // pop_system::appservice=mgr->GetAccessPoint();
        pop_system::appservice.SetAsService();
    } catch (std::exception& e) {
        LOG_WARNING("Exception occurs in pop_system::Initialize: %s", e.what());
        Finalize(false);
        return false;
    }

    char* codeconf = pop_utils::checkremove(argc, argv, "-codeconf=");
    (void)codeconf;  // Added this to avoid warning

    LOG_DEBUG_IF(codeconf == NULL, "No code config file");

    /*if (codeconf!=NULL && !pop_utils::InitCodeService(codeconf,mgr))
    {
    return false;
    }
    else return true; */

    LOG_DEBUG("SYSTEM: Init code service");
    // bool ret = !(codeconf != NULL && !pop_utils::InitCodeService(codeconf,mgr));
    LOG_DEBUG("SYSTEM: Init code service done");
    return false;
}

void pop_system::Finalize(bool /*normalExit*/) {
}

/*AppCoreService *pop_system::CreateAppCoreService(char *codelocation)
{
    // Create challenge string
    srand(time(nullptr));
    char tmp[256];

    for(int i=0; i<255; i++) {
        tmp[i]=(char)(1+254.0*rand()/(RAND_MAX+1.0) );
    }
    tmp[255]='\0';
    challenge=tmp;

    return new AppCoreService(challenge, false, codelocation);
}*/

void pop_system::processor_set(int cpu) {
    (void)cpu;
#ifndef __APPLE__
// Use glibc to set cpu affinity
/*if (cpu < 0) {
    LOG_WARNING("Cannot set processor to %d<0", cpu);
    exit(EXIT_FAILURE);
}
if(cpu >= CPU_SETSIZE) {
    LOG_WARNING("Cannot set processor to %d while CPU_SETSIZE=%d", cpu, CPU_SETSIZE);
    exit(EXIT_FAILURE);
}

cpu_set_t cpu_set;
CPU_ZERO(&cpu_set);
CPU_SET(cpu, &cpu_set);
if(sched_setaffinity(0, sizeof(cpu_set), &cpu_set) == -1) {
    LOG_WARNING("Cannot set processor to %d (cpu_set %p)", cpu,(void *)&cpu_set);
    exit(EXIT_FAILURE);
}

cpu_set_t cpu_get;
CPU_ZERO(&cpu_get);
if(sched_getaffinity(0, sizeof(cpu_get), &cpu_get) == -1) {
    LOG_WARNING("Unable to sched_getaffinity to (cpu_get) %p", (void *)&cpu_get);
    exit(EXIT_FAILURE);
}

if(memcmp(&cpu_get, &cpu_set, sizeof(cpu_set_t))) {
    LOG_WARNING("Unable to run on cpu %d", cpu);
    exit(EXIT_FAILURE);
}
#else
// Apple thread API
*/

#endif
}
