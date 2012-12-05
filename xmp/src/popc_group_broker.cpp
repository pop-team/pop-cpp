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
 
 
POPC_GroupBroker::POPC_GroupBroker() 
{
 
}
 
POPC_GroupBroker::~POPC_GroupBroker()
{
  delete _popc_internal_object;
}

void POPC_GroupBroker::popc_send_response(paroc_buffer& buffer, paroc_connection* connection, bool collective)
{
  MPI::Intercomm comm = dynamic_cast<POPC_MPIConnection*>(connection)->get_communicator();
  int world_size = comm.Get_size();
  int rank = comm.Get_rank(); 
  
  if(collective && rank == (world_size-1)) {
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


void POPC_GroupBroker::add_method_info(unsigned classuid, popc_method_info *methods, int sz)
{
	if (sz <= 0 || methods == NULL) return;
	popc_class_info &t = methodnames.AddHeadNew();
	t.cid = classuid;
	t.methods = methods;
	t.sz = sz;
}


bool POPC_GroupBroker::invoke(unsigned method[3], paroc_buffer &_popc_buffer, paroc_connection *_popc_connection)
{
  printf("Invoke in base broker\n"); 
}
