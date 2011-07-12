#include <stdio.h>

#include "paroc_interface.h"
#include "paroc_broker.h"

#include "paroc_service_base.ph"
#include "objectmonitor.ph"

#include <strings.h>


#include <stdarg.h>
int paroc_service_log(const char *format,...)
{
  char *tmp=getenv("PAROC_TEMP");
  char logfile[256];
  if (tmp!=NULL) sprintf(logfile,"%s/paroc_service_log",tmp);
  else strcpy(logfile, "/tmp/paroc_service.log");

  FILE *f=fopen(logfile,"a");
  if (f==NULL) return 1;
  time_t t=time(NULL);
  fprintf(f, ctime(&t));
  va_list ap;
  va_start(ap, format);
  vfprintf(f, format, ap);
  fprintf(f,"\n");
  va_end(ap);
  fclose(f);
  return 0;
}


paroc_service_base::paroc_service_base(const paroc_string &challenge):mychallenge(challenge)
{
  if (!paroc_system::appservice.IsEmpty())
    {
      paroc_accesspoint myself=GetAccessPoint();
      try 
	{
	  ObjectMonitor tmp(paroc_system::appservice);
	  tmp.UnManageObject(myself);
	}
      catch(...)
	{
	  DEBUG("Failed to unregister the service from ObjectMonitor");
	}
    }
}

paroc_service_base::paroc_service_base()
{

  if (!paroc_system::appservice.IsEmpty())
    {
      paroc_accesspoint myself=GetAccessPoint();
      try 
	{
	  ObjectMonitor tmp(paroc_system::appservice);
	  tmp.UnManageObject(myself);
	}
      catch(...)
	{
	}
    }
}

//Switch to the daemon mode...
void paroc_service_base::Start()
{
  daemonMode=true;

}

bool paroc_service_base::Stop(const paroc_string &challenge)
{
  if (paroc_utils::isEqual(mychallenge,challenge) || mychallenge==NULL)
    {
      daemonMode=false;
//      while (DecRef()>0);
      return true;
    }
  return false;
}

//Redefine behaviors of parallel object creation/destruction...
int paroc_service_base::AddRef()
{
  if (daemonMode) return 1;
  return paroc_object::AddRef();
}

int paroc_service_base::DecRef()
{
  if (daemonMode) return 1;
  return paroc_object::DecRef();
}
bool paroc_service_base::CanKill()
{
  if (daemonMode) return false;
  return paroc_object::CanKill();
}
