/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: factory for raw buffer
 */

#ifndef POPC_BUFFER_RAW_FACTORY_H
#define POPC_BUFFER_RAW_FACTORY_H

#include "paroc_buffer_factory.h"

/*This abstract class declares an interface creating abstract combox*/
/**
 * @class paroc_buffer_raw_factory
 * @brief Factory for raw buffer, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
class paroc_buffer_raw_factory:public paroc_buffer_factory {
public:

	paroc_buffer_raw_factory();
	virtual paroc_buffer* CreateBuffer();
	virtual bool GetBufferName(paroc_string & bufferName);

};


#endif // POPC_PROTOCOL_SOCKET_FACTORY_H
