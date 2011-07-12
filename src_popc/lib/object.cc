#include "paroc_object.h"
#include "paroc_mutex.h"


#include "paroc_interface.h"
#include "paroc_event.h"

#include "objectmonitor.ph"



paroc_object::paroc_object()
{
  refcount=1;

  if (!paroc_system::appservice.IsEmpty())
    {
      paroc_accesspoint myself=GetAccessPoint();
      try 
	{
	  ObjectMonitor tmp(paroc_system::appservice);
	  tmp.ManageObject(myself);
	}
      catch(...)
	{
	  rprintf("Can not register %s to ObjectMonitor service!\n",paroc_system::appservice.GetAccessString());
	}
    }
  
}

paroc_object::~paroc_object()
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
	  rprintf("Can not unregister %s from ObjectMonitor service!\n",paroc_system::appservice.GetAccessString());
	}
    }
}

const paroc_accesspoint & paroc_object::GetAccessPoint() const
{
  return paroc_broker::accesspoint;
}

int paroc_object::GetRefCount() 
{ 
  paroc_mutex_locker t(lock);
  return refcount; 
}

int paroc_object::AddRef()
{
  paroc_mutex_locker t(lock);
  refcount++;
  return refcount;
}

int paroc_object::DecRef()
{
  paroc_mutex_locker t(lock);
  refcount--;
  return refcount;
}


bool  paroc_object::CanKill()
{
  return  true;
}

int paroc_object::eventwait(int event, int timeout)
{
  return _paroc_events.WaitEvent(event, timeout);
}
void paroc_object::eventraise(int event)
{
  _paroc_events.PostEvent(event);
}
