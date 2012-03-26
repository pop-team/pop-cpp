#include "myobj3.ph"
#include "myobj4.ph"


MyObj3::MyObj3(POPString machine)
{
	rprintf("Remote object MyObj3 on %s\n",(const char *)POPSystem::GetHost());
}

MyObj3::~MyObj3()
{
	printf("Destroying the object MyObj3 ...\n");
}

void MyObj3::Set(int val)
{
	MyObj4 o1("localhost");
	o1.Set(val);
	data=o1.Get();
}

int MyObj3::Get()
{
	return data + 200;
}

@pack(MyObj3);
