/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief buffer factory abstraction.
 *
 *
 */

#ifndef POP_BUFFER_FACTORY_H
#define POP_BUFFER_FACTORY_H

#include "pop_buffer.h"
#include <string>

/*This abstract class declares an interface creating abstract buffer*/
class pop_buffer;

/**
 * @class pop_buffer_factory
 * @brief Buffer factory abstraction, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
class pop_buffer_factory {
public:
    pop_buffer_factory();
    virtual ~pop_buffer_factory();

public:
    virtual pop_buffer* CreateBuffer() = 0;

    virtual bool GetBufferName(std::string& bufferName) = 0;
};

#endif  // POPC_BUFFER_FACTORY_H
