#include <stdio.h>
#include "popcfactoriel.ph"

POPCfactoriel::POPCfactoriel()
{
  printf("Facto: object POPCfactoriel created on machine '%s'\n", POPGetHost()); 
}

POPCfactoriel::POPCfactoriel(POPString machine)
{
  printf("Facto: object POPCfactoriel created on machine '%s'\n", POPGetHost()); 
}

POPCfactoriel::~POPCfactoriel()
{
  printf("Facto: object POPCfactoriel on machine '%s' is being destroyed\n", POPGetHost()); 
}

int  POPCfactoriel::compute(int f)
{
  printf("Facto: call 'this->computeConc(f)'\n");
  int f1 = this->computeConc(f);
  printf("Facto: call 'computeSeq(f)'\n");
  int f2 = computeSeq(f);
  if (f1==f2) return f1;
  else return -1;
}

int  POPCfactoriel::computeConc(int f)
{
  printf("Facto: Inside 'computeConc(%d)'\n", f);
  if (f<0) return -1;
  else
    if (f<2) return 1;
    else
      return f * (/*this->*/computeConc(f-1));
}

int  POPCfactoriel::computeSeq(int f)
{
  if (f<0) return -1;
  else
    if (f<2) return 1;
    else
      return f * computeSeq(f-1);
}

@pack(POPCfactoriel);

