/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief event queue that store/wait/retrieve an event
 *
 */

#ifndef POPC_EVENT_H_
#define POPC_EVENT_H_

#define ANY_EVENT -1

#include <vector>
#include "pop_mutex.h"

/**
 * @class EventQueue
 * @brief Event queue that store/wait/retrieve an event, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class EventQueue {
public:
    EventQueue();
    ~EventQueue();
    void PostEvent(int e);
    int  WaitEvent(int e=ANY_EVENT, int timeout=-1);
    //timeout=0: return imediately if the event did not occur,
    // -1: disable timeout control,
    //otherwise, timeout in "timeout" miliseconds

protected:
    pop_condition cond;
    std::vector<int> queue;
};

#endif
