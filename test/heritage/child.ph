#ifndef _CHILD_PH_
#define _CHILD_PH_
#include "mother.ph"

parclass Child : public Mother
{

	classuid(1001);

public:
	Child() @{od.url("localhost");};
	virtual int Method1();
	virtual void callMethod(Mother &c, int v);
};

#endif
