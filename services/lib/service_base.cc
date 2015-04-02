/**
 * File : service_base.cc
 * Author : Tuan Anh Nguyen
 * Description : Base service class
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 */


#include <stdio.h>

#include "paroc_interface.h"
#include "paroc_broker.h"

#include "paroc_service_base.ph"
#include "objectmonitor.ph"

#include <strings.h>

paroc_service_base::paroc_service_base(const std::string &challenge):mychallenge(challenge), appservice(paroc_system::appservice) {
    daemonMode=false;
}

paroc_service_base::paroc_service_base(): appservice(paroc_system::appservice) {
    daemonMode=false;
}

//Switch to the daemon mode...
void paroc_service_base::Start() {
    while(GetRefCount()>1) {
        DecRef();
    }
    daemonMode=true;

    if(!paroc_system::appservice.IsEmpty()) {
        pop_accesspoint myself=GetAccessPoint();
        try {
            ObjectMonitor tmp(paroc_system::appservice);
            tmp.UnManageObject(myself);
            paroc_system::appservice.SetAccessString("");
        } catch(std::exception& e) {
            LOG_WARNING("Failed to unregister the service from ObjectMonitor: %s", e.what());
        }
    }
}

void paroc_service_base::Start(const std::string &challenge) {
    if((mychallenge==challenge) || mychallenge.empty()) {
        while(GetRefCount()>1) {
            DecRef();
        }
        mychallenge=challenge;
        Start();
    }

}

bool paroc_service_base::Stop(const std::string &challenge) {
    if(mychallenge==challenge || mychallenge.empty()) {
        daemonMode=false;
        //      while (DecRef()>0);
        return true;
    }
    return false;
}

//Redefine behaviors of parallel object creation/destruction...
int paroc_service_base::AddRef() {
    if(daemonMode) {
        return 1;
    }
    return paroc_object::AddRef();
}

int paroc_service_base::DecRef() {
    if(daemonMode) {
        return 1;
    }
    return paroc_object::DecRef();
}
bool paroc_service_base::CanKill() {
    if(daemonMode) {
        return false;
    }
    return paroc_object::CanKill();
}


JobCoreService::JobCoreService(const std::string &challenge): paroc_service_base(challenge) {
}

/*
int JobCoreService::CreateObject(const pop_accesspoint &localservice, const std::string &objname, const paroc_od &od, int howmany, pop_accesspoint *objcontacts)
{
  return POPC_JOBSERVICE_FAIL;
}
*/

