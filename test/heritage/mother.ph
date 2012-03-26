#ifndef _MOTHER_PH_
#define _MOTHER_PH_

parclass Mother
{

	classuid(1002);

public:
	Mother() @{od.url("localhost");};
	virtual int Method1();
	virtual void callMethod(Mother &c, int v);
	void SetVal(int v);
	int GetVal();

protected:
	int val;
};

#endif
