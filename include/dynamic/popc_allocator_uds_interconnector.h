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

#ifndef POPC_ALLOCATOR_UDS_INTERCONNECTOR_H_
#define POPC_ALLOCATOR_UDS_INTERCONNECTOR_H_

#include "popc_allocator.h"

#include "paroc_od.h"
#include "paroc_string.h"

class POPC_Allocator_uds_interconnector : public POPC_Allocator {
public: 
  POPC_Allocator_uds_interconnector();
  ~POPC_Allocator_uds_interconnector();          
  virtual POPString allocate(POPString& objectname, paroc_od& od); 
  virtual paroc_combox* allocate_group(POPString& objectname, paroc_od& od, int nb);     
  virtual POPC_Protocol get_protocol() { return POPC_Allocator::UDS; }; 
  virtual POPC_AllocationMechanism get_mechanism() { return POPC_Allocator::INTERCONNECTOR; };  
  
};

#endif /* POPC_ALLOCATOR_UDS_INTERCONNECTOR_H_ */
