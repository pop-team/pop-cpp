#ifndef _POPCOBJECT_PH_
#define _POPCOBJECT_PH_
#include "bytedata.h"

parclass POPCobject
{
  classuid(1500);

  public:
    POPCobject() @{od.url("localhost");};
    ~POPCobject();
    
    sync  seq  void sendBytesSyncSeq([in, size=n] char* b, int n);
    sync  seq  void sendDataSyncSeq(ByteData b);

    sync  seq float computeFlops(float a, float b);

    async seq  void sendBytesAsyncSeq([in, size=n] char* b, int n);
    async seq  void sendDataAsyncSeq(ByteData b);
        
};

#endif /*_POPCOBJECT_PH_*/
