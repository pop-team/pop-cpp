/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of thread used by POP-C++ runtime.
 *
 *
 */

/*
  Should check with C++11 std::thread or std::async
  Deeply need refactoring:
    POPC_Thread instead of paroc_thread
 */

#include "paroc_thread.h"
#include <signal.h>

pthread_mutex_t paroc_thread::objlock=PTHREAD_MUTEX_INITIALIZER;

paroc_thread::paroc_thread(bool joinable) {
    isjoinable=joinable;
    iscreated=false;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, (joinable ? PTHREAD_CREATE_JOINABLE : PTHREAD_CREATE_DETACHED));
    pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);

}

paroc_thread::~paroc_thread() {
    if(iscreated && isjoinable) {
        join();
    }
    pthread_attr_destroy(&attr);
}

void paroc_thread::join() {
    if(iscreated && isjoinable) {
        pthread_join(th,nullptr);
    }
}

void paroc_thread::kill(int sig) {
    if(iscreated) {
        pthread_kill(th,sig);
    }
}

void paroc_thread::cancel() {
    if(iscreated) {
        pthread_cancel(th);
        //      iscreated=false;
    }
}

bool paroc_thread::joinable() {
    return isjoinable;
}

int paroc_thread::create() {
    pthread_mutex_lock(&objlock);
    iscreated=true;
    int ret=pthread_create(&th, &attr, (void *(*)(void*))paroc_thread::_threadentry,this);
    if(ret!=0) {
        iscreated=false;
    }
    pthread_mutex_unlock(&objlock);

    return ret;
}

void *paroc_thread::_threadentry(void *param) {
    pthread_cleanup_push((void (*)(void*))_cleanupentry,param);
    pthread_mutex_lock(&objlock);
    paroc_thread *obj = (paroc_thread *)param;
    pthread_mutex_unlock(&objlock);
    obj->start();
    pthread_cleanup_pop(1);
    return nullptr;
}

void paroc_thread::_cleanupentry(void *param) {
    //  pthread_mutex_lock(&objlock);
    paroc_thread *obj=(paroc_thread *)param;
    //  pthread_mutex_unlock(&objlock);
    if(!obj->joinable()) {
        delete obj;
    }
}

