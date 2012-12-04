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

}

void POPC_GroupBroker::popc_send_response(paroc_buffer& buffer, paroc_connection* connection, bool collective)
{
  MPI::Intercomm comm = dynamic_cast<POPC_MPIConnection*>(connection)->get_communicator();
  int world_size = comm.Get_size();
  int rank = comm.Get_rank(); 
  
  if(collective && rank == 0) {
    printf("I'm sending a response\n"); 
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
