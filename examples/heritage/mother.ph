#ifndef _MOTHER_PH
#define _MOTHER_PH

parclass Mother
{
	classuid(1000);

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
