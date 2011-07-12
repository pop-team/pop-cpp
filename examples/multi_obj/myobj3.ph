#ifndef _MYOBJ3_PH
#define _MYOBJ3_PH
#include <string.h>
#include <unistd.h>

parclass MyObj3
{
public:
	MyObj3(POPString machine) @{ od.url(machine);};
	~MyObj3();

	seq sync void Set(int val);
	conc int Get();

private:
	int data;
	classuid(3333);
};

#endif
