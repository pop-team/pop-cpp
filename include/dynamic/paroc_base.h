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

#include <paroc_buffer.h>

/**
 * @class paroc_base
 * @brief Base class for serializable sequential objects used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * Note : paroc_base is equivalent to POPBase. To make a C++ class serializable, it should derive from POPBase and have a defined Serialize() method.
 */
class paroc_base
{
public:
	virtual ~paroc_base() {};
	virtual void Serialize(paroc_buffer &buf, bool pack)=0;
};

typedef paroc_base POPBase;

#endif
