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

#include "popc_allocator_mpi_pseudo.h"

#include "paroc_system.h"
#include "paroc_exception.h"
#include "paroc_combox.h"
#include "paroc_combox_factory.h"
#include "paroc_broker.h"

/**
 * Allocator over MPI with pseudo-dynamic allocation mechanism constructor
 */
POPC_Allocator_mpi_pseudo::POPC_Allocator_mpi_pseudo()
{
}

/**
 * Allocator over MPI with pseudo-dynamic allocation mechanism destructor
 */
POPC_Allocator_mpi_pseudo::~POPC_Allocator_mpi_pseudo()
{
}

/**
 * Allocate single object with a pseudo-dynamic allocation mechanism
 * @param objectname  Name of the class to instantiate the object
 * @param od          Object description for the allocation process
 * @return A POPString object representing the access-point of the allocated parallel object.
 */
POPString POPC_Allocator_mpi_pseudo::allocate(POPString& /*objectname*/, paroc_od& /*od*/)
{
  POPString objectaddress;

  /* TODO Allocation process here */

  return objectaddress;
}

/**
 * Allocate parallel object groupwith a pseudo-dynamic allocation mechanism
 * @param objectname  Name of the class to instantiate the object
 * @param od          Object description for the allocation process
 * @param nb          Number of objects to allocate
 * @return A pointer to a combox or an array of combox connected with the group
 */
paroc_combox* POPC_Allocator_mpi_pseudo::allocate_group(POPString& /*objectname*/, paroc_od& /*od*/, int /*nb*/)
{
  /* TODO Allocation process here */

  return NULL;
}
