#ifndef _CWORKER_PH
#define _CWORKER_PH
#include "barrier.ph"

parclass Cworker
{
	classuid(1002);

public:
	Cworker() @{od.url("localhost");};
	Cworker(int No) @{od.url("localhost");};

	async seq void Work(POP_Barrier &b);
	sync seq void SetNo(int no);
	sync seq int GetNo();

private:
	int myNo;
};
#endif

