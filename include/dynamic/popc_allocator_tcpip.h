/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief
 *
 *
 */

#ifndef POPC_ALLOCATOR_TCPIP_H_
#define POPC_ALLOCATOR_TCPIP_H_

#include "popc_allocator.h"

#include "paroc_od.h"
#include "paroc_string.h"

/* POPC_ALLOCATOR_TCPIP_LOCAL_H_ */
class POPC_Allocator_tcpip_local : public POPC_Allocator {
public:
    POPC_Allocator_tcpip_local();
    ~POPC_Allocator_tcpip_local();
    virtual POPString allocate(POPString& objectname, paroc_od& od);
    virtual paroc_combox* allocate_group(POPString& objectname, paroc_od& od, int nb);
    virtual POPC_Protocol get_protocol() {
        return POPC_Allocator::TCPIP;
    };
    virtual POPC_AllocationMechanism get_mechanism() {
        return POPC_Allocator::LOCAL;
    };

};

/* POPC_ALLOCATOR_TCPIP_SSH_H_ */
class POPC_Allocator_tcpip_ssh : public POPC_Allocator {
public:
    POPC_Allocator_tcpip_ssh();
    ~POPC_Allocator_tcpip_ssh();
    virtual POPString allocate(POPString& objectname, paroc_od& od);
    virtual paroc_combox* allocate_group(POPString& objectname, paroc_od& od, int nb);
    virtual POPC_Protocol get_protocol() {
        return POPC_Allocator::TCPIP;
    };
    virtual POPC_AllocationMechanism get_mechanism() {
        return POPC_Allocator::SSH;
    };
};

#endif /* POPC_ALLOCATOR_TCPIP_H_ */
