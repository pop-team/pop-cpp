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
  


  
  
  
  
  printf("XMP parallel object rank %d %d\n", rank, communicator.Get_remote_size());     

  int length; 
  
  communicator.Recv(&length, 1, MPI_INT, 0, 0); 
  printf("%d recv %d\n", MPI::COMM_WORLD.Get_rank(), length);

  int data2; 
  communicator.Recv(&data2, 1, MPI_INT, 0, 0); 
  printf("%d recv %d\n", MPI::COMM_WORLD.Get_rank(), data2); 

//  char* load = new char[length]; 
//  communicator.Recv(load, length, MPI_CHAR, 0, 1);
//  int data; 
//  communicator.Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, rank);
//  printf("XMP parallel object received %d\n", data);     
  

  


	
  printf("XMP Object: %d Will create object of type=%s\n", rank, objectname); 
  
  



  if(!MPI::Is_finalized()) {
    MPI::Finalize();
  }
  return 0; 
}
