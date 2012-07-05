/**
 * File : appservice.cc
 * Author : Tuan Anh Nguyen
 * Description : implementation of the application scope service
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval	2010/11/08	Add the generation of the POP Application Unique ID and Getter for this ID.
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string>
#include <locale>
#include "appservice.ph"

#include "jobmgr.ph"

using namespace std;

AppCoreService::AppCoreService(const POPString &challenge, bool daemon, const POPString &codelocation): paroc_service_base(challenge), CodeMgr(challenge), RemoteLog(challenge), ObjectMonitor(challenge), BatchMgr(challenge)
{
  /**
    * ViSaG : clementval
    * Generate the POP Application Unique ID
    */
   POPString tmpChallenge = challenge;
   time_t now = time(NULL);
   POPString ip = paroc_system::GetIP();
   char id[100];
   string tmp(tmpChallenge.GetString());
   locale loc; 
   const collate<char>& coll = use_facet<collate<char> >(loc);
   long hash = coll.hash(tmp.data(), tmp.data()+tmp.length());
   if(hash < 0)
      hash = hash*-1;
   sprintf(id, "POPAPPID_%ld_%ld_%s_%d", now-0, hash, ip.GetString(), getpid());
   _popcAppId = id;
   /* ViSaG */

	if (daemon) Start();
	LoadAddOn();
      
}

AppCoreService::~AppCoreService()
{
   try{   
      JobMgr jm(paroc_system::jobservice);
      jm.ApplicationEnd(_popcAppId, true);
   } catch (...){
      
   }

	POSITION pos=servicelist.GetHeadPosition();
	while (pos!=NULL)
	{
		ServiceEntry &t=servicelist.GetNext(pos);
		free(t.name);
		try {
			t.service->Stop(mychallenge);
		}
		catch (...)
		{
		}
		delete t.service;
	}
}

// bool AppCoreService::QueryService(const POPString &name)
// {
//   if (name==NULL) return false;

//   if (paroc_utils::isEqual(name,"CodeMgr")) return true;
//   if (paroc_utils::isEqual(name,"RemoteLog")) return true;
//   if (paroc_utils::isEqual(name,"ObjectMonitor")) return true;

//   return false;
// }

bool AppCoreService::QueryService(const POPString &name, paroc_service_base &service)
{
	if (name.Length()<=0) return false;

	POSITION pos=servicelist.GetHeadPosition();
	while (pos!=NULL)
	{
		ServiceEntry &t=servicelist.GetNext(pos);
		if (paroc_utils::isncaseEqual(name,t.name))
		{
			service=(*t.service);
			return true;
		}
	}
	return false;
}

bool AppCoreService::QueryService(const POPString &name, paroc_accesspoint &service)
{
	if (name.Length()<=0) return false;

	POSITION pos=servicelist.GetHeadPosition();
	while (pos!=NULL)
	{
		ServiceEntry &t=servicelist.GetNext(pos);
		if (paroc_utils::isncaseEqual(name,t.name))
		{
			service=(t.service)->GetAccessPoint();
			return true;
		}
	}
	return false;
}

bool AppCoreService::RegisterService(const POPString &name, const paroc_service_base &newservice)
{
	if (name.Length()<=0) return false;

	ServiceEntry t;
	try
	{
		t.service=new paroc_service_base(newservice);
		t.name=strdup(name);
	}
	catch (...)
	{
		return false;
	}
	servicelist.AddTail(t);
	return true;
}

bool AppCoreService::UnregisterService(const POPString &name)
{
	if (name.Length()<=0) return false;

	POSITION pos=servicelist.GetHeadPosition();
	while (pos!=NULL)
	{
		POSITION old=pos;
		ServiceEntry &t=servicelist.GetNext(pos);
		if (paroc_utils::isncaseEqual(name,t.name))
		{
			delete t.service;
			free(t.name);
			servicelist.RemoveAt(old);
			return true;
		}
	}
	return false;
}


void AppCoreService::LoadAddOn()
{

	char fname[1024];
	char *parocdir;
	if ((parocdir=getenv("POPC_APPSERVICE_CONF"))!=NULL) strcpy(fname, parocdir);
	else if ((parocdir=getenv("POPC_LOCATION"))==NULL) return;
	else sprintf(fname,"%s/etc/appservice.conf",parocdir);

	FILE *f=fopen(fname,"r");
	if (f==NULL) return;

	char buf[1024];
	char exec[1024];
	char service[1024];

	while (fgets(buf,1023,f)!=NULL)
	{
		char *objfile=buf;
		while (isspace(*objfile)) objfile++;
		if (*objfile=='#' || *objfile==0) continue;

		char *tmp=strstr(objfile,"-object=");
		if (tmp==NULL)
		{
			DEBUG("No addon service name specified: %s", objfile);
			continue;
		}
		paroc_accesspoint ap;
		paroc_accesspoint jobmgr;
		paroc_od od; // Note : the od is empty !
		sprintf(exec, "%s -constructor",objfile);
		if (paroc_interface::LocalExec(NULL,exec, NULL, jobmgr, GetAccessPoint(), &ap,1,od)!=0)
		{
			DEBUG("Fail to start the add-on [%s]", buf);
			continue;
		}
		try {
			paroc_service_base s(ap);
			s.Start(mychallenge);
		}
		catch (...)
		{
			DEBUG("Can not connect to %s",service);
			continue;
		}
		if (tmp!=NULL && sscanf(tmp+8,"%s",service)==1)
		{
			DEBUG("Service: %s", service);
			RegisterService(service, ap);
		}
	}
	fclose(f);

}

/**
 * ViSaG : clementval
 * Getter for the POP Application Unique ID
 * @return a POPString containing the POPAppID
 */
POPString AppCoreService::GetPOPCAppID(){
   return _popcAppId;
}




int popc_appservice_log(const char *format,...)
{
	char *tmp=getenv("POPC_TEMP");
	char logfile[256];
	if (tmp!=NULL) sprintf(logfile,"%s/popc_appservice_log",tmp);
	else strcpy(logfile, "/tmp/pop_appservice.log");

	FILE *f=fopen(logfile,"a");
	if (f==NULL) return 1;
	time_t t=time(NULL);
	fprintf(f,"%s", ctime(&t));
	va_list ap;
	va_start(ap, format);
	vfprintf(f, format, ap);
	fprintf(f,"%s","\n");
	va_end(ap);
	fclose(f);
	return 0;
}
