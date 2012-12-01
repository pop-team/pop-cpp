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
#include "paroc_buffer_xdr.h"


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
  
    paroc_buffer_xdr* buffer = new paroc_buffer_xdr();
    buffer->load(load, data_length);
  
    const paroc_message_header &header = buffer->GetHeader();
    
    
    printf("Class ID = %d, Type = %d, Method ID = %d, Semantics = %d\n", header.GetClassID(), header.GetType(), header.GetMethodID(), header.GetSemantics()); 
    
    
    
    // Receive DecRef - Means and of the process for a parallel object group.
    if (header.GetMethodID() == 2) {
      active = false; 
    }
  }

  if(!MPI::Is_finalized()) {
    MPI::Finalize();
  }
  return 0; 
}
