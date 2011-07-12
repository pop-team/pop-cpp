/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: implementation of the application scope service
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "appservice.ph"

AppCoreService::AppCoreService(const paroc_string &challenge, bool daemon, const paroc_string &codelocation): paroc_service_base(challenge), CodeMgr(challenge), RemoteLog(challenge), ObjectMonitor(challenge), BatchMgr(challenge)
{
	if (daemon) Start();
	LoadAddOn();
}

AppCoreService::~AppCoreService()
{
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

// bool AppCoreService::QueryService(const paroc_string &name)
// {
//   if (name==NULL) return false;

//   if (paroc_utils::isEqual(name,"CodeMgr")) return true;
//   if (paroc_utils::isEqual(name,"RemoteLog")) return true;
//   if (paroc_utils::isEqual(name,"ObjectMonitor")) return true;

//   return false;
// }

bool AppCoreService::QueryService(const paroc_string &name, paroc_service_base &service)
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

bool AppCoreService::QueryService(const paroc_string &name, paroc_accesspoint &service)
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

bool AppCoreService::RegisterService(const paroc_string &name, const paroc_service_base &newservice)
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

bool AppCoreService::UnregisterService(const paroc_string &name)
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

	unsigned id;
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
