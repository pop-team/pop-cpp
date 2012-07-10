#include "POPObject.ph"

POPObject::POPObject()
{

   cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject()
{
   cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}


void POPObject::transferPOPBaseArray(int n, POPData* d){
	for(int i=0; i < n; i++){
		cout << "POPBase[" << n << "]: " << d[i].getIntData() << popcendl;
	}
}

void POPObject::transferPOPBaseData(POPData d){
	cout << "POPBase: " << d.getIntData() << popcendl;
}

@pack(POPObject);