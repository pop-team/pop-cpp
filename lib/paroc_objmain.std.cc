/*Initialization of parallel objects
The Job service can pass to a parallel object environment by:
1- Specify the argument -jobservice=<code services...> when launching the object binary code (not used by the Interface)
2- Set environment variable "PAROC_JOBSERVICE to the job service point
3- <localhost>:2711 ( if 1/ and 2/ are not specified )
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

#include "appservice.ph"
#include "paroc_buffer_factory_finder.h"


void errormsg(char *s)
{
  fprintf(stderr,s);
}

void paroc_Usage(char *name)
{
      printf("\n Usage:\n\t%s [-help] [-list | -listlong] [-port=<local port>] [-callback=<host:port>] [-appservice=<host:port>] [-nostdio] <objectname>\n",name);
      exit(0); 
}

void broker_killed(int sig)
{
  rprintf("FATAL: SIGNAL %d on %s@%s\n",sig, (const char *)paroc_broker::classname,paroc_broker::accesspoint.GetAccessString());
  _exit(1);
}

extern paroc_broker *InitBroker(char *objname);
extern void QueryObjectList(char *str, int n);

void FindAbsolutePath(char *fname, char *abspath)
{
    if (*fname=='/')
    {
	strcpy(abspath,fname);
	return;
    }

    char *t=strrchr(fname,'/');
    char dir[1024];

    if (t==NULL)
    {
	if (getcwd(dir,1024)==NULL) *dir=0;
	sprintf(abspath,"%s/%s",dir,fname);
	return;
    }
    char olddir[1024];
    getcwd(olddir,1024);
    *t=0;
    chdir(fname);
    *t='/';
    if (getcwd(dir,1024)==NULL) *dir=0;
    chdir(olddir);
    sprintf(abspath,"%s/%s",dir,t+1);
}

int main(int argc, char **argv)
{
  paroc_system sys;
  char *usage=paroc_utils::checkremove(&argc,&argv,"-help");
  if (usage!=NULL || argc==1) paroc_Usage(argv[0]);

  char *tmp=paroc_utils::checkremove(&argc,&argv,"-list");
  if (tmp!=NULL)
    {
	char objlist[10240];
	objlist[10239]=0;
	QueryObjectList(objlist,10239);
	if (*tmp==0)
	{
	    printf("List of Parallel Objects resides in this code:\n====\n");
	    printf(objlist);
	    printf("====\nArchitecture=%s\n",(const char *)paroc_system::platform);
	    exit(0);      
	} else if (paroc_utils::isEqual(tmp,"long")) 
	{
	    const char sep[]="\n \t\r";
	    char *tmp=strtok(objlist,sep);

	    char abspath[1024];
	    FindAbsolutePath(argv[0],abspath);

	    while (tmp!=NULL)
	    {
		printf("%s %s %s\n",tmp, (const char *)paroc_system::platform, abspath);
		tmp=strtok(NULL,sep);
	    }
	    exit(0);
	} else paroc_Usage(argv[0]);
    }

  bool nostdio=(paroc_utils::checkremove(&argc,&argv,"-nostdio")!=NULL);

  tmp=paroc_utils::checkremove(&argc,&argv,"-appservice=");
  if (tmp!=NULL)
    {
      paroc_system::appservice.SetAccessString(tmp);
      //      strcpy(codeservice,tmp);
    } 
  //else codeservice[0]=0;


  if ((tmp=getenv("PAROC_JOBSERVICE"))!=NULL)
  {
    paroc_system::jobservice.SetAccessString(tmp);
    //      strcpy(globaljobservice,tmp);
  } else if ((tmp=paroc_utils::checkremove(&argc,&argv,"-jobservice="))!=NULL)
  {
    paroc_system::jobservice.SetAccessString(tmp);
    //    strcpy(globaljobservice,tmp);
  } 
  else
    {
      char tmpstr[256];
      DEBUG("Jobservice is not specify. Use the local default one");
      sprintf(tmpstr,"%s:%d",(const char *)paroc_system::GetHost(),DEFAULTPORT);
      paroc_system::jobservice.SetAccessString(tmpstr);
    }
  paroc_array<paroc_combox *> comboxArray;

  if (!paroc_broker::Init(&argc,&argv,comboxArray))
    {
      perror("Error starting broker....\n");
      return 1;
    }


  paroc_broker *objbroker=(paroc_broker *)InitBroker( (argc>1) ? argv[1] : NULL);
  if (objbroker==NULL)
    {
      errormsg("Unknown Object name...\n");
      paroc_Usage(argv[0]);
    }

  signal(SIGTERM,broker_killed);
  signal(SIGINT,broker_killed);
  signal(SIGQUIT,broker_killed);
  signal(SIGSEGV,broker_killed);
  signal(SIGILL,broker_killed);
  signal(SIGABRT,broker_killed);

  signal(SIGPIPE,SIG_IGN);

  objbroker->Setup(comboxArray);
  if (argv[1]!=NULL) paroc_broker::classname=argv[1];

  //Last step before starting broker: std in/out/err
  if (nostdio)
    {
      close(0);
      close(1);
      close(2);

      open("/dev/null",O_RDONLY);
#ifdef __DEBUG
      char fname[256];
      sprintf(fname,"/tmp/object_%s_%d.log", (const char *)paroc_broker::classname,getpid());
      open(fname,O_WRONLY | O_CREAT,S_IRWXU | S_IRGRP);
      dup2(1,2);
#else
      open("/dev/null",O_WRONLY);
      open("/dev/null",O_WRONLY);
#endif
    }

  //Now ....start broker....
  objbroker->Run();
  delete objbroker;
  return 0;
}






