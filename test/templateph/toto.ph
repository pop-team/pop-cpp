#ifndef _TOTO_PH
#define _TOTO_PH

#include "ClassA.h"
#include "ClassA.cc"
#include "X.h"

parclass Toto
{
	classuid(1001);

public:
	Toto() @{od.url("localhost");};
	Toto(POPString machine) @{od.url(machine);};

	~Toto();
	seq async void SetIdent(int id);
	conc sync int GetIdent();

private:
	ClassA<X> t;
};

#endif
