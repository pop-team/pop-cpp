/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/11/30
 * @brief Declaration of base POPC_Object class. This class is the base class for remote parallel object of a group of
 *        parallel object. A group parallel object is a set of parallel object that can be called in a single or
 *collective way.
 *
 *
 */

#ifndef POP_OBJECT_H_
#define POP_OBJECT_H_

#include "pop_accesspoint.h"

class POPC_Object {
public:
    POPC_Object();
    virtual ~POPC_Object();

protected:
    virtual int get_rank();
    virtual int get_group_size();
};

#endif /* POPC_OBJECT_H_ */
