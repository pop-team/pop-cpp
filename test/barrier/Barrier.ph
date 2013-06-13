#ifndef _BARRIER_PH
#define _BARRIER_PH

parclass POP_Barrier 
{
  classuid(1001);
  public: 
    POP_Barrier() @{od.node(1); od.executable("./Barrier.obj");};
    POP_Barrier(int n) @{od.node(1); od.executable("./Barrier.obj");};
  
    sync conc void activate();
    
  private:
   POPSynchronizer event;
   int counter;
};
#endif

