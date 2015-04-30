/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of raw message factory.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_BufferRAWFactory instead of pop_buffer_raw_factory
 */

#include <unistd.h>
#include <stdio.h>

#include "pop_buffer_raw_factory.h"
#include "pop_buffer_raw.h"

pop_buffer_raw_factory::pop_buffer_raw_factory() {
}

pop_buffer* pop_buffer_raw_factory::CreateBuffer() {
    pop_buffer* bufRAW = new pop_buffer_raw();
    return bufRAW;
}

bool pop_buffer_raw_factory::GetBufferName(std::string& bufferName) {
    bufferName = "raw";
    return true;
}
