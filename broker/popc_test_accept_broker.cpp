#include <mpi.h>

/**
 * This process is in charge of accepting new 
 */
 
int main(int argc, char **argv)
{
  MPI::Init();  
  
  int POPC_COMBOX_MPI_NEW_CONNECTION_TAG = 1000;
  int POPC_COMBOX_MPI_KILL_TAG = 1001;  
  int POPC_COMBOX_MPI_NO_MEANING_TAG = 2000;

  printf("Start test-accept-broker\n");  
  
  printf("try to connect to %s\n", argv[1]);  
  MPI::Intercomm connection = MPI::COMM_WORLD.Connect(argv[1], MPI_INFO_NULL, 0);
  printf("Connect\n");  
  connection.Send(&POPC_COMBOX_MPI_NO_MEANING_TAG, 1, MPI_INT, 0, POPC_COMBOX_MPI_NO_MEANING_TAG);
  printf("Send no meaning data\n");    
  connection.Disconnect();
  printf("Disconnect\n");    
  MPI::Finalize();
}