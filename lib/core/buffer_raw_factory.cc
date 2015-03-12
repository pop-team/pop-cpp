/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
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
    POPC_BufferRAWFactory instead of paroc_buffer_raw_factory
 */

#include <unistd.h>
#include <stdio.h>

#include "paroc_buffer_raw_factory.h"
#include "paroc_buffer_raw.h"

paroc_buffer_raw_factory::paroc_buffer_raw_factory() {

}

paroc_buffer * paroc_buffer_raw_factory::CreateBuffer() {
    paroc_buffer * bufRAW=new paroc_buffer_raw();
    return bufRAW;
}

bool paroc_buffer_raw_factory::GetBufferName(std::string & bufferName) {
    bufferName="raw";
    return true;
}


