/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of buffer factory base class.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_BufferFactory instead of paroc_buffer_factory
 */

#include "paroc_buffer_factory.h"

paroc_buffer_factory::paroc_buffer_factory() {
}

paroc_buffer_factory::~paroc_buffer_factory() {
}

void paroc_buffer_factory::Destroy() {
    delete this;
}

