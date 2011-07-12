/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: implementation of buffer factory for SUN-XDR
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

bool paroc_buffer_xdr_factory::GetBufferName(paroc_string & bufferName) {
	bufferName="xdr";
	return true;
}


