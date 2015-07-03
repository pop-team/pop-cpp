/**
 * File : event.cc
 * Author : Tuan Anh Nguyen
 * Description : implementation of the event queue
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 */

#include "pop_intface.h"
//#include <stdio.h>
//#include <sys/time.h>

#include "pop_event.h"

EventQueue::EventQueue() {
}

EventQueue::~EventQueue() {
}

void EventQueue::PostEvent(int e) {
    cond.lock();
    queue.push_back(e);
    cond.unlock();
    cond.broadcast();
}

int EventQueue::WaitEvent(int e, int timeout) {
    cond.lock();

    if (timeout > 0) {
        struct timeval now;
        popc_gettimeofday(&now, nullptr);
    }
    bool done = false;
    while (!done) {
        auto pos = queue.begin();
        while (pos != queue.end()) {
            auto old = pos;
            int& ev = *pos++;
            if (e == ANY_EVENT || e == ev) {
                e = ev;
                pos = queue.erase(old);
                done = true;
                break;
            }
        }
        if (!done) {
            if (timeout < 0) {
                cond.wait();
            } else if (timeout == 0 || cond.wait(timeout) != 0) {
                break;
            }
        }
    }
    cond.unlock();

    if (!done) {
        return -1;
    }

    return e;
}
