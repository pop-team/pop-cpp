#include "myobj2.ph"
#include "myobj3.ph"


MyObj2::MyObj2(POPString machine)
{
	rprintf("Remote object MyObj2 on %s\n",(const char *)POPSystem::GetHost());
}

MyObj2::~MyObj2()
{
	printf("Destroying the object MyObj2 ...\n");
}

void MyObj2::Set(int val)
{
	MyObj3 o1("localhost");
	o1.Set(val);
	data=o1.Get();
}

int MyObj2::Get()
{
	return data + 30;
}

@pack(MyObj2);
