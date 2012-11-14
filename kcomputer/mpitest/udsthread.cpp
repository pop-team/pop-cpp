//#include <mpi.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/un.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#include "paroc_buffer_xdr.h"
#include "popc_combox_uds.h"
#include "paroc_broker.h"

void *mpireceivedthread(void *t) 
{
  printf("Forked process started\n");
  std::string local_address("uds_0.0");

  popc_combox_uds ipcwaker;
  ipcwaker.Create(local_address.c_str(), false);
  if(!ipcwaker.Connect(local_address.c_str())) {
    perror("MPI received thread cannot connect to MPI interconnector"); 
    pthread_exit(NULL); 
    return NULL; 
  }
  
  
  paroc_buffer* ipcwaker_buffer = ipcwaker.GetBufferFactory()->CreateBuffer();    
  paroc_message_header header(20, 200003, INVOKE_SYNC, "_dummyconnection");
  ipcwaker_buffer->Reset();
  ipcwaker_buffer->SetHeader(header);
  paroc_connection* connection = ipcwaker.get_connection();	
  if(connection == NULL) {
    printf("MPI received thread connection is NULL\n"); 
    perror("MPI received thread connection is NULL"); 
    pthread_exit(NULL); 
    return NULL;
  } 
  if (!ipcwaker_buffer->Send(ipcwaker, connection)) {
    perror("MPI received thread failed to initialize"); 
    pthread_exit(NULL); 
    return NULL;
  }
 
 
  pthread_exit(NULL);  
  return NULL; 
}


int main(int argc, char* argv[])
{
 /* MPI::Init();
  int rank = MPI::COMM_WORLD.Get_rank();
  int world = MPI::COMM_WORLD.Get_size(); 
  */
  //printf("Process %d, world size = %d\n", rank, world); 
  printf("Process started\n");
  /*if(rank == 0) {
    for (int i=0; i < 100; i++) {
      MPI::COMM_WORLD.Send(&i, 1, MPI_INT, 1, 0); 
    }
  } else if(rank == 1) {*/
  
  std::string local_address("uds_0.0");

  /*pthread_mutex_lock(&mpi_mutex);
  pthread_cond_wait(&mpi_condition, &mpi_mutex);
  pthread_mutex_unlock(&mpi_mutex);      */
  // Connect to main process by IPC
  popc_combox_uds local;
  if(!local.Create(local_address.c_str(), true)){
    printf("POP-C++ Error: MPI Interconnector failed to initialize\n");
    return 1; 
  }  
    
    pthread_t mpithread1, mpithread2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);      
    pthread_create(&mpithread1, &attr, mpireceivedthread, NULL);
    pthread_create(&mpithread2, &attr, mpireceivedthread, NULL);


  /*  pid_t allocatepid = fork();
    if(allocatepid == 0) {
      char* argv1[3];
      argv1[0] = (char*)"forkedprocess";
      argv1[1] = "1";
      argv1[2] = (char*)0;   
      execv(argv1[0], argv1);              	
      perror("Execv failed");
    } 
    
    allocatepid = fork();
    if(allocatepid == 0) {
      char* argv1[3];
      argv1[0] = (char*)"forkedprocess";
      argv1[1] = "2";
      argv1[2] = (char*)0;             
      execv(argv1[0], argv1);              	
      perror("Execv failed");
    } */
        
    bool active = true; 
    int cnt = 0;
    while(active) {
      paroc_request request;
      request.data = NULL;   
      local.SetTimeout(-1); 
      paroc_connection* connection = local.Wait();
      paroc_buffer_factory *buffer_factory = connection->GetBufferFactory();
	    request.data = buffer_factory->CreateBuffer();
		  if (request.data->Recv(connection)) {
  		  request.from = connection;
	  		const paroc_message_header &header = request.data->GetHeader();
  		  request.methodId[0] = header.GetClassID();
		  }
      
      printf("Recv requ %d\n", request.methodId[1]);
      cnt++; 
      if(cnt == 2) 
        active = false;
      request.data->Destroy();
    }
    
    

    local.Close();
    
  
    /*for (int i=0; i < 100; i++) {
      int data; 
      MPI::COMM_WORLD.Recv(&data, 1, MPI_INT, 0, 0); 
    } */ 
    
    pthread_join(mpithread1, NULL);
    pthread_join(mpithread2, NULL);
    pthread_attr_destroy(&attr);      
    
  /*}
  
  MPI::Finalize();
  */
}

