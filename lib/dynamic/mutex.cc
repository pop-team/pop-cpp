/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of the mutual exclusive execution.
 *
 *
 */
 
/* 
  Should look inside the std for similar implementation. Must be more efficient. 
  Deeply need refactoring: 
    POPC_Mutex instead of paroc_mutex
    POPC_MutexLocker instead of paroc_mutex_locker
 */

#include <stdio.h>

#include "paroc_mutex.h"
#include <sys/time.h>

/*
*/

paroc_mutex::paroc_mutex()
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
#ifdef _LINUX
	pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE_NP);
#else
	pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
#endif
	if (pthread_mutex_init(&_mutex,&attr)!=0)
	{
		//DEBUG("Multithread initialization fail\n");
		pthread_mutexattr_destroy(&attr);
		return;
	}
	pthread_mutexattr_destroy(&attr);
}

void paroc_mutex::lock()
{
	pthread_mutex_lock(&_mutex);
}

void paroc_mutex::unlock()
{
	pthread_mutex_unlock(&_mutex);
}

paroc_mutex::~paroc_mutex()
{
	pthread_mutex_destroy(&_mutex);
}

/*
POP-C++ condition implementation....
*/

paroc_condition::paroc_condition()
{
	pthread_cond_init(&_cond,NULL);
}

paroc_condition::~paroc_condition()
{
	pthread_cond_destroy(&_cond);
}

void paroc_condition::signal()
{
	pthread_cond_signal(&_cond);
}

void paroc_condition::broadcast()
{
	pthread_cond_broadcast(&_cond);
}

void paroc_condition::wait()
{
	pthread_cond_wait(&_cond,&_mutex);
}

bool paroc_condition::wait(int timeout)
{
	if (timeout<0)
	{
		wait();
		return true;
	}
	else
	{
		struct timespec abstimeout;
		struct timeval now;
		gettimeofday(&now, NULL);
		abstimeout.tv_sec = now.tv_sec + timeout/1000;
		abstimeout.tv_nsec = ( now.tv_usec + (timeout%1000)*1000 )* 1000;
		int ret=pthread_cond_timedwait(&_cond,&_mutex,&abstimeout);
		return (ret==0);
	}

}


paroc_mutex_locker::paroc_mutex_locker(paroc_mutex &_mutex)
{
	pmutex=&_mutex;
	pmutex->lock();
}

paroc_mutex_locker::~paroc_mutex_locker()
{
	pmutex->unlock();
}


