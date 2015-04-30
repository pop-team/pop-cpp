#include "POPObject.ph"

POPObject::POPObject() {
    cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject() {
    cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() << " is being destroyed" << popcendl;
}
/*
int POPObject::dummyMethod(){
    internal = 10;
    return internal;
}
*/
char* dummyChar() {
    return "Some text";
}

@pack(POPObject);