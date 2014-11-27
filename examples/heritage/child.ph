#ifndef _CHILD_PH
#define _CHILD_PH
#include "mother.ph"

parclass Child : public Mother  // Inherit form Mother class
{
	classuid(1001);

public:
	Child() @{od.url("localhost");};

	virtual int Method1();
	virtual void callMethod(Mother &c, int v);

};
#endif
