/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: implementation of the event queue
 */

#include <stdio.h>
#include <sys/time.h>

#include "paroc_event.h"

EventQueue::EventQueue()
{
}

EventQueue::~EventQueue()
{
}

void EventQueue::PostEvent(int e)
{
	cond.lock();
	queue.AddTail(e);
	cond.unlock();
	cond.broadcast();
}

int EventQueue::WaitEvent(int e, int timeout)
{
	struct timespec abstimeout;

	cond.lock();

	if (timeout>0)
	{
		struct timeval now;
		gettimeofday(&now, NULL);
		abstimeout.tv_sec = now.tv_sec + timeout/1000;
		abstimeout.tv_nsec = ( now.tv_usec + (timeout%1000)*1000 )* 1000;
	}
	bool done=false;
	while (!done)
	{
		POSITION pos=queue.GetHeadPosition();
		while (pos!=NULL)
		{
			POSITION old=pos;
			int &ev=queue.GetNext(pos);
			if (e==ANY_EVENT || e==ev)
			{
				e=ev;
				queue.RemoveAt(old);
				done=true;
				break;
			}
		}
		if (!done)
		{
			if (timeout<0) cond.wait();
			else if (timeout==0 || cond.wait(timeout)!=0) break;
		}
	}
	cond.unlock();

	if (!done) return -1;

	return e;
}

