#ifndef _POPC_BUFFER_MYENCODING_H
#define _POPC_BUFFER_MYENCODING_H

#include <paroc_array.h>
#include <paroc_buffer_raw.h>

class paroc_buffer_raw_zlib: public paroc_buffer_raw
{
public:
	paroc_buffer_raw_zlib();
	~paroc_buffer_raw_zlib();
	virtual void Reset();
	virtual bool Send(paroc_combox &s, paroc_connection *conn);
	virtual bool Recv(paroc_combox &s, paroc_connection *conn);
};

#endif
