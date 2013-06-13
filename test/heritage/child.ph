#ifndef _CHILD_PH_
#define _CHILD_PH_
#include "mother.ph"

parclass Child : public Mother
{

	classuid(1001);

public:
	Child() @{ od.node(1); od.executable("./child.obj"); };
	virtual int Method1();
	virtual void callMethod([in]Mother &c, int v);
};

#endif
