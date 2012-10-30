#ifndef _TITI_PH
#define _TITI_PH
#include "toto.ph"

parclass Titi         
{

classuid(1001);

public:
  Titi() @{ od.node(1); od.executable("/Users/clementval/versioning/popc/popc2.6.2/test/callback/titi.obj"); };
        
  ~Titi();

  seq sync void SetIdent(int i);
  seq sync void ComputeIdent(Toto &t);	

private:
  int ident;
};
#endif
