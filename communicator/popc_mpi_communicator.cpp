/**
 * POP-C++ MPI Communicator: Acts as a communication layer for POP-C++ running over computer with only MPI suppport for 
 * inter-node communication. 
 * This process is able to: 
 * - Launch the main of the POP-C++ application when it has the rank 0.
 * - Allocate object on itself or pass the allocation request to another MPI Communicator.
 * - Redirect request received by IPC to the right node. 
 * - Redirect request received by MPI to the right object.
 *
 *
 * @author Valentin Clement
 * @date 2012/10/25
 * @file popc_mpi_communicator.cpp
 */

// System include
#include <mpi.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>

// POP-C++ library include
#include "paroc_broker.h"
#include "paroc_buffer_xdr.h"
#include "popc_combox_uds.h"
#include "paroc_utils.h"



/**
 * Catch signal of exiting child
 */
void catch_child_exit(int signal_num) {
  int retval, nval;
  char buf[256];
  bzero(buf, 256);
  nval = waitpid(0, &retval, WNOHANG);  
  //sprintf(buf,"Waited on child %d which exited with code = %d\n",nval,retval);       
  write(STDOUT_FILENO, buf, 256);
}


/**
 * Receive new incoming MPI data and transmit them to the main thread
 */
void *mpireceivedthread(void *t) 
{
  int rank = MPI::COMM_WORLD.Get_rank();  
  char* tmp = new char[20];
  sprintf(tmp, "uds_%d.0", rank);
  std::string local_address(tmp);
  delete [] tmp;
  bool active = true;
  
  
  // Connect to main process by IPC
  popc_combox_uds ipcwaker;
  ipcwaker.Create(local_address.c_str(), false);
  ipcwaker.Connect(local_address.c_str());
  paroc_buffer* ipcwaker_buffer = ipcwaker.GetBufferFactory()->CreateBuffer();    
  paroc_message_header header(20, 100003, INVOKE_SYNC, "_dummyconnection");
	ipcwaker_buffer->Reset();
	ipcwaker_buffer->SetHeader(header);  
	paroc_connection* connection = ipcwaker.get_connection();	
  if (!ipcwaker_buffer->Send(ipcwaker, connection)) {
	  paroc_exception::paroc_throw_errno();
	}   
  
  // Waiting for MPI calls
  while(active) {
    int data;
    MPI::Status status;
    // Receive data
    MPI::COMM_WORLD.Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, status);
    printf("Recv data on MPI %d\n", data);
    switch (data) {
      // Receive ending command from the main MPI process. 
      case 10: 
        {
          active = false;
          if (rank != 0) {
            // signal the IPC process to stop
            paroc_message_header endheader(20, 100001, INVOKE_SYNC, "_terminate");
	          ipcwaker_buffer->Reset();
            ipcwaker_buffer->SetHeader(endheader);  
            ipcwaker_buffer->Send(ipcwaker, connection);
          }
        }
        break;
      // Unknown command ... do nothing 
      default:
        printf("Unknown tag %d\n", rank);
    }
  }
  printf("MPI thread %d ending\n", rank);
  pthread_exit(NULL);
}

/**
 *
 */
int main(int argc, char* argv[])
{
  // Initialize the local variable of the communicator
  if(!MPI::Is_initialized()){
 	  // Init MPI for multithread support
  	int required_support = MPI_THREAD_SERIALIZED; // Required multiple thread support to allow multiple connection to an object
	  int provided_support = MPI::Init_thread(required_support); 
  }	 
  
  // Catch signal when a child is exiting  
  signal(SIGCHLD, catch_child_exit);
      
  if(argc < 2) {
    printf("usage: %s -app=<app_exec>\n", argv[0]);
    MPI::Finalize();    
    return 1;
  }
  
  // Initialize local address
  int rank = MPI::COMM_WORLD.Get_rank();
  int world = MPI::COMM_WORLD.Get_size();
  char* tmp = new char[20];
  sprintf(tmp, "uds_%d.0", rank);
  std::string local_address(tmp);
  delete [] tmp;

  // Init object counter
  int next_object_id = 1;  
  
  pid_t mainpid;        // Save main pid to wait for it at the end
  pthread_t mpithread;  // MPI Receive thread
  
  if(rank == 0) {
    std::string application_arg;
    char* capp = paroc_utils::checkremove(&argc, &argv, "-app=");
    if(capp == NULL) {
      printf("usage: %s -app=<app_exec>\n", argv[0]);      
      MPI::Finalize();  
      return 1;
    } else {
      application_arg.append(capp);
      printf("App %s %d\n", argv[0], argc);
    }
    

    pid_t mainpid = fork();

    if(mainpid == 0) {
      //char* argv1[2];
      //argv1[0] = const_cast<char*>(application_arg.c_str());
      //argv1[1] = (char*)0;
      argv[0] = const_cast<char*>(application_arg.c_str());
      execv(argv[0], argv);
      perror("Execv failed");

    } else if (mainpid == -1) {
      perror("start main process");
      MPI::Finalize();
      return 1;
    }
  }
    

  // Create local combox server to accept incoming request from interface
  popc_combox_uds local;
  local.Create(local_address.c_str(), true);
  
  // Create MPI receive thread
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);  
  pthread_create(&mpithread, &attr, mpireceivedthread, NULL);
  
  // Wait for IPC request
  bool active = true;
  while (active) {
    paroc_request request;
    request.data = NULL;

    // Wait for data on the UDS
    paroc_connection* connection = local.Wait();
    if(connection == NULL) {
      // Connection is null. No data will come on this connection. Wait for another one.
      printf("Connection null\n");	  
    } else {
      // Process incoming request
      paroc_buffer_factory *buffer_factory = connection->GetBufferFactory();
	    request.data = buffer_factory->CreateBuffer();
		  if (request.data->Recv(connection)) {
  		  request.from = connection;
	  		const paroc_message_header &header = request.data->GetHeader();
  		  request.methodId[0] = header.GetClassID();
	  		request.methodId[1] = header.GetMethodID();
			    
			  // Killing the process, end of the higher-level application
		  	if(request.methodId[1] == 100001){
		  	  active = false;
          int data = 10; 		  	  
          int tag = 0; // TAG 10 = END OF THE APPLICATION		  	  
		  	  if(world > 1) {
		  	    for(int i = 1; i < world; i++) {
              // Inform other MPI communicator to end their process. 
		  	      MPI::COMM_WORLD.Isend(&data, 1, MPI_INT, i, tag);
		  	    }
          }
    	    MPI::COMM_WORLD.Isend(&data, 1, MPI_INT, 0, tag);                  
        } else if(request.methodId[1] == 100002) {  
          // Connection to this process as a router process
          
		  	  POPString real_destination;
		      request.data->Push("realdest", "POPString", 1);
         	request.data->UnPack(&real_destination, 1);
        	request.data->Pop();
         	int current_fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();      	
        } else if(request.methodId[1] == 100003) {
          // Get information from the MPI received node
          printf("Connection from MPI thread %d\n", rank);
          
                   	
        } else if(request.methodId[1] == 100000) {  
          // Allocation a new parallel object
          
          POPString objectname, codefile;
          int node;
          request.data->Push("objectname", "POPString", 1);
          request.data->UnPack(&objectname, 1);
          request.data->Pop();
          request.data->Push("codefile", "POPString", 1);
          request.data->UnPack(&codefile, 1);
          request.data->Pop();		  
		  	  request.data->Push("node", "int", 1);
          request.data->UnPack(&node, 1);
          request.data->Pop();		  
           	  	
          if (node != rank) {
            printf("Will allocate on another node %d\n", node);
            
            // Send allocation information to the destination MPI Communicator
            int objectname_length = strlen(objectname.GetString());
            int codefile_length = strlen(codefile.GetString());
            MPI::COMM_WORLD.Isend(&objectname_length, 1, MPI_INT, node, 10);
            MPI::COMM_WORLD.Isend(objectname.GetString(), 1, MPI_INT, node, 11);
            MPI::COMM_WORLD.Isend(&codefile_length, 1, MPI_INT, node, 12);
            MPI::COMM_WORLD.Isend(codefile.GetString(), 1, MPI_INT, node, 13);
            
            
            
          } 

          char* tmp = new char[15];
          snprintf(tmp, 15, "uds_%d.%d", rank, next_object_id);
          next_object_id++;
              
          popc_combox_uds receiver;
          std::string receiver_address(local_address);
          receiver_address.append("_");
          receiver_address.append(tmp);

          receiver.Create(receiver_address.c_str(), true);
              
          std::string _objectname("-object=");
          _objectname.append(objectname.GetString());
          std::string _objectaddress("-address=");
          _objectaddress.append(tmp);
          std::string objurl("uds://");
          objurl.append(tmp);
          delete [] tmp;              
          POPString objectaddress(objurl.c_str());
          std::string _receiveraddress("-callback=");
          _receiveraddress.append(receiver_address);
          char *localrank = new char[20];
          snprintf(localrank, 20, "-local_rank=%d", rank);
                  
          // Allocate the object      
          pid_t allocatepid = fork();
          if(allocatepid == 0){
            char* argv1[6];
            argv1[0] = codefile.GetString();                        // Object executable
            argv1[1] = const_cast<char*>(_objectname.c_str());      // Object name
            argv1[2] = const_cast<char*>(_objectaddress.c_str());   // Object address
            argv1[3] = const_cast<char*>(_receiveraddress.c_str()); // Address of ready call
            argv1[4] = localrank;                                   // Rank of the creator process
            argv1[5] = (char*)0;             
            execv(argv1[0], argv1);              	
          }
          paroc_request callback;
          paroc_connection* objectcallback = receiver.Wait();
          paroc_buffer_factory *buffer_factory = objectcallback->GetBufferFactory();
    	    callback.data = buffer_factory->CreateBuffer();
		      if (callback.data->Recv(receiver, objectcallback)) {
  			    callback.from = connection;
	  		    const paroc_message_header &callback_header = callback.data->GetHeader();
  		  	  callback.methodId[0] = callback_header.GetClassID();
	  		    callback.methodId[1] = callback_header.GetMethodID(); 
  		  	  if(callback.methodId[1] == 100002){
           	  request.data->Reset();		  
      	  		paroc_message_header h("_allocate");
           		request.data->SetHeader(h);
       		    request.data->Push("objectaddress", "POPString", 1);
           		request.data->Pack(&objectaddress, 1);
           		request.data->Pop();
           		request.data->Send(request.from);
	  	      } else {
              request.data->Reset();		  
      	  		paroc_message_header h("_allocate");
           		request.data->SetHeader(h);
       		    request.data->Push("objectaddress", "POPString", 1);
       		    POPString empty;
           		request.data->Pack(&empty, 1);
           		request.data->Pop();
           		request.data->Send(request.from);
	  	      }
	  	    }
   	    	callback.data->Destroy();
   	    	receiver.Close();		  	      
	  	  }
        request.data->Destroy();			  
      }
    }
  }    
      
  local.Close();
  
  if(rank == 0) {
    // Wait for the program to finish
    int status;  
    waitpid(mainpid, &status, 0);
    pthread_join(mpithread, NULL);
  }

  
  
  MPI::Finalize();
  return 0;
}

