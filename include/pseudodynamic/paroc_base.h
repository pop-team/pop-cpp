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
