#include "POPObject.ph"
#include <unistd.h>

POPObject::POPObject()
{
	banana.weight = 0.625;
	apple.weight = 0.500;
   cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
   
   cout << "Apple weight is:" << apple.weight << " Banana weight is: " << banana.weight << popcendl;
}

POPObject::~POPObject()
{
   cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

@pack(POPObject);