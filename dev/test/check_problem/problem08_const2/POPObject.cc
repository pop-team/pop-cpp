#include "POPObject.ph"

POPObject::POPObject() {
    dummyInt = 10;
    cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject() {
    cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() << " is being destroyed" << popcendl;
}

const int* POPObject::dummyMethod() {
    cout << "Dummy method called" << popcendl;
    return &dummyInt;
}

//@pack(POPObject);