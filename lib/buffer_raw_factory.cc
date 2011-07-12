/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: implementation of raw message factory
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

bool paroc_buffer_raw_factory::GetBufferName(paroc_string & bufferName) {
	bufferName="raw";
	return true;
}


