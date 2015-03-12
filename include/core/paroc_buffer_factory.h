/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief buffer factory abstraction.
 *
 *
 */

#ifndef POPC_BUFFER_FACTORY_H
#define POPC_BUFFER_FACTORY_H

#include "paroc_buffer.h"
#include <string>

/*This abstract class declares an interface creating abstract buffer*/
class paroc_buffer;

/**
 * @class paroc_buffer_factory
 * @brief Buffer factory abstraction, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
class paroc_buffer_factory {
public:
    paroc_buffer_factory();
protected:
    virtual ~paroc_buffer_factory();

public:
    virtual void Destroy();

    virtual paroc_buffer* CreateBuffer()=0;

    virtual bool GetBufferName(std::string & bufferName)=0;
};

#endif // POPC_BUFFER_FACTORY_H
