#ifndef _BYTEDATA_H_
#define _BYTEDATA_H_
#include "noPOPC.h"

class ByteData: public POPBase
{
  public:

    ByteData();
    ~ByteData();
    void Serialize(paroc_buffer &buf, bool pack);

    char* theData;
    int n;
};
#endif

