/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief factory for raw buffer
 *
 *
 */

#ifndef POP_BUFFER_RAW_FACTORY_H
#define POP_BUFFER_RAW_FACTORY_H

#include "pop_buffer_factory.h"

/*This abstract class declares an interface creating abstract combox*/
/**
 * @class pop_buffer_raw_factory
 * @brief Factory for raw buffer, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
class pop_buffer_raw_factory : public pop_buffer_factory {
public:
    pop_buffer_raw_factory();
    virtual pop_buffer* CreateBuffer();
    virtual bool GetBufferName(std::string& bufferName);
};

#endif  // POPC_PROTOCOL_SOCKET_FACTORY_H
