#ifndef _MOTHER_PH_
#define _MOTHER_PH_

parclass Mother
{

	classuid(1002);

public:
	Mother() @{ od.node(1); od.executable("./child.obj"); };
	virtual int Method1();
	virtual void callMethod([in]Mother &c, int v);
	void SetVal(int v);
	int GetVal();

protected:
	int val;
};

#endif
