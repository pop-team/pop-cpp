#include <stdio.h>

#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

#include "paroc_system.h"
#include <appservice.ph>
#include <paroc_buffer_factory_finder.h>
#include <paroc_utils.h>

paroc_accesspoint paroc_system::appservice;
paroc_accesspoint paroc_system::jobservice;
paroc_string paroc_system::platform;
char *paroc_system::paroc_errstr[13]=
  {"Out of resource",
   "Fail to bind to the remote object broker",
   "Mismatch remote method id",
   "Can not access code service",
   "Object allocation failed",
   "Bad paroc package format",
   "ParoC++ local application service failed",
   "ParoC++ job manager service failed",
   "Execution of object code failed",
   "Bad binding reply",
   "No support protocol",
   "No support data encoding",
   "Unknown ParoC++ exception"
  };


AppCoreService *paroc_system::mgr=NULL;
paroc_string paroc_system::challenge;

paroc_system::paroc_system()
{
  paroc_combox_factory::GetInstance();
  paroc_buffer_factory_finder::GetInstance();
  char *tmp=getenv("PAROC_PLATFORM");
  if (tmp!=NULL)
    {
      platform=tmp;
    }
  else
    {
      char str[128];
      
#ifndef PAROC_ARCH
      char arch[64], sysname[64];
      sysinfo(SI_SYSNAME,sysname,64);
      sysinfo(SI_ARCHITECTURE,arch,64);
      sprintf(str,"%s-%s",sysname,arch);
#else 
      strcpy(str,PAROC_ARCH);
#endif
      platform=str;
    }
}


paroc_system::~paroc_system()
{
  if (mgr!=NULL)
    {
      Finalize(false);
      delete mgr;
    }
  mgr=NULL;

  paroc_combox_factory *pf=paroc_combox_factory::GetInstance();
  paroc_buffer_factory_finder *bf=paroc_buffer_factory_finder::GetInstance();
  pf->Destroy();
  delete bf;
}


void paroc_system::perror(const char *msg)
{
  if (errno>USER_DEFINE_ERROR && errno<=USER_DEFINE_LASTERROR)
    {
      if (msg==NULL) msg="Error";
      fprintf(stderr,"%s: %s\n",msg,paroc_errstr[errno-USER_DEFINE_ERROR-1]);
    } 
  else if (errno>USER_DEFINE_LASTERROR) fprintf(stderr,"%s: Unknown error\n",msg);
  else ::perror(msg);
}

paroc_string paroc_system::GetHost()
{
  char str[128];
  char *t=getenv("PAROC_HOST");
  if (t==NULL || *t==0)
    {
      gethostname(str,127);
      if (strchr(str,'.')==NULL)
	{
	  int len=strlen(str);
	  char *domain=getenv("PAROC_DOMAIN");
	  if (domain!=NULL)
	    {
	      str[len]='.';
	      strcpy(str+len+1,domain);
	    } 
	  else
	    {
	      return GetIP();
	    }
	}
      return paroc_string(str);
    } else return paroc_string(t);
}


paroc_string paroc_system::GetIP()
{
  char ipaddr[64];
  char hostname[256];
  if (gethostname(hostname,256)!=0) return paroc_string("127.0.0.1");
  struct hostent *hp=gethostbyname(hostname);
  unsigned ip=(unsigned(127)<<24)+1;

  if (hp==NULL || *(hp->h_addr_list)==NULL) return paroc_string("127.0.0.1");
    
  char **p=hp->h_addr_list;
  while (*p!=NULL)
    {
      memcpy(&ip,*p, sizeof (unsigned));
      ip=ntohl(ip);
      if (ip!=(unsigned(127)<<24)+1)
	{
	  break;
	}
      p++;
    }
  int n1,n2,n3,n4;
  n1=ip & 255;
  ip=ip>>8;
  
  n2=ip & 255;
  ip=ip>>8;
  
  n3=ip & 255;
  ip=ip>>8;
  
  n4=ip & 255;
  sprintf(ipaddr,"%d.%d.%d.%d",n4,n3,n2,n1);
  endhostent();

  return paroc_string(ipaddr);
}

int paroc_system::GetIP(const char *hostname, int *iplist, int listsize)
{
  struct hostent *hp;
  int n;
  char **p;
  int addr;
  if ((int)(addr = inet_addr(hostname)) == -1) 
    {
      hp=gethostbyname(hostname);
    } 
  else
    {
      if (listsize>0) 
	{
	  *iplist=ntohl(addr);
	  return 1;
	}
      return 0;
    }
  if (hp==NULL) return 0;
  n=0;
  for (p = hp->h_addr_list; *p != 0 && n<listsize; p++) 
    {
      memcpy(iplist, *p, sizeof (int));
      *iplist=ntohl(*iplist);
      if (*iplist==(int(127)<<24)+1) continue;
      n++;
      iplist++;

    }
  endhostent();
  if (n==0) n=1;
  return n;
}


int paroc_system::GetIP(int *iplist, int listsize)
{
  char *parocip=getenv("PAROC_IP");
  if (parocip!=NULL)
    {
      int n;
      int addr;
      parocip=strdup(parocip);
      char *tmp;
      char *tok=strtok_r(parocip," \n\r\t",&tmp);
      n=0;
      while (tok!=NULL && n<listsize)
	{
	  if ((int)(addr = inet_addr(tok)) != -1)
	    {
	      *iplist=ntohl(addr);
	      iplist++;
	      n++;
	    }
          tok=strtok_r(NULL," \n\r\t",&tmp);
	}
      free(parocip);
      return n;
    }
  return GetIP(GetHost(),iplist, listsize);
}



bool paroc_system::Initialize(int *argc,char ***argv)
{
  char *info=paroc_utils::checkremove(argc,argv,"-jobservice=");
  if (info==NULL) return false;
  paroc_system::jobservice.SetAccessString(info);

  char *codeser=paroc_utils::checkremove(argc,argv,"-appservicecode=");
  char *proxy=paroc_utils::checkremove(argc,argv,"-proxy=");

  char *appcontact=paroc_utils::checkremove(argc,argv,"-appservicecontact=");

  if (codeser==NULL && appcontact==NULL) return false;

  try {
    if (appcontact==NULL)
      {
	char url[1024];
	if (proxy==NULL) strcpy(url,codeser);
	else sprintf(url,"%s -proxy=%s",codeser, proxy);
	mgr=CreateAppCoreService(url);
      }
    else
      {
	challenge=NULL;
	paroc_accesspoint app;
	app.SetAccessString(appcontact);
	mgr=new AppCoreService(app);
      }

    paroc_system::appservice=mgr->GetAccessPoint();
  }

  catch (...)
    {
      if (mgr!=NULL)
	{
	  mgr->KillAll();
	  mgr->Stop(challenge);
	  delete mgr;
	  mgr=NULL;
	}
      return false;
    }

  char *codeconf=paroc_utils::checkremove(argc,argv,"-codeconf=");

  DEBUGIF(codeconf==NULL,"No code config file\n");

  if (codeconf!=NULL && !paroc_utils::InitCodeService(codeconf,mgr)) return false;

 return true;
  

}

void paroc_system::Finalize(bool normalExit)
{
  
  if (mgr!=NULL)
    {
      try 
	{
	  if (normalExit)
	    {
	      //Wait all object to be terminated!
	      int timeout=10;
	      int oldcount=0, count;
	      
	      while ((count=mgr->CheckObjects())>0)
		{
		  if (timeout<1800 && oldcount==count) timeout=timeout*4/3;
		  else timeout=10;
		  
		  sleep(timeout);
		  oldcount=count;
		}
	    }
	  else mgr->KillAll();
	  
	  mgr->Stop(challenge);
	  delete mgr;
	  //	DEBUG("Application scope services are terminated");
	}
      catch (paroc_exception *e)
	{
	  paroc_system::perror(e->Extra());
	  delete e;
	}
      catch (...)
	{
	  fprintf(stderr,"ERROR on finalizing the application\n");
	}
      mgr=NULL;
    }
}



AppCoreService *paroc_system::CreateAppCoreService(char *codelocation)
{
  int i=0;
  int range=40;
  srand(time(NULL));
  char tmp[256];

  for (int i=0;i<255;i++) tmp[i]=(char)(1+254.0*rand()/(RAND_MAX+1.0) );
  tmp[255]=0;
  challenge=tmp;
  
  return new AppCoreService(challenge, false, codelocation);
}


