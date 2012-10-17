#include <mpi.h>

/**
 * This process is in charge of accepting new 
 */
 
int main(int argc, char **argv)
{
  MPI::Init();  
  
  int POPC_COMBOX_MPI_NEW_CONNECTION_TAG = 1000;
  int POPC_COMBOX_MPI_KILL_TAG = 1001;  

  //printf("Start accept-broker\n");  
  int connection = 0;
  
  MPI::Intercomm parent = MPI::COMM_WORLD.Get_parent();  
  
  // Create communicator for communication between broker process and accepting new communication  
  MPI::Intracomm broker_intracomm = MPI::COMM_WORLD.Dup();
  MPI::Intracomm self = MPI::COMM_WORLD.Split(1, 0);

//  printf("Acceptbroker - Communicators created: broker:size/rank(%d/%d), self:size/rank(%d/%d)\n", broker_intracomm.Get_size(), broker_intracomm.Get_rank(), self.Get_size(), self.Get_rank());

  // Open the port to receive new connection
  char port_name[MPI_MAX_PORT_NAME];
  MPI::Open_port(MPI_INFO_NULL, port_name);


  int length = strlen(port_name);
  broker_intracomm.Send(&length, 1, MPI_INT, 0, 0);
  broker_intracomm.Send(&port_name, length, MPI_CHAR, 0, 1);
  

  bool active = true;
  MPI::Status status;
  int data = 0;
  while (active) {
    //printf("AB: wait for a connection %s\n", port_name);
    // Waiting for a new connection from an interface
    MPI::Intercomm new_connection = self.Accept(port_name, MPI_INFO_NULL, 0);
    //printf("AB: new connection\n");    
    new_connection.Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, status); 
    if(status.Get_tag() == POPC_COMBOX_MPI_KILL_TAG){
      active = false; 
      new_connection.Disconnect();
      //broker_intracomm.Send(&data, 1, MPI_INT, 0, POPC_COMBOX_MPI_KILL_TAG);
    } else if (status.Get_tag() == POPC_COMBOX_MPI_NEW_CONNECTION_TAG){
      broker_intracomm.Send(&data, 1, MPI_INT, 0, POPC_COMBOX_MPI_NEW_CONNECTION_TAG);
      new_connection.Disconnect();
    } else {
      new_connection.Disconnect();
    }
  }

  //printf("AB: ending\n");        
  MPI::Close_port(port_name); 
  printf("AB: port closed\n");        
  MPI::Finalize();
}