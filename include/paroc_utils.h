/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: utilities used by the runtime
MODIFICATIONS: PK&VC:25.2.2011 add definition of POPGetHost
 */


#ifndef POPC_UTILS_H
#define POPC_UTILS_H
#include "paroc_string.h"

#define SSH_TUNNEL_ERROR 65280
#define SSH_PORT_MOD 16383
#define SSH_PORT_FIRST 49152
#define SSH_MAX_ATTEMPT 10

class AppCoreService;

class paroc_utils
{
public:

	static char *checkremove(int *argc, char ***argv, const char *opt);
	static bool isEqual(const char *s1, const char *s2);
	static bool isncaseEqual(const char *s1, const char *s2);
	static bool MatchWildcard(const char *str, const char *wildcard);
	static void FindAbsolutePath(const char *fname, char *abspath);
   

#ifdef _POPC_
	static bool SameContact(const char *contact1, const char *contact2);
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
