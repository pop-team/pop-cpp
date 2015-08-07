/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief Declaration of the base class pop_allocatorFactory. The allocator factory allows to provide the right
 *allocator for
 *        parallel object allocation depending the lower layer (SSH, MPI, POP-C++ MPI Interconnector ...).
 *
 *
 */

#include "pop_allocator_tcpip.h"

#include "pop_system.h"
#include "pop_exception.h"
#include "pop_combox.h"
#include "pop_combox_factory.h"
#include "pop_broker.h"
#include "pop_utils.h"
#include "pop_interface.h"

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
std::string socket_allocator_service::allocate(const std::string& objectname, const pop_od& od) {
    pop_accesspoint jobcontact, objectaddress, remotejobcontact;

    // Exec using JobMgr interface...
    std::string platforms = od.getPlatforms();

    if (!platforms.empty()) {
        CodeMgr mgr(pop_system::appservice);
        if (mgr.GetPlatform(objectname, platforms) <= 0) {
            pop_exception::pop_throw(OBJECT_EXECUTABLE_NOTFOUND, "No platform found", objectname.c_str());
        }
        // od.setPlatforms(platforms);
    }
    // Global Resource management system --> Find a resource.

    std::string joburl = od.getJobURL();

    if (!joburl.empty()) {
        jobcontact.SetAccessString(joburl.c_str());
    } else {
        jobcontact = pop_system::jobservice;
    }

    if (jobcontact.IsEmpty()) {
        char str[1024];
        sprintf(str, "%s:%d", pop_system::GetHost().c_str(), DEFAULTPORT);
        jobcontact.SetAccessString(str);
    }

    try {
        JobCoreService resources(jobcontact);
        int ret =
            resources.CreateObject(pop_system::appservice, objectname, od, 1, &objectaddress, 1, &remotejobcontact);

        if (ret != 0) {
            pop_exception::pop_throw(ret, objectname, "CreateObject returned error code");
        }

    } catch (std::exception& e) {
        LOG_ERROR("Cannot create object via POP-C++ Job Manager: %s", e.what());
        pop_exception::pop_throw(POP_JOBSERVICE_FAIL, "Cannot create object via POP-C++ job service", e.what());
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
pop_combox* socket_allocator_service::allocate_group(const std::string& objectname, const pop_od& od, int nb) {
    /* Allocation process here */

    return NULL;
}
