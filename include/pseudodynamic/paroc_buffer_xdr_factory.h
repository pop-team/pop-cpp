/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: factory for xdr formatted buffers
 */

#ifndef POPC_BUFFER_XDR_FACTORY_H
#define POPC_BUFFER_XDR_FACTORY_H

#include "paroc_buffer_factory.h"


/**
 * @class paroc_buffer_xdr_factory
 * @brief Factory for xdr formatted buffers, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *  This abstract class declares an interface creating abstract combox
 */
class paroc_buffer_xdr_factory:public paroc_buffer_factory {
public:

	paroc_buffer_xdr_factory();
	virtual paroc_buffer* CreateBuffer();
	virtual bool GetBufferName(paroc_string & bufferName);

};


#endif // POPC_PROTOCOL_SOCKET_FACTORY_H
