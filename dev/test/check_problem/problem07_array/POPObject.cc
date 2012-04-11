#include "POPObject.ph"

POPObject::POPObject()
{

   cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject()
{
   cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

void POPObject::dummyMethod(int n, int* i){
	cout << "Dummy method called" << popcendl;
	for(int j=0; j < n; j++){
		cout << i[j] << popcendl;	
	}
}

@pack(POPObject);