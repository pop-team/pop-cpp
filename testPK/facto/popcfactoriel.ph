#ifndef _POPCFACTORIEL_PH_
#define _POPCFACTORIEL_PH_

parclass POPCfactoriel
{
  classuid(1500);

  public:
    POPCfactoriel()@{od.url("localhost");}; 
    POPCfactoriel(POPString machine)@{od.url(machine);};
    ~POPCfactoriel();
    
    sync seq  int compute(int f);
    sync conc int computeConc(int f);
    sync seq  int computeSeq(int f);
};

#endif /*_POPCFACTORIEL_PH_*/
