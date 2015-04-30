/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/11/30
 * @brief Implementation of base POPC_Object class. This class is the base class for remote parallel object of a group
 *of
 *        parallel object. A group parallel object is a set of parallel object that can be called in a single or
 *collective way.
 *
 *
 */

#include "popc_object.h"

#include <mpi.h>

/**
 * Base constructor
 */
POPC_Object::POPC_Object() {
}

/**
 * Base destructor
 */
POPC_Object::~POPC_Object() {
}

/**
 * Return the rank of the object in the group
 * @return Integer value representing the rank of the object in its group
 */
int POPC_Object::get_rank() {
    return MPI::COMM_WORLD.Get_rank();
}

/**
 * Return the size of the group in which the object is included
 * @return Integer value representing the size of the object's group
 */
int POPC_Object::get_group_size() {
    return MPI::COMM_WORLD.Get_size();
}