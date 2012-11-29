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
  if(!MPI::Is_initialized()) {
    int required_support = MPI_THREAD_SERIALIZED;
    int provided_support = MPI::Init_thread(required_support); 

    if(provided_support < required_support) {
      printf("POP-C++ Warning: Support of multithread in MPI is lower than required. Deadlock can block your application\n"); 
    } else {
      printf("POP-C++ XMP process started %d\n", MPI::COMM_WORLD.Get_rank());
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
	
	printf("Will create object of type=%s\n", objectname); 



  if(!MPI::Is_finalized()) {
    MPI::Finalize();
  }
  return 0; 
}
