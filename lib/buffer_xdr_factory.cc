/**
 * File : buffer_xdr_factory.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of buffer factory for SUN-XDR
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
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


