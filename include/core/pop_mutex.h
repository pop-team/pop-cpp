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

#include <mutex>
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


class paroc_condition: public pop_mutex {
public:
    paroc_condition();
    ~paroc_condition();

    void signal();
    void broadcast();
    void wait();
    bool wait(int timeout);

protected:
    pthread_cond_t _cond;
};

using pop_mutex_locker = std::unique_lock<pop_mutex>;

class POPSynchronizer: public paroc_condition {
public:
    void raise() {
        broadcast();
    }
};

#endif
