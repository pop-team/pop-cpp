/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief Declaration of the allocator over MPI with pseudo-dynamic allocation
 *
 *
 */

#ifndef POPC_ALLOCATOR_MPI_PSEUDO_H_
#define POPC_ALLOCATOR_MPI_PSEUDO_H_

#include "popc_allocator.h"

#include "paroc_od.h"

class mpi_allocator_pseudo : public POPC_Allocator {
public:
    virtual std::string allocate(std::string& objectname, paroc_od& od);
    virtual pop_combox* allocate_group(std::string& objectname, paroc_od& od, int nb);
    virtual POPC_Protocol get_protocol() {
        return POPC_Allocator::MPI;
    }
    virtual POPC_AllocationMechanism get_mechanism() {
        return POPC_Allocator::PSEUDODYNAMIC;
    }

};

#endif /* POPC_ALLOCATOR_MPI_PSEUDO_H_ */
