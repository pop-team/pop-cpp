/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2009/10/08
 * @brief Thread used in the resource discovery for timeout
 *
 *
 */

#include "paroc_thread.h"

#include <string.h>

class NodeThread : public paroc_thread {
public:
    NodeThread(int timeout, const paroc_accesspoint &node, std::string reqid);
    virtual void start();
    virtual void stop();
private:
    std::string _reqid;
    int _timeout;
    bool _running;
    bool _unlock;
    paroc_accesspoint _node;
};
