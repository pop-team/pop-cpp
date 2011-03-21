#ifndef POPC_BUFFER_RAW_ZLIB_FACTORY_H
#define POPC_BUFFER_RAW_ZLIB_FACTORY_H

#include "paroc_buffer_factory.h"

/*This abstract class declares an interface creating abstract combox*/
class paroc_buffer_raw_zlib_factory:public paroc_buffer_factory {
public:

	paroc_buffer_raw_zlib_factory();
	virtual paroc_buffer* CreateBuffer();
	virtual bool GetBufferName(paroc_string & bufferName);

};


#endif // POPC_PROTOCOL_SOCKET_FACTORY_H
