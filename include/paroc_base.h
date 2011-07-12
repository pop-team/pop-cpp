#ifndef _PAROC_BASE_SERIALIZABLE
#define _PAROC_BASE_SERIALIZABLE

#include <paroc_buffer.h>

class paroc_base
{
 public:
  virtual void Serialize(paroc_buffer &buf, bool pack)=0;
};
typedef paroc_base POPBase;
#endif
