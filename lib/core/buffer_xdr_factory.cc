/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of buffer factory for SUN-XDR.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_BufferXDRFactory instead of pop_buffer_xdr_factory
 */

#include <unistd.h>
#include <stdio.h>

#include "pop_buffer_xdr_factory.h"
#include "pop_buffer_xdr.h"

pop_buffer_xdr_factory::pop_buffer_xdr_factory() {

}

pop_buffer * pop_buffer_xdr_factory::CreateBuffer() {
    pop_buffer * bufXDR=new pop_buffer_xdr();
    return bufXDR;
}

bool pop_buffer_xdr_factory::GetBufferName(std::string & bufferName) {
    bufferName="xdr";
    return true;
}


