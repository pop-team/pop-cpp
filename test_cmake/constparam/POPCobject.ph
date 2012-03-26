#ifndef POPCOBJECT_PH_
#define POPCOBJECT_PH_

#include <timer.h>
#include "structdata.h"

parclass POPCobject
{
  classuid(1500);

  public:
    POPCobject() @{od.url("localhost");};
    ~POPCobject();
    
    sync  seq void m2(POPCobject const &o);
 
    sync  seq void m4(StructData const &d);

    async seq void m300(StructData const d);

    sync  seq void m400(StructData const d);

    sync  seq const StructData m12(int v);
    
    sync  seq POPCobject const &m20(); 
      
};

#endif /*POPCOBJECT_PH_*/
