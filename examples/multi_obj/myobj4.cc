#include "myobj4.ph"



MyObj4::MyObj4(POPString machine)
{
	rprintf("Remote object MyObj4 on %s\n",(const char *)POPSystem::GetHost());
}

MyObj4::~MyObj4()
{
	printf("Destroying the object MyObj4 ...\n");
}

void MyObj4::Set(int val)
{
	data=val;
}

int MyObj4::Get()
{
	return data + 1000;
}

@pack(MyObj4);
