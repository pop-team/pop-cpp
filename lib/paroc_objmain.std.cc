/**
 * File : paroc_objmain.std.cc
 * Author : Tuan Anh Nguyen
 * Description : "main" entry for the object executable
 * Initialization of parallel objects
 * The Job service can pass to a parallel object environment by:
 * 1- Specify the argument -jobservice=<code services...> when launching the object binary code (not used by the Interface)
 * 2- Set environment variable "POPC_JOBSERVICE to the job service point
 * 3- <localhost>:2711 ( if 1/ and 2/ are not specified )
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			  Comment
 * P.Kuonen   2012/09/18  Add "POP-C++ error" in error messages (PEKA)
 * clementval 2012/09/27  Code cleaning (indent, convention ...)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "paroc_broker.h"
#include "paroc_broker_factory.h"
#include "paroc_buffer_factory_finder.h"
#include "appservice.ph"


bool CheckIfPacked(const char *objname);

//extern paroc_broker *InitBroker(char *objname);
//extern void QueryObjectList(char *str, int n);


int main(int argc, char **argv)
{
  if(paroc_utils::checkremove(&argc, &argv, "-mpi") != NULL && !MPI::Is_initialized()){
 	  // Init MPI for multithread support
  	int required_support = MPI_THREAD_MULTIPLE; // Required multiple thread support to allow multiple connection to an object
	  int provided_support = MPI::Init_thread(required_support);
//	  MPI::COMM_WORLD.Set_errhandler(MPI::ERRORS_THROW_EXCEPTIONS); 

	  // Get the inter-communicator to communicate with the parent process (Interface)
  	static MPI::Intercomm parent = MPI::COMM_WORLD.Get_parent();
  }


	char *rcore = paroc_utils::checkremove(&argc,&argv,"-core=");
	if (rcore != NULL) {
		paroc_system::processor_set(atoi(rcore));
	}
#ifdef UC_LINUX
  else {
    paroc_system::processor_set(0);
  }
#endif

	paroc_system sys;

	//Connect to callback ....
	char *addr = paroc_utils::checkremove(&argc, &argv, "-callback=");
	paroc_combox *callback = NULL;
	int status = 0;
	if (addr != NULL) {
		paroc_combox_factory *fact = paroc_combox_factory::GetInstance();

		char *tmp = strstr(addr, "://");
		if (tmp == NULL) {
		  callback = fact->Create("socket");
		} else {
			*tmp = 0;
			callback = fact->Create(addr);
			*tmp = ':';
		}

		if (!callback->Create(NULL, 0, false) || !callback->Connect(addr)) {
			callback->Destroy();
			return 1;
		}
	}
	
	paroc_broker_factory::CheckIfPacked = &CheckIfPacked; // transmit the address of the check function to broker factory
	paroc_broker *br = paroc_broker_factory::Create(&argc,&argv);

	if (br == NULL) { 
	  status = 1;
	} else if (!br->Initialize(&argc, &argv)) {
		//Initialize broker...
		printf("Fail to initialize the broker for class %s\n", (const char *)paroc_broker::classname);
		status = 1;
	}


	// Send accesspoint via callback
	if (callback != NULL) {
	  printf("BROKER: Sending status and accesspoint\n");
		char url[1024];
		int len;

		
		paroc_buffer *buf = callback->GetBufferFactory()->CreateBuffer();
		
		paroc_message_header h("Callback");
		buf->SetHeader(h);

		buf->Push("status", "int", 1);
		buf->Pack(&status, 1);
		buf->Pop();
		
		printf("BROKER: status sent %d\n", status);

		buf->Push("address", "paroc_accesspoint", 1);
		paroc_broker::accesspoint.Serialize(*buf,true);
		buf->Pop();

		bool ret = buf->Send(*callback);
		
		buf->Destroy();
		
		
		callback->disconnect();		
		callback->Destroy();
		
		if (!ret) {
			rprintf("POP-C++ Error: fail to send accesspoint via callback\n");
			delete br;
			return 1;
		}
	} else if (status == 0) {
		fprintf(stdout, "%s\n", (const char *)paroc_broker::accesspoint.GetAccessString());
	}
	
	// Set the current working directory
	char *cwd=paroc_utils::checkremove(&argc,&argv,"-cwd=");
	if (cwd != NULL) {
		if (chdir(cwd) != 0)
			DEBUG("current working dir cannot be set set to %s",cwd);
	}

#ifdef OD_DISCONNECT
	bool checkConnect = (paroc_utils::checkremove(&argc, &argv, "-checkConnection")) != NULL;
	if (br != NULL)
	  br->checkConnection = checkConnect;
#endif

  // Start the broker
	if (status == 0) {
		br->Run();
		printf("Broker started\n");
		delete br;
	} else if (br != NULL) {
	  delete br;
	}

	return status;
}