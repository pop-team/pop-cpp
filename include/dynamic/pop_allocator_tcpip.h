/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief
 *
 * Modifications:
 * - Rename pop_allocator_tcpip_ssh to _service for clarity
 */

#ifndef POPC_ALLOCATOR_TCPIP_H_
#define POPC_ALLOCATOR_TCPIP_H_

#include "pop_allocator.h"

#include "pop_od.h"

/* POPC_ALLOCATOR_TCPIP_LOCAL_H_ */
class socket_allocator_local : public pop_allocator {
public:
    virtual std::string allocate(std::string& objectname, pop_od& od);   // TODO LW: Params must be const
    virtual pop_combox* allocate_group(std::string& objectname, pop_od& od, int nb);
    virtual pop_protocol get_protocol() {
        return pop_allocator::TCPIP;
    }
    virtual pop_allocationMechanism get_mechanism() {
        return pop_allocator::LOCAL;
    }

};

/* POPC_ALLOCATOR_TCPIP_SERVICE_H_ */
class socket_allocator_service : public pop_allocator {
public:
    virtual std::string allocate(std::string& objectname, pop_od& od);
    virtual pop_combox* allocate_group(std::string& objectname, pop_od& od, int nb);
    virtual pop_protocol get_protocol() {
        return pop_allocator::TCPIP;
    }
    virtual pop_allocationMechanism get_mechanism() {
        return pop_allocator::SSH;
    }
};

#endif /* POPC_ALLOCATOR_TCPIP_H_ */
