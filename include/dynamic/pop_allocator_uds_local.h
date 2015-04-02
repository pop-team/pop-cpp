/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Baptiste Wicht
 * @date 2015/03/27
 * @brief
 */

#ifndef POPC_ALLOCATOR_UDS_LOCAL_H_
#define POPC_ALLOCATOR_UDS_LOCAL_H_

#include "pop_allocator.h"

#include "pop_od.h"

struct pop_allocator_uds_local : public pop_allocator {
    virtual std::string allocate(std::string& objectname, pop_od& od);   // TODO LW: Params must be const
    virtual pop_combox* allocate_group(std::string& objectname, pop_od& od, int nb);

    virtual pop_protocol get_protocol() {
        return pop_allocator::UDS;
    }
    virtual pop_allocationMechanism get_mechanism() {
        return pop_allocator::LOCAL;
    }
};

#endif
