/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/11/30
 * @brief 
 *
 *
 */
 
#include "popc_group_broker.h"
#include "popc_connection_mpi.h"
#include <mpi.h>
 
/**
 * Base constructor
 */
POPC_GroupBroker::POPC_GroupBroker() 
{ 
}
 
/**
 * Base destructor
 */
POPC_GroupBroker::~POPC_GroupBroker()
{
  delete _popc_internal_object;
}

/**
 * Send a response to the end-point
 * @param buffer      Buffer filled with the response header and data load
 * @param connection  Connection used to send the response. 
 * @param collective  Set to TRUE if the response results from a collective call. FALSE if the response results from a 
 *                    non-collective call.
 */
void POPC_GroupBroker::popc_send_response(paroc_buffer& buffer, paroc_connection* connection, bool collective)
{
  MPI::Intercomm comm = dynamic_cast<POPC_MPIConnection*>(connection)->get_communicator();
  int world_size = comm.Get_size();
  int rank = comm.Get_rank(); 
  
  if((collective && rank == (world_size-1)) || !collective) {
    int data[2];
    data[0] = 16; 
    data[1] = 0; 
    comm.Send(&data, 2, MPI_INT, 0, 0); 
    int length = buffer.get_size(); 
    comm.Send(&length, 1, MPI_INT, 0, 1); 
    char* load = buffer.get_load();
    comm.Send(load, length, MPI_CHAR, 0, 2); 
  }
}

/**
 * Add information about methods from child class. 
 * @param classuid  Unique identifier of the class 
 * @param methods   Pointer containing the methods to be added
 * @param size      Number of methods to add
 */
void POPC_GroupBroker::add_method_info(unsigned classuid, popc_method_info *methods, int size)
{
	if (size <= 0 || methods == NULL) {
	  return;
	}
	popc_class_info &t = methodnames.AddHeadNew();
	t.cid = classuid;
	t.methods = methods;
	t.sz = size;
}

/**
 * Invoke a specific method
 * @param method            Information on the method to call (ID, semantics ...)
 * @param _popc_buffer      Buffer containing parameter and used to send the result of the call
 * @param _popc_connection  Connection used to send the result of the call
 */
bool POPC_GroupBroker::invoke(unsigned method[3], paroc_buffer &_popc_buffer, paroc_connection *_popc_connection)
{
  printf("Invoke in base broker\n"); 
}
