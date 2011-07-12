/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: "main" entry for the main program
 */

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "paroc_exception.h"
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

	char **argv1=argv;
	int i;
	for (i=argc-1;i>=0;i--) if (paroc_utils::isEqual(argv[i],"-initparoc"))
		{
			char **argv1=argv+i+1;
			int argc1=argc-i-1;
			if (!paroc_system::Initialize(&argc1,&argv1))
			{
				fprintf(stderr,"Initialization of parallel objects fail...\n");
				paroc_system::Finalize(false);
				return -1;
			}
			argv[i]=NULL;
			argc=i;
			break;
		}

	if (i<0) return parocmain(argc,argv);

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
