#include "POPObject.ph"

POPObject::POPObject() {
    cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject() {
    cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() << " is being destroyed" << popcendl;
}

void POPObject::transferPOPBaseData(const POPData d) {
    int i = d.getIntData();
    cout << "POPBase: " << i << popcendl;
}

@pack(POPObject);