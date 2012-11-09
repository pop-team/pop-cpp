#include <mpi.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  MPI::Init();
  int rank = MPI::COMM_WORLD.Get_rank();
  int world = MPI::COMM_WORLD.Get_size(); 
  
  printf("Process %d, world size = %d\n", rank, world); 

  if(rank == 0) {
    for (int i=0; i < 100; i++) {
      MPI::COMM_WORLD.Send(&i, 1, MPI_INT, 1, 0); 
    }
  } else if(rank == 1) {
    struct sockaddr_un _sock_address;  
    socklen_t address_length;    
    int _socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    int connection_fd = 0;      
    if(_socket_fd < 0) {
      perror("socket() failed\n");
    } else {
      memset(&_sock_address, 0, sizeof(struct sockaddr_un));    
      _sock_address.sun_family = AF_UNIX;    
      strcpy(_sock_address.sun_path, "uds_0.0");  
      unlink("uds_0.0"); 
      if(bind(_socket_fd, (struct sockaddr *) &_sock_address, sizeof(struct sockaddr_un)) != 0) {
        perror("bind() failed\n");
      } else {
        if  (listen(_socket_fd, 10) != 0) {
          perror("listen() failed\n");
        }
      }
    }

    pid_t allocatepid = fork();
    if(allocatepid == 0) {
      char* argv1[2];
      argv1[0] = (char*)"forkedprocess";
      argv1[1] = (char*)0;             
      execv(argv1[0], argv1);              	
      perror("Execv failed");
    }    
    connection_fd = accept(_socket_fd, (struct sockaddr *) &_sock_address, &address_length);        
    if(connection_fd != 0) {
      char* data = new char[25];
      int nbytes = read(connection_fd, data, 25);
      printf("Receive %d - %s\n", nbytes, data); 
    }
    
    for (int i=0; i < 100; i++) {
      int data; 
      MPI::COMM_WORLD.Recv(&data, 1, MPI_INT, 0, 0); 
    }  
    
    close(_socket_fd);
    unlink("uds_0.0");     
  }
  
  MPI::Finalize();
}