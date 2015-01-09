/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief factory for xdr formatted buffers
 *
 *
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
