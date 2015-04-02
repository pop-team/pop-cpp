/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief mutex control and synchronizer
 *
 *
 */


#ifndef _POPC_MUTEX_H
#define _POPC_MUTEX_H
#include <pthread.h>

/**
 * @class pop_mutex
 * @brief Mutex control and synchronizer, used by POP-C++ runtime.
 *
 * @author Tuan Anh Nguyen
 */

class pop_mutex {
public:
    pop_mutex();
    ~pop_mutex();
    void lock();
    void unlock();
protected:
    pthread_mutex_t _mutex;
};


class pop_condition: public pop_mutex {
public:
    pop_condition();
    ~pop_condition();

    void signal();
    void broadcast();
    void wait();
    bool wait(int timeout);

protected:
    pthread_cond_t _cond;
};

//Note(BW): Ideally, this should be replaced by std unique_lock. Unfortunately, this is used in the parser, so this would
//mean that C++11 compilation is necessary for the POP programs. This has to be discussed

class pop_mutex_locker {
public:
    pop_mutex_locker(pop_mutex &_mutex);
    ~pop_mutex_locker();
private:
    pop_mutex *pmutex;
};

class POPSynchronizer: public pop_condition {
public:
    void raise() {
        broadcast();
    }
};

#endif
