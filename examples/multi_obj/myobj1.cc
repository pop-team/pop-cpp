#include "myobj1.ph"
#include "myobj2.ph"


MyObj1::MyObj1(POPString machine)
{
	rprintf("Remote object MyObj1 on %s\n",(const char *)POPSystem::GetHost());
}

MyObj1::~MyObj1()
{
	printf("Destroying the object MyObj1 ...\n");
}

void MyObj1::Set(int val)
{
	MyObj2 o1("localhost");
	o1.Set(val);
	data=o1.Get();
}

int MyObj1::Get()
{
	return data + 4;
}

@pack(MyObj1);
