/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Abstract class used for marshall special object
 *
 *
 */

#ifndef _POPC_BASE_SERIALIZABLE
#define _POPC_BASE_SERIALIZABLE

#include <pop_buffer.h>

/**
 * @class pop_base
 * @brief Base class for serializable sequential objects used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * Note : pop_base is equivalent to POPBase. To make a C++ class serializable, it should derive from POPBase and have a defined Serialize() method.
 */
class pop_base {
public:
    virtual ~pop_base() {}
    virtual void Serialize(pop_buffer &buf, bool pack)=0;
};

typedef pop_base POPBase;

#endif
