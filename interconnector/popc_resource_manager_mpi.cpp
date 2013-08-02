/**
 *
 */
 
#include <mpi.h>

 
int main(int argc, char **argv)
{
  int current_free_rank; 
  int max_rank;
  if(!MPI::Is_initialized()){
 	  // Init MPI for multithread support
  	int required_support = MPI_THREAD_SERIALIZED; // Required multiple thread support to allow multiple connection to an object
	  int provided_support = MPI::Init_thread(required_support); 
  }	 
  
  max_rank = MPI::COMM_WORLD.Get_size();
  current_free_rank = MPI::COMM_WORLD.Get_rank()+1;
  
  bool active = true;
  while (active){
    MPI::Status status;
    int cmd;
    MPI::COMM_WORLD.Recv(&cmd, 1, MPI_INT, MPI_ANY_SOURCE, 10, status);
    switch (cmd) {
      case 1: {
        int length;
        MPI::COMM_WORLD.Recv(&length, 1, MPI_INT, status.Get_source(), 11);
        char* classname = new char[length+1];
        MPI::COMM_WORLD.Recv(classname, length, MPI_CHAR, status.Get_source(), 12);
        classname[length] = '\0';
        
        if(current_free_rank == max_rank)
          current_free_rank = -1;
        MPI::COMM_WORLD.Send(&current_free_rank, 1, MPI_INT, status.Get_source(), 13);
        current_free_rank++;
        }
        break;
      case 2:
        active = false;      
        break;
      default:
        printf("Unknown command\n");
    }
  }
  
  MPI::Finalize();
}