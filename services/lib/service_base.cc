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

#include "pop_interface.h"
#include "pop_broker.h"

#include "service_base.ph"
#include "objectmonitor.ph"

#include <strings.h>

pop_service_base::pop_service_base(const std::string& challenge)
    : mychallenge(challenge), appservice(pop_system::appservice) {
    daemonMode = false;
}

pop_service_base::pop_service_base() : appservice(pop_system::appservice) {
    daemonMode = false;
}

// Switch to the daemon mode...
void pop_service_base::Start() {
    while (GetRefCount() > 1) {
        DecRef();
    }
    daemonMode = true;

    if (!pop_system::appservice.IsEmpty()) {
        pop_accesspoint myself = GetAccessPoint();
        try {
            ObjectMonitor tmp(pop_system::appservice);
            tmp.UnManageObject(myself);
            pop_system::appservice.SetAccessString("");
        } catch (std::exception& e) {
            LOG_WARNING("Failed to unregister the service from ObjectMonitor: %s", e.what());
        }
    }
}

void pop_service_base::Start(const std::string& challenge) {
    if ((mychallenge == challenge) || mychallenge.empty()) {
        while (GetRefCount() > 1) {
            DecRef();
        }
        mychallenge = challenge;
        Start();
    }
}

bool pop_service_base::Stop(const std::string& challenge) {
    if (mychallenge == challenge || mychallenge.empty()) {
        daemonMode = false;
        //      while (DecRef()>0);
        return true;
    }
    return false;
}

// Redefine behaviors of parallel object creation/destruction...
int pop_service_base::AddRef() {
    if (daemonMode) {
        return 1;
    }
    return pop_object::AddRef();
}

int pop_service_base::DecRef() {
    if (daemonMode) {
        return 1;
    }
    return pop_object::DecRef();
}
bool pop_service_base::CanKill() {
    if (daemonMode) {
        return false;
    }
    return pop_object::CanKill();
}

JobCoreService::JobCoreService(const std::string& challenge) : pop_service_base(challenge) {
}

/*
int JobCoreService::CreateObject(const pop_accesspoint &localservice, const std::string &objname, const pop_od &od, int
howmany, pop_accesspoint *objcontacts)
{
  return POPC_JOBSERVICE_FAIL;
}
*/
