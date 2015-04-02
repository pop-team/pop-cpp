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

#include "pop_allocator.h"

#include "pop_od.h"

class mpi_allocator_pseudo : public pop_allocator {
public:
    virtual std::string allocate(std::string& objectname, pop_od& od);
    virtual pop_combox* allocate_group(std::string& objectname, pop_od& od, int nb);
    virtual pop_protocol get_protocol() {
        return pop_allocator::MPI;
    }
    virtual pop_allocationMechanism get_mechanism() {
        return pop_allocator::PSEUDODYNAMIC;
    }

};

#endif /* POPC_ALLOCATOR_MPI_PSEUDO_H_ */
