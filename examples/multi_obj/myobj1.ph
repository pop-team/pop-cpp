#ifndef _MYBJ1_PH
#define _MYOBJ1_PH
#include <string.h>
#include <unistd.h>

parclass MyObj1
{
public:
	MyObj1(POPString machine) @{ od.url(machine);};
	~MyObj1();

	seq sync void Set(int val);
	conc int Get();

private:
	int data;
	classuid(1111);
};

#endif
