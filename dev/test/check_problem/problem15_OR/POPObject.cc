#include "POPObject.ph"

POPObject::POPObject() {

    cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject() {
    cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

void POPObject::dummyMethod(bool dummy) {
    cout << "Dummy method called" << popcendl;
    if(dummy || false) {
        cout << "Expression was true" << popcendl;
    } else {
        cout << "Expression was false" << popcendl;
    }
}

@pack(POPObject);