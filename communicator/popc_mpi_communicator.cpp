/**
 *
 *
 */

// System include
#include <mpi.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

// POP-C++ library include
#include "paroc_broker.h"
#include "paroc_buffer_xdr.h"
#include "popc_combox_uds.h"



/**
 * Catch signal of exiting child
 */
void catch_child_exit(int signal_num) {
  int retval, nval;
  char buf[256];
  bzero(buf, 256);
  nval = waitpid(0, &retval, WNOHANG);  
//  sprintf(buf,"Waited on child %d which exited with code = %d\n",nval,retval);       
  write(STDOUT_FILENO, buf, 256);
}

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
  char* tmp = new char[20];
  sprintf(tmp, "uds_%d.0", rank);
  std::string local_address(tmp);
  delete [] tmp;

  // Init object counter
  int next_object_id = 1;  
  
  if(rank == 0) {
    std::string application_arg(argv[1]);

    std::size_t pos = application_arg.find("-app=");
    if(pos != std::string::npos){
      application_arg = application_arg.substr(pos+5);
    }

    pid_t pid = fork();

    if(pid ==0) {
      char* argv1[2];
      argv1[0] = const_cast<char*>(application_arg.c_str());
      argv1[1] = (char*)0;
      execv(argv1[0], argv1);
      perror("Execv failed");

    } else if(pid != -1) {
      // Create local combox server to accept incoming request from interface
      popc_combox_uds local;
      local.Create(local_address.c_str(), true);
      bool active = true;
      while (active) {
    		paroc_request request;
    		request.data = NULL;
      
  	  	paroc_connection* connection = local.Wait();
  		  if(connection == NULL) {
  		    printf("Connection null\n");
  		  
    		} else {
  		  
    		  paroc_buffer_factory *buffer_factory = connection->GetBufferFactory();
	    	  request.data = buffer_factory->CreateBuffer();
		      if (request.data->Recv(connection)) {
  			    request.from = connection;
	  		    const paroc_message_header &header = request.data->GetHeader();
  		  	  request.methodId[0] = header.GetClassID();
	  		    request.methodId[1] = header.GetMethodID();
			    
		  	    if(request.methodId[1] == 100001){
		  	      active = false;
		  	    } else if(request.methodId[1] == 100000) {
		  	      POPString objectname, codefile;
		  	     	request.data->Push("objectname", "POPString", 1);
            	request.data->UnPack(&objectname, 1);
            	request.data->Pop();
		  	     	request.data->Push("codefile", "POPString", 1);
            	request.data->UnPack(&codefile, 1);
            	request.data->Pop();		  

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


              
              
              // Allocate the object      
              pid_t allocatepid = fork();
              if(allocatepid == 0){
                char* argv1[5];
                argv1[0] = codefile.GetString();  // Object executable
                argv1[1] = const_cast<char*>(_objectname.c_str());   // Object name
                argv1[2] = const_cast<char*>(_objectaddress.c_str()); // Object address
                argv1[3] = const_cast<char*>(_receiveraddress.c_str());
                argv1[4] = (char*)0;             
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
      // Wait for the program to finish
      int status;  
      waitpid(pid, &status, 0);
    } else {
      perror("erreur");
      MPI::Finalize();    
      return 1;
    }  
  }
  
  MPI::Finalize();
  return 0;
}

