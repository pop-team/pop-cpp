/**
 * File : service_base.cc
 * Author : Tuan Anh Nguyen
 * Description : Base service class
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 */


#include <stdio.h>

#include "paroc_interface.h"
#include "paroc_broker.h"

#include "paroc_service_base.ph"
#include "objectmonitor.ph"

#include <strings.h>

paroc_service_base::paroc_service_base(const paroc_string &challenge):mychallenge(challenge), appservice(paroc_system::appservice)
{
	daemonMode=false;
}

paroc_service_base::paroc_service_base(): appservice(paroc_system::appservice)
{
	daemonMode=false;
}

//Switch to the daemon mode...
void paroc_service_base::Start()
{
	while (GetRefCount()>1) DecRef();
	daemonMode=true;

	if (!paroc_system::appservice.IsEmpty())
	{
		paroc_accesspoint myself=GetAccessPoint();
		try
		{
			ObjectMonitor tmp(paroc_system::appservice);
			tmp.UnManageObject(myself);
			paroc_system::appservice.SetAccessString(NULL);
		}
		catch (...)
		{
			DEBUG("Failed to unregister the service from ObjectMonitor");
		}
	}
}

void paroc_service_base::Start(const paroc_string &challenge)
{
	if (paroc_utils::isEqual(mychallenge,challenge) || mychallenge==NULL)
	{
		while (GetRefCount()>1) DecRef();
		mychallenge=challenge;
		Start();
	}

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


JobCoreService::JobCoreService(const paroc_string &challenge): paroc_service_base(challenge)
{
}

/*
int JobCoreService::CreateObject(const paroc_accesspoint &localservice, const paroc_string &objname, const paroc_od &od, int howmany, paroc_accesspoint *objcontacts)
{
  return POPC_JOBSERVICE_FAIL;
}
*/

