/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: utilities used by the runtime
 */


#ifndef POPC_UTILS_H
#define POPC_UTILS_H
#include "paroc_string.h"

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
	static paroc_string MakeContact(const char *host, int port);

	static float benchmark_power();

	static int InitCodeService(char *fileconf, AppCoreService *service);

#endif

};
typedef paroc_utils POPUtils;

#ifdef _POPC_
int rprintf(const char *format,...);

#ifndef _POPC_RUNTIME_
#define printf rprintf
#endif

#endif

#endif
