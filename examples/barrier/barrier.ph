#ifndef _BARRIER_PH
#define _BARRIER_PH

parclass POP_Barrier
{
	classuid(1001);

public:
	POP_Barrier() @{od.url("localhost");};
	POP_Barrier(int n) @{od.url("localhost");};

	sync conc void activate();

private:
	POPSynchronizer event;
	int counter;
};
#endif

