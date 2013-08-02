#ifndef _CWORKER_PH
#define _CWORKER_PH
#include "Barrier.ph"

parclass Cworker
{
  classuid(1002);
  public: 
    Cworker() @{ od.node(1); od.executable("./Cworker.obj"); };
    Cworker(int No) @{od.node(1); od.executable("./Cworker.obj");};
    
    async seq void Work(POP_Barrier &b);
    sync seq void SetNo(int no);
    sync seq int GetNo();

  private:
    int myNo;
};
#endif
 
