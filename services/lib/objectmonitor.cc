/**
 * File : objectmonitor.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of the object monitor service
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 * P.Kuonen   25.3.2011 Messages cosmetic changes
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "popc_logger.h"
#include "objectmonitor.ph"

//static IMPLEMENT_TYPE(ObjectMonitor) *myObjMonitor=NULL;
static ObjectMonitor *myObjMonitor=NULL;

static void LocalServiceTerminate(int sig) {
    LOG_ERROR( "Local service received signal %d!!!! Kill all objects",sig);
    if(myObjMonitor!=NULL) {
        myObjMonitor->KillAll();
    }
    popc__exit(1);
}

ObjectMonitor::ObjectMonitor(const POPString &challenge): paroc_service_base(challenge) {
    myObjMonitor=this;
    popc_signal(popc_SIGINT,LocalServiceTerminate);
#ifndef __WIN32__
    popc_signal(popc_SIGKILL,LocalServiceTerminate);
#endif
    popc_signal(popc_SIGTERM,LocalServiceTerminate);
    isActive=true;
    LOG_DEBUG("Create object monitor");
}

ObjectMonitor::~ObjectMonitor() {
    LOG_DEBUG("Destroy object monitor");
}

void ObjectMonitor::KillAll() {
    mutex {
        LOG_INFO("POP-C++: End of all parallel objects is being processed");
        POSITION pos=objects.GetHeadPosition();
        while(pos!=NULL) {
            paroc_accesspoint &t=objects.GetNext(pos);
            try {
                paroc_interface tmp(t);
                tmp.Kill();
            } catch(std::exception& e) {
                LOG_WARNING("Exception while killing objects: %s", e.what());
            }
        }
        objects.RemoveAll();
    }
}

int ObjectMonitor::CheckObjects() {
    mutex {
        POSITION pos=objects.GetHeadPosition();
        bool active=false;

        while(pos!=NULL) {
            POSITION old=pos;
            paroc_accesspoint &t=objects.GetNext(pos);
            try {
                paroc_interface test(t);
                if(!active && test.ObjectActive()) {
                    active=true;
                }
                if(!active && !isActive) {
                    test.DecRef();
                }
            } catch(std::exception &e) {
                LOG_WARNING("Exception in CheckObjects: %s",e.what());
                objects.RemoveAt(old);
	    }
        }
        isActive=active;

        LOG_DEBUG("Check parallel objects....%d object alive", objects.GetCount());
        return objects.GetCount();
    }
}

void ObjectMonitor::ManageObject(paroc_accesspoint &p) {
    mutex {
        const char *newstr=p.GetAccessString();
        POSITION pos=objects.GetHeadPosition();
        while(pos!=NULL) {
            paroc_accesspoint &t=objects.GetNext(pos);
            if(paroc_utils::isEqual(t.GetAccessString(), newstr)) {
                return;
            }
        }
        LOG_DEBUG("Add object %s", newstr);
        objects.AddTail(p);
    }
}

void ObjectMonitor::UnManageObject(paroc_accesspoint &p) {
    mutex {
        const char *newstr=p.GetAccessString();
        POSITION pos=objects.GetHeadPosition();
        while(pos!=NULL) {
            POSITION old=pos;
            paroc_accesspoint &t=objects.GetNext(pos);
            if(paroc_utils::isEqual(t.GetAccessString(), newstr)) {
                objects.RemoveAt(old);
                return;
            }
        }
        LOG_WARNING("ObjectMonitor: unable to unmanage ap: %s",newstr);
    }
}
