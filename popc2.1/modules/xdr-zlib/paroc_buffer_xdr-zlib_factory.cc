#include <unistd.h>
#include <stdio.h>

#include "paroc_buffer_xdr-zlib_factory.h"
#include "paroc_buffer_xdr-zlib.h"

paroc_buffer_xdr_zlib_factory::paroc_buffer_xdr_zlib_factory()
{
}

paroc_buffer * paroc_buffer_xdr_zlib_factory::CreateBuffer() {
	//  printf("Create xdr-zlib buffer\n");
	paroc_buffer * bufXDR_ZLIB=new paroc_buffer_xdr_zlib();
	return bufXDR_ZLIB;
}

bool paroc_buffer_xdr_zlib_factory::GetBufferName(paroc_string & bufferName) {
	bufferName="xdr-zlib";
	return true;
}


