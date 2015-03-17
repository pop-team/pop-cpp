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

ObjectMonitor::ObjectMonitor(const std::string &challenge): paroc_service_base(challenge) {
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
        LOG_INFO("Kill all remaining parallel objects");
        for(auto& t : objects){
            LOG_INFO("Kill object %s", t.GetAccessString().c_str());
            try {
                paroc_interface tmp(t);
                tmp.Kill();
            } catch(std::exception& e) {
                LOG_WARNING("Exception while killing objects: %s", e.what());
            }
        }
        objects.clear();
    }
}

int ObjectMonitor::CheckObjects(bool pingObjects) {
    mutex {
        if(pingObjects){
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
                        LOG_WARNING("Object %s is already inactive", t.GetAccessString().c_str());
                        test.DecRef();
                    }
                } catch(std::exception &e) {
                    LOG_WARNING("An object might have been destroyed prematurely: exception while calling %s: %s",t.GetAccessString().c_str(),e.what());
                    pos = objects.erase(old);
                }
            }
            isActive=active;
        }

        LOG_DEBUG("Check parallel objects....%ld object alive", objects.size());
        return objects.size();
    }
}

void ObjectMonitor::ManageObject(paroc_accesspoint &p) {
    mutex {
        const std::string& newstr=p.GetAccessString();
        LOG_DEBUG("Manage object with ap %s", newstr.c_str());
        for(auto& t : objects){
            if(t.GetAccessString() == newstr) {
                LOG_WARNING("Found object with a similar ap: %s", newstr.c_str());
                return;
            }
        }
        objects.push_back(p);
    }
}

void ObjectMonitor::UnManageObject(paroc_accesspoint &p) {
    mutex {
        const std::string& newstr=p.GetAccessString();
        LOG_DEBUG("Unanage object with ap %s", newstr.c_str());
        auto pos=objects.begin();
        while(pos!=objects.end()) {
            if(pos->GetAccessString() == newstr) {
                pos = objects.erase(pos);
                return;
            }
            ++pos;
        }
        LOG_WARNING("ObjectMonitor: unable to unmanage ap: %s",newstr.c_str());
    }
}
