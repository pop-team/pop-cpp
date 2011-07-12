#ifndef _MYOBJ4_PH
#define _MYOBJ4_PH
#include <string.h>
#include <unistd.h>

parclass MyObj4
{
public:
	MyObj4(POPString machine) @{ od.url(machine);};
	~MyObj4();

	seq sync void Set(int val);
	conc int Get();

private:
	int data;
	classuid(4444);
};

#endif
