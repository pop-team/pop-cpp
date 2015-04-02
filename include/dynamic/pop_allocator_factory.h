/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief Declaration of the class pop_allocatorFactory. The allocator factory allows to provide the right allocator for
 *        parallel object allocation depending the lower layer (SSH, MPI, POP-C++ MPI Interconnector ...).
 *
 *
 */

#ifndef POPC_ALLOCATOR_FACTORY_H_
#define POPC_ALLOCATOR_FACTORY_H_

#include "pop_allocator.h"


class pop_allocatorFactory {
private:
    pop_allocatorFactory();
    ~pop_allocatorFactory();
    static pop_allocatorFactory* instance;

public:
    static const char* PREFIX_UDS;
    static const char* PREFIX_TCP;
    static const char* PREFIX_MPI;
    static const char* PREFIX_SHM;

    static pop_allocatorFactory* get_instance();
    pop_allocator* get_allocator(pop_allocator::pop_protocol protocol,
                                  pop_allocator::pop_allocationMechanism alloc_mechanism);

};

#endif /* POPC_ALLOCATOR_FACTORY_H_ */
