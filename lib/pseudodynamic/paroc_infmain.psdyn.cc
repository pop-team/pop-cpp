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
#include <mpi.h>

#include "paroc_exception.h"
#include "paroc_utils.h"
#include "paroc_system.h"
#include "paroc_buffer_factory_finder.h"

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
	paroc_system::is_remote_object_process = false;

	/**
	 * 
	 */
  if(!MPI::Is_initialized()){
 	  // Init MPI for multithread support
  	int required_support = MPI_THREAD_SERIALIZED; // Required multiple thread support to allow multiple connection to an object
	  int provided_support = MPI::Init_thread(required_support); 
  }	 
  printf("ARGS %d %s\n", argc, argv[0]);
  paroc_system::current_free_process = 2;
//  printf("Main %d\n", MPI::COMM_WORLD.Get_rank());
	
	//printf("Start main of POP-C++ application: rank:%d\n", rank);
	char **argv1 = argv;
	int i;
	for (i = argc - 1; i >= 0; i--) {
	  if (paroc_utils::isEqual(argv[i],"-initparoc")) {
	  	char **argv1 = argv + i + 1;
  		int argc1 = argc - i - 1;
		  if (!paroc_system::Initialize(&argc1, &argv1)) {
	  		fprintf(stderr,"Initialization of parallel objects fail...\n");
  			paroc_system::Finalize(false);
			  return -1;
		  }
	  	argv[i] = NULL;
  		argc = i;
		  break;
	  }
	}
		

  //printf("MAIN: Ready to call real application main\n");
	 
	/* END OF ADD */

	if (i<0) {
		int ret = parocmain(argc,argv);
		
		int cmd = 2; 
		MPI::COMM_WORLD.Send(&cmd, 1, MPI_INT, 1, 10);
		
    if(!MPI::Is_finalized()) {     
    	MPI::Finalize();		
    }
		return ret; 
	}

	atexit(_paroc_atexit);
	signal(SIGKILL, SignalTerminate);
	signal(SIGTERM, SignalTerminate);
	signal(SIGINT, SignalTerminate);
	signal(SIGQUIT, SignalTerminate);
	signal(SIGPIPE, SIG_IGN);

	try {
		int ret = parocmain(argc, argv);
		//app.Finalize(ret == 0);
  //  printf("Will call MPI::Finalize and exit main 1\n");		
		// Only for MPI
    if(!MPI::Is_finalized()){
      printf("MPI::Finalize\n");	      
    	MPI::Finalize();		
    }
   // printf("Exit main\n");		    	
		return ret;
	} catch (paroc_exception *e) {
	 // printf("End of main exception caught 1\n");
		errno = e->Code();
		paroc_system::perror(e);
		delete e;
		paroc_system::Finalize(false);
   // printf("Will call MPI::Finalize and exit main\n");		
		// Only for MPI
    if(!MPI::Is_finalized())
    	MPI::Finalize();		
		return -1;
	} catch (int e) {
	  //printf("End of main exception caught 2\n");	
		errno=e;
		paroc_system::perror("Exception occured\n");
		paroc_system::Finalize(false);
    //printf("Will call MPI::Finalize and exit main\n");		
		// Only for MPI
    if(!MPI::Is_finalized())
    	MPI::Finalize();				
		return -1;
	} catch (...) {
	  //printf("End of main exception caught 3\n");	
		fprintf(stderr,"Unknown exception\n");
		paroc_system::Finalize(false);
   // printf("Will call MPI::Finalize and exit main\n");		
		// Only for MPI		
    if(!MPI::Is_finalized())
    	MPI::Finalize();				
	}	
 // printf("Will call MPI::Finalize and exit main\n");	
	// Only for MPI
  if(!MPI::Is_finalized())
   	MPI::Finalize();				  
	return 1;
}
