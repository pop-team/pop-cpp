#include "POPObject.ph"
#include <unistd.h>

using namespace poptest;

POPObject::POPObject() {
    cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject() {
    cout << "POPCobject: on machine:" << POPSystem::GetHost().c_str() <<" is being destroyed" << popcendl;
}


void POPObject::testMethod() {
    cout << "Call testMethod" << popcendl;
}

@pack(POPObject);
