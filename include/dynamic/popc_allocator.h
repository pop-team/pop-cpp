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

#ifndef POPC_ALLOCATOR_H_
#define POPC_ALLOCATOR_H_

#include "paroc_od.h"
#include "pop_accesspoint.h"
#include "pop_combox.h"

class POPC_Allocator {
public:
    enum POPC_Protocol { UDS, TCPIP, MPI, SHM };
    enum POPC_AllocationMechanism { LOCAL, SSH, INTERCONNECTOR, PSEUDODYNAMIC };

    POPC_Allocator() {}
    virtual ~POPC_Allocator() {}
    virtual std::string allocate(std::string& objectname, paroc_od& od) = 0;
    virtual pop_combox* allocate_group(std::string& objectname, paroc_od& od, int nb) = 0;
    virtual POPC_Protocol get_protocol() = 0;
    virtual POPC_AllocationMechanism get_mechanism() = 0;
};

#endif /* POPC_ALLOCATOR_H_ */
