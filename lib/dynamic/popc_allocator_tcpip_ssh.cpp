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

#include "popc_allocator_tcpip.h"

#include "paroc_system.h"
#include "paroc_exception.h"
#include "paroc_combox.h"
#include "paroc_combox_factory.h"
#include "paroc_broker.h"
#include "include/pseudodynamic/paroc_system.h"
#include "include/pseudodynamic/paroc_interface.h"

#define ALLOC_TIMEOUT 60
/**
 * Allocator over TCP/IP with local mechanism constructor
 */ 
POPC_Allocator_tcpip_ssh::POPC_Allocator_tcpip_ssh()
{
}

/**
 * Allocator over TCP/IP with local mechanism destrcutor
 */ 
POPC_Allocator_tcpip_ssh::~POPC_Allocator_tcpip_ssh()
{
}

/**
 * Allocate a single object by using the TCP/IP protocol with a local allocation mechanism
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @return A string representation of the access-point
 */
POPString POPC_Allocator_tcpip_ssh::allocate(POPString& objectname, paroc_od& od)
{
        POPString objectaddress;
        
        /* Allocation here */
        return objectaddress;  
}

/**
 * Allocate a single object by using the TCP/IP protocol with a local allocation mechanism
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @param nb          The number of object to allocate in the group
 * @return A pointer to a single combox connected with the group
 */
paroc_combox* POPC_Allocator_tcpip_ssh::allocate_group(POPString& objectname, paroc_od& od, int nb)
{

  /* Allocation process here */  
  
  return NULL; 
}
