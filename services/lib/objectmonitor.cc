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
    LOG_ERROR( "LOCAL SERVICE SIGNAL %d!!!!",sig);
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
}

ObjectMonitor::~ObjectMonitor() {
}

void ObjectMonitor::KillAll() {
    mutex {
        LOG_INFO("POP-C++: End of all parallel objects is being processed");
        for(auto& t : objects){
            try {
                paroc_interface tmp(t);
                tmp.Kill();
            } catch(...) {
                LOG_WARNING("Exception while killing objects");
            }
        }
        objects.clear();
    }
}

int ObjectMonitor::CheckObjects() {
    mutex {
        bool active=false;

        auto pos = objects.begin();
        while(pos!=objects.end()) {
            auto old=pos;
            auto &t=*pos++;
            try {
                paroc_interface test(t);
                if(!active && test.ObjectActive()) {
                    active=true;
                }
                if(!active && !isActive) {
                    test.DecRef();
                }
            } catch(...) {
                LOG_WARNING("Exception in CheckObjects");
                pos = objects.erase(old);
            }
        }
        isActive=active;

        LOG_DEBUG("Check parallel objects....%ld object alive", objects.size());
        return objects.size();
    }
}

void ObjectMonitor::ManageObject(paroc_accesspoint &p) {
    mutex {
        const char *newstr=p.GetAccessString();
        for(auto& t : objects){
            if(paroc_utils::isEqual(t.GetAccessString(), newstr)) {
                return;
            }
        }
        objects.push_back(p);
    }
}

void ObjectMonitor::UnManageObject(paroc_accesspoint &p) {
    mutex {
        const char *newstr=p.GetAccessString();
        auto pos=objects.begin();
        while(pos!=objects.end()) {
            if(paroc_utils::isEqual(pos->GetAccessString(), newstr)) {
                pos = objects.erase(pos);
                return;
            }
            ++pos;
        }
        LOG_WARNING("ObjectMonitor: unable to unmanage ap: %s",newstr);
    }
}
