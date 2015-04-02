/**
 * File : codemgr.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of the code manager service
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "codemgr.ph"
#include "popc_logger.h"

CodeMgr::CodeMgr(const std::string &challenge): paroc_service_base(challenge) {
    //Nothing else to init
}

CodeMgr::~CodeMgr() {
    LOG_DEBUG("Now destroy CodeMgr");
}

void CodeMgr::RegisterCode(const std::string &objname, const std::string &platform, const std::string &codefile) {
    if(objname.size() >= CODE_MAX_STRING_SIZE || platform.size() >= CODE_MAX_STRING_SIZE || codefile.size() >= CODE_MAX_STRING_SIZE) {
        LOG_ERROR( "Could not register code, information longer than %i: %i %i %i",
                    CODE_MAX_STRING_SIZE, objname.size(), platform.size(), codefile.size());
        LOG_ERROR( "RegisterCode %s %s %s", objname.c_str(), platform.c_str(), codefile.c_str());

        //TODO: Throw exception
        return;
    }

    auto n=info.size();
    int i;
    for(i=0; i<n; i++){
        if(objname==info[i].objname) {
            break;
        }
    }

    codedb *element;
    if(i<n) {
        element=&(info[i]);
    } else {
        info.resize(n+1);
        element=&(info[n]);
        element->objname=objname.c_str();
    }

    n=element->platform.size();
    for(i=0; i<n; i++){
        if(platform==element->platform[i].platform) {
            break;
        }
    }

    if(i<n) {
        LOG_DEBUG("Changing (%s, %s) -> %s",element->objname.c_str(),element->platform[i].platform.c_str(),codefile.c_str());
        element->platform[i].codefile=codefile;
    } else {
        element->platform.resize(n+1);
        element->platform[n].codefile=codefile.c_str();
        element->platform[n].platform=platform;
    }
}

int CodeMgr::QueryCode(const std::string &objname, const std::string &platform, std::string &codefile) {
    codefile="";
    auto n=info.size();
    codedb *element;

    int i;
    for(i=0; i<n; i++){
        if(objname==info[i].objname) {
            break;
        }
    }

    if(i>=n) {
        LOG_WARNING("Found no code file for %s", objname.c_str());
        return 0;
    }

    element=&(info[i]);
    n=element->platform.size();
    for(i=0; i<n; i++){
        if(pop_utils::MatchWildcard(platform,element->platform[i].platform)) {
            break;
        }
    }

    if(i>=n) {
        LOG_WARNING("Found no code file for %s", platform.c_str());
        return 0;
    }

    codefile=element->platform[i].codefile;

    return 1;
}

int CodeMgr::GetPlatform(const std::string &objname, std::string &platform) {
    platform=nullptr;
    auto n=info.size();

    int i;
    for(i=0; i<n; i++){
        if(objname==info[i].objname) {
            break;
        }
    }

    if(i>=n) {
        return 0;
    }

    auto& element=info[i];
    n=element.platform.size();
    for(i=0; i<n; i++) {
        platform+=element.platform[i].platform;
        if(i<n-1) {
            platform+=" ";
        }
    }

    return n;
}
