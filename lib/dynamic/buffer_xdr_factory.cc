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
    POPC_BufferXDRFactory instead of paroc_buffer_xdr_factory
 */

#include <unistd.h>
#include <stdio.h>

#include "paroc_buffer_xdr_factory.h"
#include "paroc_buffer_xdr.h"

paroc_buffer_xdr_factory::paroc_buffer_xdr_factory() {

}

paroc_buffer * paroc_buffer_xdr_factory::CreateBuffer() {
	paroc_buffer * bufXDR=new paroc_buffer_xdr();
	return bufXDR;
}

bool paroc_buffer_xdr_factory::GetBufferName(POPString & bufferName) {
	bufferName="xdr";
	return true;
}


