/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief Implementation of the class pop_allocatorFactory. The allocator factory allows to provide the right allocator
 *for
 *        parallel object allocation depending the lower layer (SSH, MPI, POP-C++ MPI Interconnector ...).
 *
 *
 */

#include "pop_allocator_factory.h"
#include "pop_allocator_uds_local.h"
#include "pop_allocator_uds_interconnector.h"
#include "pop_allocator_tcpip.h"
#include "pop_allocator_mpi_pseudo.h"
#include "pop_logger.h"

const char* pop_allocatorFactory::PREFIX_UDS = "uds";
const char* pop_allocatorFactory::PREFIX_TCP = "socket";
const char* pop_allocatorFactory::PREFIX_MPI = "mpi";
const char* pop_allocatorFactory::PREFIX_SHM = "shm";

// Unique instance of the allocator factory
pop_allocatorFactory* pop_allocatorFactory::instance = nullptr;

/**
 * Allocator Factory constructor
 */
pop_allocatorFactory::pop_allocatorFactory() {
}

/**
 * Allocator Factory destructor
 */
pop_allocatorFactory::~pop_allocatorFactory() {
}

/**
 * Get a pointer to the Allocator Factory
 * @return A pointer to the unique instance of the Allocator Factory
 */
pop_allocatorFactory* pop_allocatorFactory::get_instance() {
    if (instance == nullptr) {
        instance = new pop_allocatorFactory();
    }
    return instance;
}

/**
 * Get an Allocator for a specific allocation
 * @param protocol        Protocol used for the allocation procedure
 * @param alloc_mechanism Mechanism used to allocate the parallel object
 * @return A pointer to an Allocator
 */
pop_allocator* pop_allocatorFactory::get_allocator(pop_allocator::pop_protocol protocol,
                                                   pop_allocator::pop_allocationMechanism alloc_mechanism) {
    switch (protocol) {
        // Allocation over UDS socket
        case pop_allocator::UDS: {
            switch (alloc_mechanism) {
                case pop_allocator::LOCAL:
                    return new pop_allocator_uds_local();
                case pop_allocator::INTERCONNECTOR:
                    return new uds_allocator_interconnector();
                default:
                    LOG_WARNING("No allocator found");
                    return nullptr;
            }
        }
        // Allocation over TCP/IP socket
        case pop_allocator::TCPIP: {
            switch (alloc_mechanism) {
                case pop_allocator::LOCAL:
                    return new socket_allocator_local();
                case pop_allocator::SSH:
                    return new socket_allocator_service();
                default:
                    LOG_WARNING("No allocator found");
                    return nullptr;
            }
        }
        // Allocation over MPI
        case pop_allocator::MPI: {
            switch (alloc_mechanism) {
                case pop_allocator::PSEUDODYNAMIC:
                //            return new mpi_allocator_pseudo();
                default:
                    LOG_WARNING("No allocator found");
                    return nullptr;
            }
        }
        default:
            LOG_WARNING("No allocator found");
            return nullptr;
    }
}
