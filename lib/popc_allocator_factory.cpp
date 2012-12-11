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

POPC_AllocatorFactory* POPC_AllocatorFactory::instance = NULL;


POPC_AllocatorFactory::POPC_AllocatorFactory()
{
  
}

POPC_AllocatorFactory::~POPC_AllocatorFactory()
{

}

/**
 *
 */
POPC_AllocatorFactory* POPC_AllocatorFactory::get_instance()
{
  if(instance == NULL) {
    instance = new POPC_AllocatorFactory(); 
  } 
  return instance;
} 
 
POPC_Allocator* POPC_AllocatorFactory::get_allocator(POPC_Allocator::POPC_Protocol protocol, 
    POPC_Allocator::POPC_AllocationMechanism alloc_mechanism)
{
  switch (protocol) {
    case POPC_Allocator::UDS :
      {
        switch(alloc_mechanism) {
          case POPC_Allocator::INTERCONNECTOR : 
            return new POPC_Allocator_uds_interconnector();            
          default: 
            return NULL; 
        }
      } 
    default:
      return NULL;  
  }
  

}
  
