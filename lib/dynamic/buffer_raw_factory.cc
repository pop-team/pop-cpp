/**
 * File : buffer_raw_factory.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of raw message factory
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
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

bool paroc_buffer_raw_factory::GetBufferName(POPString & bufferName) {
	bufferName="raw";
	return true;
}


