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
#include "pop_mutex.h"
#include "pop_interface.h"
#include "pop_event.h"
#include "pop_broker.h"
#include "pop_system.h"

#ifndef POP_PSEUDO
#include "objectmonitor.ph"
#endif

int paroc_object::argc=0;
char **paroc_object::argv=NULL;

paroc_object::paroc_object() {
    refcount=1;
    if(!pop_system::appservice.IsEmpty()) {
        pop_accesspoint myself=GetAccessPoint();
#ifndef POP_PSEUDO
        try {
            ObjectMonitor tmp(pop_system::appservice);
            tmp.ManageObject(myself);
        } catch(std::exception &e) {
            LOG_WARNING("Can not register %s@%s to ObjectMonitor service: %s",pop_broker::classname.c_str(), myself.GetAccessString().c_str(), e.what());
        }
#endif
    }

}

paroc_object::~paroc_object() {
#ifndef POP_PSEUDO
    if(!pop_system::appservice.IsEmpty()) {
        pop_accesspoint myself=GetAccessPoint();
        try {
            ObjectMonitor tmp(pop_system::appservice);
            tmp.UnManageObject(myself);
        } catch(std::exception &e) {
            // Did not find the object to unregister V1.3.1m: suppress error mess. V3.0 log as debug
            LOG_DEBUG("Can not unregister %s@%s from ObjectMonitor service: %s",pop_broker::classname.c_str(), myself.GetAccessString().c_str(), e.what());
        }
    }
#endif
}

const pop_accesspoint & paroc_object::GetAccessPoint() const {
    return pop_broker::accesspoint;
}

/**
 * Get the accesspoint of the parallel object and set the _noaddref variavle to TRUE
 */
const pop_accesspoint & paroc_object::GetAccessPointForThis() {
    pop_broker::accesspoint.SetNoAddRef();
    return pop_broker::accesspoint;
}

int paroc_object::GetRefCount() {
    pop_mutex_locker t(lock);
    return refcount;
}

int paroc_object::AddRef() {
    pop_mutex_locker t(lock);
    refcount++;
    return refcount;
}

int paroc_object::DecRef() {
    pop_mutex_locker t(lock);
    refcount--;
    return refcount;
}

bool  paroc_object::CanKill() {
    return  true;
}

int paroc_object::eventwait(int event, int timeout) {
    return _pop_events.WaitEvent(event, timeout);
}
void paroc_object::eventraise(int event) {
    _pop_events.PostEvent(event);
}
