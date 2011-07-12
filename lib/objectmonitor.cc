/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: implementation of the object monitor service
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "objectmonitor.ph"

static IMPLEMENT_TYPE(ObjectMonitor) *myObjMonitor=NULL;

static void LocalServiceTerminate(int sig)
{
	printf("LOCAL SERVICE SIGNAL %d!!!!\n",sig);
	if (myObjMonitor!=NULL) myObjMonitor->KillAll();
	_exit(1);
}

ObjectMonitor::ObjectMonitor(const paroc_string &challenge): paroc_service_base(challenge)
{
	myObjMonitor=this;
	signal(SIGINT,LocalServiceTerminate);
	signal(SIGKILL,LocalServiceTerminate);
	signal(SIGTERM,LocalServiceTerminate);
	isActive=true;
}

ObjectMonitor::~ObjectMonitor()
{
}

void ObjectMonitor::KillAll()
{
	mutex
	{
		printf("Kill all parallel objects are requested\n");
		POSITION pos=objects.GetHeadPosition();
		while (pos!=NULL)
		{
			paroc_accesspoint &t=objects.GetNext(pos);
			try
			{
				paroc_interface tmp(t);
				tmp.Kill();
			}
			catch (...)
			{
			}
		}
		objects.RemoveAll();
	}
}

int ObjectMonitor::CheckObjects()
{
	mutex
	{
		POSITION pos=objects.GetHeadPosition();
		bool active=false;

		while (pos!=NULL)
		{
			POSITION old=pos;
			paroc_accesspoint &t=objects.GetNext(pos);
			try
			{
				paroc_interface test(t);
				if (!active && test.ObjectActive()) active=true;
				if (!active && !isActive) test.DecRef();
			}
			catch (...)
			{
				objects.RemoveAt(old);
			}
		}
		isActive=active;

		DEBUG("Check parallel objects....%d object alive", objects.GetCount());
		return objects.GetCount();
	}
}

void ObjectMonitor::ManageObject(paroc_accesspoint &p)
{
	mutex {
		const char *newstr=p.GetAccessString();
		POSITION pos=objects.GetHeadPosition();
		while (pos!=NULL)
		{
			paroc_accesspoint &t=objects.GetNext(pos);
			if (paroc_utils::isEqual(t.GetAccessString(), newstr)) return;
		}
		objects.AddTail(p);
	}
}

void ObjectMonitor::UnManageObject(paroc_accesspoint &p)
{
	mutex {
		const char *newstr=p.GetAccessString();
		POSITION pos=objects.GetHeadPosition();
		while (pos!=NULL)
		{
			POSITION old=pos;
			paroc_accesspoint &t=objects.GetNext(pos);
			if (paroc_utils::isEqual(t.GetAccessString(), newstr))
			{
				objects.RemoveAt(old);
				return;
			}
		}
		//    DEBUG("ObjectMonitor: unable to unmanage ap: %s",newstr);
	}
}

