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

CodeMgr::CodeMgr(const POPString &challenge): paroc_service_base(challenge) {
    //Nothing else to init
}

CodeMgr::~CodeMgr() {
    LOG_DEBUG("Now destroy CodeMgr");
}

void CodeMgr::RegisterCode(const POPString &objname, const POPString &platform, const POPString &codefile) {
    if(objname.Length() >= CODE_MAX_STRING_SIZE || platform.Length() >= CODE_MAX_STRING_SIZE || codefile.Length() >= CODE_MAX_STRING_SIZE) {
        LOG_ERROR( "Could not register code, information longer than %i: %i %i %i",
                    CODE_MAX_STRING_SIZE, objname.Length(), platform.Length(), codefile.Length());
        LOG_ERROR( "RegisterCode %s %s %s", objname.c_str(), platform.c_str(), codefile.c_str());

        //TODO: Throw exception
        return;
    }

    auto n=info.GetSize();
    int i;
    for(i=0; i<n; i++){
        if(paroc_utils::isEqual(objname,info[i].objname)) {
            break;
        }
    }

    codedb *element;
    if(i<n) {
        element=&(info[i]);
    } else {
        info.SetSize(n+1);
        element=&(info[n]);
        strcpy(element->objname,objname);
    }

    n=element->platform.GetSize();
    for(i=0; i<n; i++){
        if(paroc_utils::isEqual(platform,element->platform[i].platform)) {
            break;
        }
    }

    if(i<n) {
        LOG_DEBUG("Changing (%s, %s) -> %s",element->objname,element->platform[i].platform,(const char *)codefile);
        strcpy(element->platform[i].codefile,codefile);
    } else {
        element->platform.SetSize(n+1);
        strcpy(element->platform[n].codefile,codefile);
        strcpy(element->platform[n].platform,platform);
    }
}

int CodeMgr::QueryCode(const POPString &objname, const POPString &platform, POPString &codefile) {
    codefile=nullptr;
    auto n=info.GetSize();
    codedb *element;

    int i;
    for(i=0; i<n; i++){
        if(paroc_utils::isEqual(objname,info[i].objname)) {
            break;
        }
    }

    if(i>=n) {
        return 0;
    }

    element=&(info[i]);
    n=element->platform.GetSize();
    for(i=0; i<n; i++){
        if(paroc_utils::MatchWildcard(platform,element->platform[i].platform)) {
            break;
        }
    }

    if(i>=n) {
        return 0;
    }

    codefile=element->platform[i].codefile;

    return 1;
}

int CodeMgr::GetPlatform(const POPString &objname, POPString &platform) {
    platform=nullptr;
    auto n=info.GetSize();

    int i;
    for(i=0; i<n; i++){
        if(paroc_utils::isEqual(objname,info[i].objname)) {
            break;
        }
    }

    if(i>=n) {
        return 0;
    }

    auto& element=info[i];
    n=element.platform.GetSize();
    for(i=0; i<n; i++) {
        platform+=element.platform[i].platform;
        if(i<n-1) {
            platform+=" ";
        }
    }

    return n;
}
