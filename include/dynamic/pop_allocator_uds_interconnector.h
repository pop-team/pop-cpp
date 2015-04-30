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

#ifndef POP_ALLOCATOR_UDS_INTERCONNECTOR_H_
#define POP_ALLOCATOR_UDS_INTERCONNECTOR_H_

#include "pop_allocator.h"

#include "pop_od.h"

class uds_allocator_interconnector : public pop_allocator {
public:
    virtual std::string allocate(const std::string& objectname, const pop_od& od);
    virtual pop_combox* allocate_group(const std::string& objectname, const pop_od& od, int nb);
    virtual pop_protocol get_protocol() {
        return pop_allocator::UDS;
    }
    virtual pop_allocationMechanism get_mechanism() {
        return pop_allocator::INTERCONNECTOR;
    }
};

#endif /* POPC_ALLOCATOR_UDS_INTERCONNECTOR_H_ */
