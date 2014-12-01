/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief Declaration of the class POPC_AllocatorFactory. The allocator factory allows to provide the right allocator for
 *        parallel object allocation depending the lower layer (SSH, MPI, POP-C++ MPI Interconnector ...).
 *
 *
 */

#ifndef POPC_ALLOCATOR_FACTORY_H_
#define POPC_ALLOCATOR_FACTORY_H_

#include "popc_allocator.h"


class POPC_AllocatorFactory {
private:
    POPC_AllocatorFactory();
    ~POPC_AllocatorFactory();
    static POPC_AllocatorFactory* instance;

public:
    static POPC_AllocatorFactory* get_instance();
    POPC_Allocator* get_allocator(POPC_Allocator::POPC_Protocol protocol,
                                  POPC_Allocator::POPC_AllocationMechanism alloc_mechanism);

};

#endif /* POPC_ALLOCATOR_FACTORY_H_ */
