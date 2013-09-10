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
    
    //async void m1(POPCobject &o); // ref. parameters not allowed for async 
    sync  void m2(POPCobject &o);   // OK

    //async void m100(POPCobject o);  // forbidden must be passed as &o 
    //sync  void m200(POPCobject o);  // forbidden must be passed as &o

    //async void m3(StructData &d); // ref. parameters not allowed for async 
    sync  void m4(StructData &d);   // OK

    async void m300(StructData d);  // OK
    sync  void m400(StructData d);  // OK

    async void m5([in,size=sizeof(*o)] POPCobject* o);// pointer allowed only if
    sync  void m6([in,size=sizeof(*o)] POPCobject* o);// used with in, out, size
                                                      // directives
                              // but creates a "Segmentation fault" at execution
                              // probably because size is not correct 

    async void m7([in,size=sizeof(*d)] StructData* d);  // pointer allowed only 
    sync  void m8([in,size=sizeof(*d)] StructData* d);  // if used with in, out,
                                                       // size directives
                              // but creates a "Segmentation fault" at execution
                              // probably because size is not correct 


    //async POPCobject m9(); // async cannot return anything
    //sync  POPCobject m10();  // POP-C++ bug: is accepted but put a warning
                             // that it is treated as with a & (see m20)
                             // Corrected in version 2.0

    //async StructData m11();    // async cannot return anything
    sync  StructData m12(int v); // OK

    //async POPobject* m13(); // pointers are
    //sync  POPobject* m14(); // not allowed as parameters

    //async StructData* m15(); // pointers are
    //sync  StructData* m16(); // not allowed as parameters

    //async POPCobject& m17(); // async cannot return a value
    //sync  StructData& m18(); // Non sens in POP-C++, equivalent without &
   
    //async StructData& m19();  // async cannot have ref. parameter
    sync  POPCobject& m20();  // POP-C++ limitation, HACK: remove & (see m10)
                                // Corrected in version 2.0
      
};

#endif /*POPCOBJECT_PH_*/
