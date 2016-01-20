/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
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

#ifndef POP_UTILS_H
#define POP_UTILS_H

#include "pop_logger.h"
#include "pop_buffer.h"

#define SSH_TUNNEL_ERROR 65280
#define SSH_PORT_MOD 16383
#define SSH_PORT_FIRST 49152
#define SSH_MAX_ATTEMPT 10

typedef std::string POPString;

class AppCoreService;

class pop_utils {
public:
    static char* checkremove(int* argc, char*** argv, const char* opt);
    static bool check_remove(int* argc, char*** argv, const char* opt);
    static bool isEqual(const char* s1, const char* s2);
    static bool isncaseEqual(const std::string& s1, const std::string& s2);
    static bool MatchWildcard(const std::string& str, const std::string& wildcard);
    static std::string FindAbsolutePath(const std::string& fname);
    static void Assert(bool a);

#ifdef _POP_
    static bool SameContact(const std::string& contact1, const std::string& contact2);
    static bool IsRemoteDest(const char* dest);
    static int GetPortFromURL(const char* url);
    static const char* GetIPFromURL(const char* url);
    static const char* GetCurrentUser();
    static std::string MakeContact(const char* host, int port);
    static bool isIPv4Address(std::string value);
    static bool isValidName(std::string value);
    static float benchmark_power();

    static int InitCodeService(char* fileconf, AppCoreService* service);

#endif
};
typedef pop_utils POPUtils;

#ifdef _POP_
int rprintf(const char* format, ...);

#ifndef _POP_RUNTIME_
#define printf rprintf
#define POPGetHost() (const char*) POPSystem::GetHost()
#endif

#endif

template<typename Buffer>
void pop_prepare_response(Buffer* buffer, const char* name){
    pop_message_header header(name);
    header.SetRequestID(buffer->GetHeader().GetRequestID());

    buffer->Reset();
    buffer->SetHeader(header);
}

template<typename Buffer>
void pop_prepare_response(Buffer* buffer, int classid, int methodid, const char* name){
    pop_message_header header(name);
    header.SetClassID(classid);
    header.SetMethodID(methodid);
    header.SetRequestID(buffer->GetHeader().GetRequestID());

    buffer->Reset();
    buffer->SetHeader(header);
}

#endif
