#include "POPObject.ph"

POPObject::POPObject()
{

   cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject()
{
   cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

void POPObject::dummyMethod(const bool dummy){
	cout << "Dummy method called" << popcendl;
	//	dummy = false; AS EXPECTED, THE PARAMETER IS CONST AND CANNOT BE CHANGED
}

void POPObject::dummyMethodConst() const {
	cout << "Dummy method called" << popcendl;
	dummyInt = 10;
}

@pack(POPObject);