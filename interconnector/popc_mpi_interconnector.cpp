/**
 * POP-C++ MPI Interconnector: Acts as a communication layer for POP-C++ running over computer with only MPI suppport for 
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
 * @file popc_mpi_interconnector.cpp
 */

// System include
#include <mpi.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdio.h>
#include <map>


// POP-C++ library include
#include "paroc_broker.h"
#include "paroc_buffer_xdr.h"
#include "popc_combox_uds.h"
#include "paroc_utils.h"


using namespace std;

/**
 * Catch signal of exiting child
 */
void catch_child_exit(int signal_num) {
  int retval;
  char buf[256];
  bzero(buf, 256);
  waitpid(0, &retval, WNOHANG);  
}


int rank, world;

map<int, int> incomingtag;
map<int, pair<int, int> > incomingconnection;
map<int, pair<int, int> > outgoingconnection;
map<pair<int, int>, paroc_combox*> connectionmap;

// Condition variable to serialize MPI Call
pthread_mutex_t mpi_mutex;
pthread_cond_t mpi_condition;



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

  /*pthread_mutex_lock(&mpi_mutex);
  pthread_cond_wait(&mpi_condition, &mpi_mutex);
  pthread_mutex_unlock(&mpi_mutex);      */
  // Connect to main process by IPC
  popc_combox_uds ipcwaker;
  ipcwaker.Create(local_address.c_str(), false);
  if(!ipcwaker.Connect(local_address.c_str())) {
    perror("MPI received thread cannot connect to MPI interconnector"); 
    pthread_exit(NULL); 
    return NULL; 
  }
  
  
  paroc_buffer* ipcwaker_buffer = ipcwaker.GetBufferFactory()->CreateBuffer();    
  /*paroc_message_header header(20, 200003, INVOKE_SYNC, "_dummyconnection");
  ipcwaker_buffer->Reset();
  ipcwaker_buffer->SetHeader(header);  */
  paroc_connection* connection = ipcwaker.get_connection();	
  if(connection == NULL) {
    printf("MPI received thread connection is NULL\n"); 
    perror("MPI received thread connection is NULL"); 
    pthread_exit(NULL); 
    return NULL;
  } 
  /*if (!ipcwaker_buffer->Send(ipcwaker, connection)) {
    perror("MPI received thread failed to initialize"); 
    pthread_exit(NULL); 
    return NULL;
  } */  
  
  // Waiting for MPI calls
  while(active) {
    int data;
    MPI::Status status;
    // Receive data
    //printf("Recveive thread %d wait for message\n", rank);  
    MPI::COMM_WORLD.Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 0, status);
    //printf("Recv data on MPI %d (%d)\n", rank, data);
    switch (data) {
      // Receive ending command from the main MPI process. 
      case 10: 
        {
          //printf("Recv terminate %d\n", rank);
          active = false;
          if (rank != 0) {
            // signal the IPC process to stop
            paroc_message_header endheader(20, 200001, INVOKE_SYNC, "_terminate");
	          ipcwaker_buffer->Reset();
            ipcwaker_buffer->SetHeader(endheader);  
            ipcwaker_buffer->Send(ipcwaker, connection);
//            printf("%d _term\n", rank);                       
           /* pthread_mutex_lock(&mpi_mutex);
            pthread_cond_wait(&mpi_condition, &mpi_mutex);
            pthread_mutex_unlock(&mpi_mutex);       */            
          }                      
        }
        break;
      // Allocation of new parallel object
      case 11:
        {
          printf("ALLOCATE 11\n");
          // signal the IPC thread to be ready to receive data for allocation
          paroc_message_header endheader(20, 200004, INVOKE_SYNC, "_allocation");
	        ipcwaker_buffer->Reset();
          ipcwaker_buffer->SetHeader(endheader);  
          ipcwaker_buffer->Send(ipcwaker, connection);
//          printf("%d _allocation\n", rank);                     
          pthread_mutex_lock(&mpi_mutex);
          pthread_cond_wait(&mpi_condition, &mpi_mutex);
          pthread_mutex_unlock(&mpi_mutex);
        }                
        break;
      // Wait for action to complete
      case 12:
        {

          break;
        }
      // Will receive a request from a redirection
      case 13:
        {
          //printf("MPI request %d %d\n", rank, status.Get_source());
          paroc_message_header reqheader(status.Get_source(), 200005, INVOKE_SYNC, "_request");
	        ipcwaker_buffer->Reset();
          ipcwaker_buffer->SetHeader(reqheader);  
          ipcwaker_buffer->Send(ipcwaker, connection);
//          printf("%d _request\n", rank);           
/*          pthread_mutex_lock(&mpi_mutex);
          pthread_cond_wait(&mpi_condition, &mpi_mutex);
          pthread_mutex_unlock(&mpi_mutex);          */
          break;
        }
      case 14:
        {
          paroc_message_header reqheader(status.Get_source(), 200006, INVOKE_SYNC, "_response");
	        ipcwaker_buffer->Reset();
          ipcwaker_buffer->SetHeader(reqheader);  
          ipcwaker_buffer->Send(ipcwaker, connection);
//          printf("%d _response\n", rank); 
/*          pthread_mutex_lock(&mpi_mutex);
          pthread_cond_wait(&mpi_condition, &mpi_mutex);
          pthread_mutex_unlock(&mpi_mutex);             */
          break;
        }
      // Unknown command ... do nothing 
      default:
        printf("Unknown data received on %d = %d\n", rank, data);
    }
  }
//  printf("MPI thread %d ending\n", rank);
  pthread_exit(NULL);
  return NULL;
}

/**
 * Main thread of the POP-C++ MPI Communicator. This thread is responsible for all IPC communication and MPI communication after
 * received command from the MPI receive thread. 
 * Usage: popc_mpi_communicator -app=<popc_application_main> [args]
 */
int main(int argc, char* argv[])
{
  // Initialize the local variable of the communicator
  if(!MPI::Is_initialized()){
 	  // Init MPI for multithread support
  	int required_support = MPI_THREAD_SERIALIZED; // Maximum supported by the K Computer
	  int provided_support = MPI::Init_thread(required_support); 
  }	 
  
  // Catch signal when a child is exiting  
  signal(SIGCHLD, catch_child_exit);
  signal(SIGPIPE, SIG_IGN);    
  if(argc < 2) {
    printf("usage: %s -app=<popc_application_main> [args]\n", argv[0]);
    MPI::Finalize();    
    return 1;
  }
  
  // Initialize local address
  rank = MPI::COMM_WORLD.Get_rank();
  world = MPI::COMM_WORLD.Get_size();

  printf("Interconnectore started %d, world size = %d\n", rank, world); 
  
  pid_t mainpid;        // Save main pid to wait for it at the end
  pthread_t mpithread;  // MPI Receive thread


  char* tmp = new char[20];
  sprintf(tmp, "uds_%d.0", rank);
  std::string local_address(tmp);
  delete [] tmp;

  // Create local combox server to accept incoming request from interface
  popc_combox_uds local;
  if(!local.Create(local_address.c_str(), true)){
    printf("POP-C++ Error: MPI Interconnector %d failed to initialize\n", rank);
    MPI::Finalize();
    return 1; 
  }  
  
  // Start main of the POP-C++ application on the MPI process with rank 0
  if(rank == 0) {
    std::string application_arg;
    char* capp = paroc_utils::checkremove(&argc, &argv, "-app=");
    // End application if app is not provided
    if(capp == NULL) {
      if(rank == 0) {
        printf("usage: %s -app=<app_exec>\n", argv[0]);      
      }
      MPI::Finalize();  
      return 1;
    } else {
      application_arg.append(capp);
    }
    printf("MPI Interconnector %d - fork for main - main name = %s\n", rank, application_arg.c_str());    
    // Create new process for the POP-C++ application main
    mainpid = fork();

    if(mainpid == 0) {
      argv[0] = const_cast<char*>(application_arg.c_str());
      execv(argv[0], argv);
      perror("Execv failed");
    } else if (mainpid == -1) {
      perror("start main process");
      MPI::Finalize();
      return 1;
    }
  }


  printf("Main started\n"); 
  
  int next_tag = 1000;  

  // Init object counter
  int next_object_id = 1;  


    
  // Create MPI receive thread
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);  
  pthread_mutex_init(&mpi_mutex, NULL);
  pthread_cond_init (&mpi_condition, NULL);    
  pthread_create(&mpithread, &attr, mpireceivedthread, NULL);



  
/* pthread_mutex_lock(&mpi_mutex);
  pthread_cond_signal(&mpi_condition);
  pthread_mutex_unlock(&mpi_mutex); */ 
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
    } else if(!connection->is_initial_connection()) {
      // Process incoming request
      paroc_buffer_factory *buffer_factory = connection->GetBufferFactory();
	    request.data = buffer_factory->CreateBuffer();
		  if (request.data->Recv(connection)) {
  		  request.from = connection;
	  		const paroc_message_header &header = request.data->GetHeader();
  		  request.methodId[0] = header.GetClassID();
        if(header.GetType() == TYPE_EXCEPTION) {
  	  		request.methodId[1] = header.GetMethodID() - 100000;
        } else {
          request.methodId[1] = header.GetMethodID();
        }
        //printf("MPI: fd %d %d\n", dynamic_cast<popc_connection_uds*>(connection)->get_fd(), request.methodId[1]);			    
			  // Killing the process, end of the higher-level application
		  	if(request.methodId[1] == 200001){
		  	  active = false;
		  	  if(rank == 0) {
            int data = 10; // DATA 10 = END OF THE APPLICATION		  	   		  	  
            int tag = 0;   // TAG 0 = COMMAND MESSAGE
		    	  if(world > 1) {
		    	    for(int i = 1; i < world; i++) {
                // Inform other MPI communicator to end their process. 
		  	        MPI::COMM_WORLD.Isend(&data, 1, MPI_INT, i, tag);
  		  	    }
            }
      	    MPI::COMM_WORLD.Isend(&data, 1, MPI_INT, 0, tag);                      	    
      	  }
/*          pthread_mutex_lock(&mpi_mutex);
          pthread_cond_signal(&mpi_condition);
          pthread_mutex_unlock(&mpi_mutex);  */
       
        } else if(request.methodId[1] == 200002) {  
          // Connection to this process as a router process
          
		  	  int dest_node, dest_id;
		      request.data->Push("destnode", "int", 1);
         	request.data->UnPack(&dest_node, 1);
        	request.data->Pop();

		      request.data->Push("destid", "int", 1);
         	request.data->UnPack(&dest_id, 1);
        	request.data->Pop();
        	
         	int current_fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();  
         	incomingconnection.insert(pair<int, pair<int, int> >(current_fd, pair<int, int>(dest_node, dest_id)));
         	
         	//printf("Connection fd = %d, dest node = %d, dest id = %d\n", current_fd, dest_node, dest_id);
         	    	
        } else if(request.methodId[1] == 200003) {
          // Get information from the MPI received node
          // None to get for the moment
          
        } else if(request.methodId[1] == 200004) {
          // Allocation of a new parallel object from MPI
          MPI::Status status;
          int objectname_length, codefile_length; 
          MPI::COMM_WORLD.Recv(&objectname_length, 1, MPI_INT, MPI_ANY_SOURCE, 10, status);
          MPI::COMM_WORLD.Recv(&codefile_length, 1, MPI_INT, status.Get_source(), 12);
          char* objectname = new char[objectname_length+1];
          char* codefile = new char[codefile_length+1];                    
          MPI::COMM_WORLD.Recv(objectname, objectname_length, MPI_CHAR, status.Get_source(), 11);
          MPI::COMM_WORLD.Recv(codefile, codefile_length, MPI_CHAR, status.Get_source(), 13);
          objectname[objectname_length] = '\0';
          codefile[codefile_length] = '\0';
          
          // Allocate on the local node
          char* tmp = new char[15];
          snprintf(tmp, 15, "uds_%d.%d", rank, next_object_id);
          next_object_id++;
              
          popc_combox_uds receiver;
          std::string receiver_address(local_address);
          receiver_address.append("_");
          receiver_address.append(tmp);
          receiver.Create(receiver_address.c_str(), true);
              
          std::string _objectname("-object=");
          _objectname.append(objectname);
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
          if(allocatepid == 0) {
            char* argv1[6];
            argv1[0] = codefile;                        // Object executable
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
  	  	  	if(callback.methodId[1] == 200002){
  	  	  	  int length = strlen(objectaddress.GetString());
  	  	  	  MPI::COMM_WORLD.Isend(&length, 1, MPI_INT, status.Get_source(), 14);
              MPI::COMM_WORLD.Isend(objectaddress.GetString(), length, MPI_CHAR, status.Get_source(), 15);
	  	      } else {
  	  	  	  int length = 0;
  	  	  	  MPI::COMM_WORLD.Isend(&length, 1, MPI_INT, status.Get_source(), 14);	  	      
  	  	    }
	    	  }
   	      callback.data->Destroy();
   	      receiver.Close();            
          pthread_mutex_lock(&mpi_mutex);
          pthread_cond_signal(&mpi_condition);
          pthread_mutex_unlock(&mpi_mutex);
        } else if(request.methodId[1] == 200000) {  
          // Allocation a new parallel object from IPC
          
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
           	  	
          if (node != rank && node != -1 && node < world) {
            // Unlock local MPI receive thread
            int data = 12;
      	    MPI::COMM_WORLD.Isend(&data, 1, MPI_INT, rank, 0); 
            

            // Send signal to the remote node
            data = 11; 
            MPI::COMM_WORLD.Isend(&data, 1, MPI_INT, node, 0);        
                
            // Send allocation information to the destination MPI Communicator
            int objectname_length = strlen(objectname.GetString());
            int codefile_length = strlen(codefile.GetString());
            MPI::COMM_WORLD.Isend(&objectname_length, 1, MPI_INT, node, 10);
            MPI::COMM_WORLD.Isend(objectname.GetString(), objectname_length, MPI_CHAR, node, 11);
            MPI::COMM_WORLD.Isend(&codefile_length, 1, MPI_INT, node, 12);
            MPI::COMM_WORLD.Isend(codefile.GetString(), codefile_length, MPI_CHAR, node, 13);
            
            // Receive objaccess from the allocator node
            int objaccess_length; 
            MPI::COMM_WORLD.Recv(&objaccess_length, 1, MPI_INT, node, 14);
            char* objaccess = new char[objaccess_length+1];
            MPI::COMM_WORLD.Recv(objaccess, objaccess_length, MPI_CHAR, node, 15);
            objaccess[objaccess_length] = '\0';

            // Return objaccess
            POPString objectaddress(objaccess);
            delete [] objaccess;
         	  request.data->Reset();		            
   	    		paroc_message_header h("_allocate");
         		request.data->SetHeader(h);
            request.data->Push("objectaddress", "POPString", 1);
            request.data->Pack(&objectaddress, 1);
            request.data->Pop();
            request.data->Send(request.from);            
            
          } else {
            // Allocate on the local node
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
            if(allocatepid == 0) {
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
  	  	  	  if(callback.methodId[1] == 200002){
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
	  	  } else if(request.methodId[1] == 200005) {
          // Receive request from MPI and redirect to IPC object
          int dest_id;
          int source = request.methodId[0];
          MPI::Status status; 
          MPI::COMM_WORLD.Recv(&dest_id, 1, MPI_INT, source, MPI_ANY_TAG, status);

                    
          int tag = status.Get_tag();
/*          pthread_mutex_lock(&mpi_mutex);
          pthread_cond_signal(&mpi_condition);
          pthread_mutex_unlock(&mpi_mutex);          
          */
          //printf("Redirect %d IPC to %d tag=%d\n", source, dest_id, tag);

          // Receive the data length
          int length; 
          //printf("MPI(%d) start receive request\n", rank);
          MPI::COMM_WORLD.Recv(&length, 1, MPI_INT, source, tag);
          
          // Connect to the remote object
        	/*paroc_combox_factory* combox_factory = paroc_combox_factory::GetInstance();
          paroc_combox* client = combox_factory->Create("uds");
          char* address = new char[15];
          snprintf(address, 15, "uds_%d.%d", rank, dest_id); 
          client->Create(address, false);
          
          if(client->Connect(address)) {
            connection = client->get_connection();	
          	int fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();        	
            outgoingconnection[fd] = pair<int, int>(tag, source);        	
            local.add_fd_to_poll(fd);

          } else {
            printf("Can't connect\n");
          }*/
            
                 
          
       	  paroc_combox* client;
         	paroc_connection* connection;
       	  
          if(connectionmap[pair<int, int>(source, dest_id)] == NULL) {
            // Need to establish a connection
      
            // Connect to the remote object
          	paroc_combox_factory* combox_factory = paroc_combox_factory::GetInstance();
            client = combox_factory->Create("uds");
            char* address = new char[15];
            snprintf(address, 15, "uds_%d.%d", rank, dest_id);

            // Save the combox for further communication
            connectionmap[pair<int, int>(source, dest_id)] = client;          

          
            client->Create(address, false);
            if(client->Connect(address)) {
            	connection = client->get_connection();	
          	  int fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();        	
              // Store 
            	outgoingconnection[fd] = pair<int, int>(tag, source);        	
              local.add_fd_to_poll(fd);

            } else {
              printf("Can't connect\n");
            }
          
          } else {
            // Get old combox
            client = connectionmap[pair<int, int>(source, dest_id)]; 
           	connection = client->get_connection();	
         	  int fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();             	
            outgoingconnection[fd] = pair<int, int>(tag, source);        	                     	  
          }         
          
          char* data = new char[length];
          // Receive the data
          MPI::COMM_WORLD.Recv(data, length, MPI_CHAR, source, tag);          
         	//printf("MPI(%d) - Request Recv complete\n", rank);


     	  	if (client->Send(data, length, connection) < 0) {
         	  printf("Can't send to final object\n");
         	}
         	//printf("MPI(%d) - Request sent complete\n", rank);
          delete [] data;
	  	  } else if(request.methodId[1] == 200006) {          
	  	    // Response from local node MPI Communicator to IPC caller
          int source = request.methodId[0];	  	    
	  	    MPI::Status status;
	  	    int length;
	  	    MPI::COMM_WORLD.Recv(&length, 1, MPI_INT, source, MPI_ANY_TAG, status);

	  	    int tag = status.Get_tag();
/*	  	    pthread_mutex_lock(&mpi_mutex);
          pthread_cond_signal(&mpi_condition);
          pthread_mutex_unlock(&mpi_mutex);  */
          	  	    

	  	    char *data = new char[length];
	  	    MPI::COMM_WORLD.Recv(data, length, MPI_CHAR, source, tag);
	  	    
	  	    int fd = incomingtag[tag];
	  	    //printf("Redirect to caller %d\n", fd);
	  	    popc_connection_uds* tmpconnection = new popc_connection_uds(fd, &local);
	        if (local.Send(data, length, tmpconnection) < 0) {
        	  printf("Can't send to caller\n");
        	} 
	  	    
	  	    delete [] data;
	  	  } else {
	  	    // Redirect request 
	  	    int fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();
	  	    //printf("Redirect via MPI on %d fd = %d\n", rank, fd);	  	    
	  	    // Redirect response to caller
	  	    if(outgoingconnection[fd].first != 0) {
            //printf("IPC - Response %d %d\n", rank, request.methodId[1]);	  	  	  	    
	  	      int dest = outgoingconnection[fd].second;
	  	      int tag = outgoingconnection[fd].first;     
  	  	    int data = 14;
            MPI::COMM_WORLD.Isend(&data, 1, MPI_INT, dest, 0); 	  	      
	  	      
	  	      // Send length of the request
            int length = request.data->get_size();
            MPI::COMM_WORLD.Isend(&length, 1, MPI_INT, dest, tag);
            char *load = request.data->get_load();
            MPI::COMM_WORLD.Isend(load, length, MPI_CHAR, dest, tag);            
	  	      
	  	    
	  	    } else { 
            //printf("IPC - Request %d %d\n", rank, request.methodId[1]);	  	    
	  	      // Redirect request to object
	  	      int dest_node = incomingconnection[fd].first;
	    	    int dest_id = incomingconnection[fd].second;

            // printf("Redirect from %d to %d.%d tag=%d fd=%d\n", rank, dest_node, dest_id, next_tag, fd);             	    	    
  	  	    // Send the request by MPI
	  	      int data = 13;
            MPI::COMM_WORLD.Isend(&data, 1, MPI_INT, dest_node, 0); 
            // Send object id
            MPI::COMM_WORLD.Isend(&dest_id, 1, MPI_INT, dest_node, next_tag);
            // Send data size
            int length = request.data->get_size();
            MPI::COMM_WORLD.Isend(&length, 1, MPI_INT, dest_node, next_tag);
            // Send the actual data        
            char *load = request.data->get_load();
            MPI::COMM_WORLD.Isend(load, length, MPI_CHAR, dest_node, next_tag);            
            incomingtag[next_tag] = fd;
            //printf("tag=%d fd=%d\n", next_tag, fd);
            next_tag++;
          	  	    
	  	    }
	  	  }
        request.data->Destroy();
      }
    }
  }    
      
  local.Close();
  
  
  
  // Delete connection to object
  map<pair<int, int>, paroc_combox*>::iterator it;
  for (it = connectionmap.begin() ; it != connectionmap.end(); it++) {
    ((*it).second)->Close();
    delete dynamic_cast<popc_combox_uds*>((*it).second);
  }
  


  pthread_join(mpithread, NULL);
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&mpi_mutex);
  pthread_cond_destroy(&mpi_condition);

  MPI::Finalize();
  return 0;
}

