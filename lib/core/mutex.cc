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
    POPC_Mutex instead of pop_mutex
    POPC_MutexLocker instead of pop_mutex_locker
 */
#include "popc_intface.h"

//#include <stdio.h>

#include "pop_mutex.h"
#include "popc_logger.h"
//#include <sys/time.h>

/*
*/

pop_mutex::pop_mutex() {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
#ifdef _LINUX
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE_NP);
#else
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
#endif
    if(pthread_mutex_init(&_mutex,&attr)!=0) {
        LOG_WARNING("Multithread initialization fail");
        pthread_mutexattr_destroy(&attr);
        return;
    }
    pthread_mutexattr_destroy(&attr);
}

void pop_mutex::lock() {
    pthread_mutex_lock(&_mutex);
}

void pop_mutex::unlock() {
    pthread_mutex_unlock(&_mutex);
}

pop_mutex::~pop_mutex() {
    pthread_mutex_destroy(&_mutex);
}

/*
POP-C++ condition implementation....
*/

pop_condition::pop_condition() {
    pthread_cond_init(&_cond,nullptr);
}

pop_condition::~pop_condition() {
    pthread_cond_destroy(&_cond);
}

void pop_condition::signal() {
    pthread_cond_signal(&_cond);
}

void pop_condition::broadcast() {
    pthread_cond_broadcast(&_cond);
}

void pop_condition::wait() {
    pthread_cond_wait(&_cond,&_mutex);
}

bool pop_condition::wait(int timeout) {
    if(timeout<0) {
        wait();
        return true;
    } else {
        struct timespec abstimeout;
        struct timeval now;
        popc_gettimeofday(&now, nullptr);
        abstimeout.tv_sec = now.tv_sec + timeout/1000;
        abstimeout.tv_nsec = (now.tv_usec + (timeout%1000)*1000)* 1000;
        int ret=pthread_cond_timedwait(&_cond,&_mutex,&abstimeout);
        return (ret==0);
    }

}

/*
POP-C++ locker implementation....
*/



pop_mutex_locker::pop_mutex_locker(pop_mutex &_mutex) {
    pmutex=&_mutex;
    pmutex->lock();
}

pop_mutex_locker::~pop_mutex_locker() {
    pmutex->unlock();
}


