#ifndef _MYOBJ2_PH
#define _MYOBJ2_PH
#include <string.h>
#include <unistd.h>

parclass MyObj2
{
public:
	MyObj2(POPString machine) @{ od.url(machine);};
	~MyObj2();

	seq sync void Set(int val);
	conc int Get();

private:
	int data;
	classuid(2222);
};

#endif
