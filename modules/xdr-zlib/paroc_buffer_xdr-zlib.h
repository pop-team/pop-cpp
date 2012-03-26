#ifndef _POPC_BUFFER_MYENCODING_H
#define _POPC_BUFFER_MYENCODING_H

#include "paroc_array.h"
#include <paroc_buffer_xdr.h>
#include <paroc_combox.h>

class paroc_buffer_xdr_zlib: public paroc_buffer_xdr
{
public:
	paroc_buffer_xdr_zlib();
	~paroc_buffer_xdr_zlib();
	virtual void Reset();
	virtual bool Send(paroc_combox &s, paroc_connection *conn);
	virtual bool Recv(paroc_combox &s, paroc_connection *conn);
};

#endif
