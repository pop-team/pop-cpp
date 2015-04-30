#include "POPObject.ph"

POPTest::POPObject::POPObject() {
    cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPTest::POPObject::~POPObject() {
    cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() << " is being destroyed" << popcendl;
}

void POPTest::POPObject::dummyMethod() {
    cout << "Dummy method called" << popcendl;
}

@pack(POPTest::POPObject);
