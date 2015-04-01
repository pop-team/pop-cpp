/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief Declaration of the base class POPC_AllocatorFactory. The allocator factory allows to provide the right allocator for
 *        parallel object allocation depending the lower layer (SSH, MPI, POP-C++ MPI Interconnector ...).
 *
 *
 */

#include "popc_allocator_tcpip.h"

#include "paroc_system.h"
#include "paroc_exception.h"
#include "paroc_combox.h"
#include "paroc_combox_factory.h"
#include "paroc_broker.h"
#include "paroc_utils.h"
#include "paroc_interface.h"

#include "codemgr.ph"
#include "batchmgr.ph"
#include "appservice.ph"
#define ALLOC_TIMEOUT 60

/**
 * Allocate a single object by using the TCP/IP protocol with a local allocation mechanism
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @return A string representation of the access-point
 */
std::string socket_allocator_service::allocate(std::string& objectname, paroc_od& od) {
    paroc_accesspoint jobcontact, objectaddress, remotejobcontact;

    //Exec using JobMgr interface...
    std::string platforms = od.getPlatforms();

    if(!platforms.empty()) {
        CodeMgr mgr(paroc_system::appservice);
        if(mgr.GetPlatform(objectname, platforms)<=0) {
            paroc_exception::paroc_throw(OBJECT_EXECUTABLE_NOTFOUND, "No platform found", objectname.c_str());
        }
        od.setPlatforms(platforms);
    }
    //Global Resource management system --> Find a resource.

    std::string joburl = od.getJobURL();


    if(!joburl.empty()) {
        jobcontact.SetAccessString(joburl.c_str());
    } else {
        jobcontact=paroc_system::jobservice;
    }

    if(jobcontact.IsEmpty()) {
        char str[1024];
        sprintf(str,"%s:%d", paroc_system::GetHost().c_str(),DEFAULTPORT);
        jobcontact.SetAccessString(str);
    }

    try {
        JobCoreService resources(jobcontact);
        int ret;
        /*if (paroc_interface::batchindex==0 && paroc_interface::batchsize>1)
        {
                if (batchaccesspoint!=NULL) delete [] batchaccesspoint;
                batchaccesspoint=new paroc_accesspoint[paroc_interface::batchsize];
        //TODO put an other array than batchaccesspoint
                ret=resources.CreateObject(paroc_system::appservice,objectname,od, paroc_interface::batchsize,  batchaccesspoint, paroc_interface::batchsize, batchaccesspoint);
                if (ret==0) objectaddress=batchaccesspoint[paroc_interface::batchindex++];
        }
        else{*/
        ret=resources.CreateObject(paroc_system::appservice,objectname,od, 1,  &objectaddress, 1, &remotejobcontact);
        //}

        if(ret!=0) {
            paroc_exception::paroc_throw(ret,objectname,"CreateObject returned error code");
        }

    } catch(std::exception & e) {
        LOG_ERROR("Cannot create object via POP-C++ Job Manager: %s", e.what());
        paroc_exception::paroc_throw(POPC_JOBSERVICE_FAIL,"Cannot create object via POP-C++ job service",e.what());
    }

    return objectaddress.GetAccessString();
}

/**
 * Allocate a single object by using the TCP/IP protocol with a local allocation mechanism
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @param nb          The number of object to allocate in the group
 * @return A pointer to a single combox connected with the group
 */
paroc_combox* socket_allocator_service::allocate_group(std::string& objectname, paroc_od& od, int nb) {

    /* Allocation process here */

    return NULL;
}
