/**
 * File : paroc_infmain.std.cc
 * Author : Tuan Anh Nguyen
 * Description : "main" entry for the main program
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 */

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "paroc_exception.h"
#include "paroc_buffer_factory_finder.h"
#include "paroc_broker.h"
#include "paroc_buffer_xdr.h"
#include "popc_combox_uds.h"


// Set processor
#include <sched.h>
#define error printf
#define panic printf
#define debug(a,b,c) printf((b),(c),(a))

extern int parocmain(int, char **);

void SignalTerminate(int sig)
{
	printf("SIGNAL %d!!!!\n",sig);
	paroc_system::Finalize(false);
	exit(1);
}

void _paroc_atexit()
{
	paroc_system::Finalize(false);
}

int main(int argc, char **argv)
{

#ifdef UC_LINUX
	paroc_system::processor_set(0);
#endif
	paroc_system app;
  paroc_system::pop_current_local_address = 1;
  paroc_system::popc_local_mpi_communicator_rank = 0;

	char **argv1 = argv;
	int i;
	for (i=argc-1;i>=0;i--) {
	  if (paroc_utils::isEqual(argv[i],"-initparoc")) {
	    printf("init\n");
			char **argv1=argv+i+1;
			int argc1=argc-i-1;
			if (!paroc_system::Initialize(&argc1, &argv1)) {
				fprintf(stderr,"Initialization of parallel objects fail...\n");
				paroc_system::Finalize(false);
				return -1;
			}
			argv[i]=NULL;
			argc=i;
			break;
		}
	}


	if (i < 0) {
	  int ret = parocmain(argc, argv);

	  /**
	   * POP-C++ on the K Computer
	   * Terminate the MPI Communicators network by sending a termination message to the local MPI Communicator with rank 0
	   */

	  paroc_combox_factory* combox_factory = paroc_combox_factory::GetInstance();
	  if (combox_factory == NULL) 
	    paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "POPCMain");
	
  	paroc_combox* allocating_combox = combox_factory->Create("uds");
    if(allocating_combox == NULL)
      paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "POPCMain");
    
    paroc_buffer* allocating_buffer = allocating_combox->GetBufferFactory()->CreateBuffer();  
  
    char* local_address = new char[15];
    snprintf(local_address, 15, "uds_%d.0", paroc_system::popc_local_mpi_communicator_rank);

    if(!allocating_combox->Create(local_address, false) || !allocating_combox->Connect(local_address))
      paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "POPCMain");

  	paroc_message_header header(0, 200001, INVOKE_SYNC, "_terminate");
	  allocating_buffer->Reset();
  	allocating_buffer->SetHeader(header);
	  paroc_connection* connection = allocating_combox->get_connection();

    if (!allocating_buffer->Send((*allocating_combox), connection)) {
	    paroc_exception::paroc_throw_errno();
  	}   
	  return ret;
	}



	atexit(_paroc_atexit);

	signal(SIGKILL,SignalTerminate);
	signal(SIGTERM,SignalTerminate);
	signal(SIGINT,SignalTerminate);
	signal(SIGQUIT,SignalTerminate);
	signal(SIGPIPE,SIG_IGN);

	try {
		int ret=parocmain(argc,argv);
		app.Finalize(ret==0);
		return ret;
	}
	catch (paroc_exception *e)
	{
		errno=e->Code();
		paroc_system::perror(e);
		delete e;
		paroc_system::Finalize(false);
		return -1;
	}
	catch (int e)
	{
		errno=e;
		paroc_system::perror("Exception occured\n");
		paroc_system::Finalize(false);
		return -1;
	}
	catch (...)
	{
		fprintf(stderr,"Unknown exception\n");
		paroc_system::Finalize(false);
	}
	return 1;
}
