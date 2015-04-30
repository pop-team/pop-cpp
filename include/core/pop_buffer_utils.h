/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Marshall function
 *
 *
 */

#ifndef _POP_BUFFER_UTILS_H
#define _POP_BUFFER_UTILS_H

#include <string>
#include "pop_buffer.h"
#include "pop_memspool.h"

template <class T>
void packarray(pop_buffer& buf, T* param, int size, int flag, pop_memspool* temp);

#endif
