/**
 * Entry point of POP-C++ parallel object integrating XMP support
 * 
 * @author Valentin Clement
 * @date 2012/11/29
 *
 */

#include <mpi.h>
#include <stdlib.h>

#include "paroc_utils.h"
#include "paroc_system.h"
#include "popc_buffer_xdr_mpi.h"
#include "paroc_broker.h"
#include "popc_group_broker.h"
#include "popc_group_broker_factory.h"
#include "popc_connection_mpi.h"
#include "paroc_combox.h"



int main(int argc, char* argv[]) 
{
  MPI::Intercomm communicator; 
  int rank; 
  if(paroc_utils::checkremove(&argc, &argv, "-listlong") != NULL) {
    printf("This kind of parallel object doesn't support this option.\n"); 
    return 1;
  }

  if(!MPI::Is_initialized()) {
    int required_support = MPI_THREAD_SERIALIZED;
    int provided_support = MPI::Init_thread(required_support); 
    
    communicator = MPI::COMM_WORLD.Get_parent(); 
    rank = MPI::COMM_WORLD.Get_rank();  
    
    if(provided_support < required_support) {
      printf("POP-C++ Warning: Support of multithread in MPI is lower than required. Deadlock can block your application\n"); 
    } else {
      printf("POP-C++ XMP process started %d\n", rank);
    }
  }  

  char *objectname = paroc_utils::checkremove(&argc, &argv, "-object=");
  if (objectname == NULL) {
    printf("POP-C++ Error: Object name has not been specified in the arguments!\n");
    if(!MPI::Is_finalized()) {
      MPI::Finalize();
    }
    return 1;	   
  }
  


  
  
  
  
  //printf("XMP parallel object rank %d %d\n", rank, communicator.Get_remote_size());    
   
  POPC_GroupBroker* broker = POPC_GroupBrokerFactory::create(objectname); 
  POPC_MPIConnection* mpi_connection = new POPC_MPIConnection(); 
  mpi_connection->set_communicator(communicator); 
  

  bool active = true; 
  MPI::Status status; 
  while(active) {
    int length; 
      
    MPI::Request req = communicator.Irecv(&length, 1, MPI_INT, 0, 0); 

    bool done = false; 
    while(!done) {
      done = req.Test(status); 
    }


    int data_length; 
    req = communicator.Irecv(&data_length, 1, MPI_INT, 0, 1); 
    printf("BROKER: length = %d\n", data_length); 
    done = false; 
    while(!done) {
      done = req.Test(status); 
    }    

    char* load = new char[data_length];
    req = communicator.Irecv(load, data_length, MPI_CHAR, 0, 2); 
    
    done = false; 
    while(!done) {
      done = req.Test(status); 
    }
    
    paroc_request request; 
    request.data = new popc_buffer_xdr_mpi();
    request.data->load(load, data_length);
  
    const paroc_message_header &header = request.data->GetHeader();
		request.methodId[0] = header.GetClassID();
  	request.methodId[1] = header.GetMethodID();  
    request.from = mpi_connection;
    printf("BROKER %d: Class ID = %d, Type = %d, Method ID = %d, Semantics = %d\n", rank, header.GetClassID(), header.GetType(), header.GetMethodID(), header.GetSemantics()); 

    // Receive DecRef - Means end of the process for a parallel object group.
    if (header.GetMethodID() == 2) {
      active = false; 
    } else {
      broker->invoke(request.methodId, *request.data, request.from);
    }
  }

  if(!MPI::Is_finalized()) {
    MPI::Finalize();
  }
  return 0; 
}
