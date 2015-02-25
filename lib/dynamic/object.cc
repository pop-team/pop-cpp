/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of the parallel object-object-side
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_ObjectCore instead of paroc_object
 */

#include "paroc_object.h"
#include "paroc_mutex.h"
#include "paroc_interface.h"
#include "paroc_event.h"
#include "paroc_broker.h"
#include "paroc_system.h"

#ifndef POP_PSEUDO
#include "objectmonitor.ph"
#endif

int paroc_object::argc=0;
char **paroc_object::argv=NULL;

paroc_object::paroc_object() {
    refcount=1;
    if(!paroc_system::appservice.IsEmpty()) {
        paroc_accesspoint myself=GetAccessPoint();
#ifndef POP_PSEUDO
        try {
            ObjectMonitor tmp(paroc_system::appservice);
            tmp.ManageObject(myself);
        } catch(std::exception &e) {
            LOG_WARNING("Can not register %s@%s to ObjectMonitor service: %s",(const char *)paroc_broker::classname, myself.GetAccessString(), e.what());
        }
#endif
    }

}

paroc_object::~paroc_object() {
#ifndef POP_PSEUDO
    if(!paroc_system::appservice.IsEmpty()) {
        paroc_accesspoint myself=GetAccessPoint();
        try {
            ObjectMonitor tmp(paroc_system::appservice);
            tmp.UnManageObject(myself);
        } catch(std::exception &e) {
            // Did not find the object to unregister V1.3.1m: suppress error mess. V3.0 log as debug
            LOG_DEBUG("Can not unregister %s@%s from ObjectMonitor service: %s",(const char *)paroc_broker::classname, myself.GetAccessString(), e.what());
        }
    }
#endif
}

const paroc_accesspoint & paroc_object::GetAccessPoint() const {
    return paroc_broker::accesspoint;
}

/**
 * Get the accesspoint of the parallel object and set the _noaddref variavle to TRUE
 */
const paroc_accesspoint & paroc_object::GetAccessPointForThis() {
    paroc_broker::accesspoint.SetNoAddRef();
    return paroc_broker::accesspoint;
}

int paroc_object::GetRefCount() {
    paroc_mutex_locker t(lock);
    return refcount;
}

int paroc_object::AddRef() {
    paroc_mutex_locker t(lock);
    refcount++;
    return refcount;
}

int paroc_object::DecRef() {
    paroc_mutex_locker t(lock);
    refcount--;
    return refcount;
}

bool  paroc_object::CanKill() {
    return  true;
}

int paroc_object::eventwait(int event, int timeout) {
    return _paroc_events.WaitEvent(event, timeout);
}
void paroc_object::eventraise(int event) {
    _paroc_events.PostEvent(event);
}
