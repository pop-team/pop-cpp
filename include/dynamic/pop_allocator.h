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

#ifndef POP_ALLOCATOR_H_
#define POP_ALLOCATOR_H_

#include "pop_od.h"
#include "pop_accesspoint.h"
#include "pop_combox.h"

class pop_allocator {
public:
    enum pop_protocol { UDS, TCPIP, MPI, SHM };
    enum pop_allocationMechanism { LOCAL, SSH, INTERCONNECTOR, PSEUDODYNAMIC };

    pop_allocator() {
    }
    virtual ~pop_allocator() {
    }
    virtual std::string allocate(const std::string& objectname, const pop_od& od) = 0;
    virtual pop_combox* allocate_group(const std::string& objectname, const pop_od& od, int nb) = 0;
    virtual pop_protocol get_protocol() = 0;
    virtual pop_allocationMechanism get_mechanism() = 0;
};

#endif /* POPC_ALLOCATOR_H_ */
