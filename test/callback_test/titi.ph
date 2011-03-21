#ifndef _TITI_PH
#define _TITI_PH
#include "toto.ph"

parclass Titi
{
	classuid(1001);
public:
	Titi() @{od.url("localhost");};

	~Titi();

	seq sync void SetIdent(int i);
	seq sync void ComputeIdent(Toto &t);

private:
	int ident;
};
#endif
