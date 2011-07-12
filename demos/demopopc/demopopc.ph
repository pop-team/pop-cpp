#ifndef POPCOBJECT_PH_
#define POPCOBJECT_PH_

#include <timer.h>

parclass POPCobject
{
	classuid(1500);

public:
	POPCobject(int newID, int wanted, int minp) @{od.power(wanted, minp);};
	POPCobject(int newID, POPString machine) @{od.url(machine);};
	~POPCobject();

	async seq void sendIDto([in] POPCobject &o);
	sync conc int getID();
	async conc void recAnID(int i);
	sync mutex void wait(int sec);

private:
	int iD;
	Timer timer;
	double initTime, computeTime;

};

#endif /*POPCOBJECT_PH_*/
