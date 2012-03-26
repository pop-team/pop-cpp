#include <unistd.h>
#include <stdio.h>

#include "paroc_buffer_raw-zlib_factory.h"
#include "paroc_buffer_raw-zlib.h"

paroc_buffer_raw_zlib_factory::paroc_buffer_raw_zlib_factory()
{
}

paroc_buffer * paroc_buffer_raw_zlib_factory::CreateBuffer() {
	paroc_buffer * bufRAW_ZLIB=new paroc_buffer_raw_zlib();
	return bufRAW_ZLIB;
}

bool paroc_buffer_raw_zlib_factory::GetBufferName(paroc_string & bufferName) {
	bufferName="raw-zlib";
	return true;
}


