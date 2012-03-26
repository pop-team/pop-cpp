#ifndef POPCOBJECT_PH_
#define POPCOBJECT_PH_

#include <timer.h>
#include <string.h>

using namespace std;

parclass POPCobject
{
	classuid(1500);

public:
	POPCobject();
	POPCobject(int newID, POPString machine) @{od.url(machine);};
	POPCobject(int newID) @{od.protocol("socket http");};
	POPCobject(int newID, double p) @{od.power(p,p/2.0);};
	POPCobject(int newID, int m) @{od.memory(m, m/2);};
	/*POPCobject(int newID, int m) @{od.directory(m, m/2);};
	POPCobject(int newID, int m) @{od.directory(m, m/2);};*/
	~POPCobject();

private:
	int iD;
};

#endif /*POPCOBJECT_PH_*/
