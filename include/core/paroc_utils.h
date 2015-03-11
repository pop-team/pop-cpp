/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief utilities used by the runtime
 *
 *
 * UPDATES:
 * Author Date        Description
 * PK     2011/02/25  Add definition of POPGetHost
 */

#ifndef POPC_UTILS_H
#define POPC_UTILS_H
#include "paroc_string.h"
#include "popc_logger.h"

#define SSH_TUNNEL_ERROR 65280
#define SSH_PORT_MOD 16383
#define SSH_PORT_FIRST 49152
#define SSH_MAX_ATTEMPT 10

class AppCoreService;

class paroc_utils {
public:

    static char *checkremove(int *argc, char ***argv, const char *opt);
    static bool check_remove(int *argc, char ***argv, const char *opt);
    static bool isEqual(const char *s1, const char *s2);
    static bool isncaseEqual(const std::string& s1, const std::string& s2);
    static bool MatchWildcard(const std::string& str, const std::string& wildcard);
    static void FindAbsolutePath(const char *fname, char *abspath);
    static void Assert(bool a);


#ifdef _POPC_
    static bool SameContact(const std::string& contact1, const std::string& contact2);
    static bool IsRemoteDest(const char *dest);
    static int GetPortFromURL(const char *url);
    static const char *GetIPFromURL(const char *url);
    static const char* GetCurrentUser();
    static paroc_string MakeContact(const char *host, int port);
    static bool isIPv4Address(POPString value);
    static bool isValidName(POPString value);
    static float benchmark_power();

    static int InitCodeService(char *fileconf, AppCoreService *service);

#endif

};
typedef paroc_utils POPUtils;

#ifdef _POPC_
int rprintf(const char *format,...);

#ifndef _POPC_RUNTIME_
#define printf rprintf
#define POPGetHost() (const char*)POPSystem::GetHost()
#endif

#endif

#endif
