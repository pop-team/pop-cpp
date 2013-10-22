/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief Implementation of the class POPC_AllocatorFactory. The allocator factory allows to provide the right allocator for 
 *        parallel object allocation depending the lower layer (SSH, MPI, POP-C++ MPI Interconnector ...). 
 *
 *
 */
 
#include "popc_allocator_factory.h"
#include "popc_allocator_uds_interconnector.h"
#include "popc_allocator_tcpip.h"
#include "popc_allocator_mpi_pseudo.h"


// Unique instance of the allocator factory
POPC_AllocatorFactory* POPC_AllocatorFactory::instance = NULL;


/**
 * Allocator Factory constructor
 */
POPC_AllocatorFactory::POPC_AllocatorFactory()
{
}

/**
 * Allocator Factory destructor
 */
POPC_AllocatorFactory::~POPC_AllocatorFactory()
{
}

/**
 * Get a pointer to the Allocator Factory
 * @return A pointer to the unique instance of the Allocator Factory
 */
POPC_AllocatorFactory* POPC_AllocatorFactory::get_instance()
{
  if(instance == NULL) {
    instance = new POPC_AllocatorFactory(); 
  } 
  return instance;
} 
 
/**
 * Get an Allocator for a specific allocation
 * @param protocol        Protocol used for the allocation procedure
 * @param alloc_mechanism Mechanism used to allocate the parallel object
 * @return A pointer to an Allocator
 */
POPC_Allocator* POPC_AllocatorFactory::get_allocator(POPC_Allocator::POPC_Protocol protocol, 
    POPC_Allocator::POPC_AllocationMechanism alloc_mechanism)
{
  switch (protocol) {
    // Allocation over UDS socket
    case POPC_Allocator::UDS :
      {
        switch(alloc_mechanism) {
          case POPC_Allocator::INTERCONNECTOR : 
            return new POPC_Allocator_uds_interconnector();            
          default: 
            return NULL; 
        }
      }
    // Allocation over TCP/IP socket
    case POPC_Allocator::TCPIP : 
      {
        switch(alloc_mechanism) {
          case POPC_Allocator::LOCAL : 
            return new POPC_Allocator_tcpip_local();
            case POPC_Allocator::SSH :
                return new POPC_Allocator_tcpip_ssh();
          default: 
            return NULL; 
        }
      } 
    // Allocation over MPI
    case POPC_Allocator::MPI : 
      {
        switch(alloc_mechanism) {
          case POPC_Allocator::PSEUDODYNAMIC : 
//            return new POPC_Allocator_mpi_pseudo();            
          default: 
            return NULL; 
        }
      }       
    default:
      return NULL;  
  }
}
  
