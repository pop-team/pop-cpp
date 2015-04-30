#include "POPObject.ph"
#include <unistd.h>

POPObject::POPObject() {
    cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject() {
    cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() << " is being destroyed" << popcendl;
}

@pack(POPObject);