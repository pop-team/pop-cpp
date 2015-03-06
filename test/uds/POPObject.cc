#include "POPObject.ph"

#include <unistd.h>

POPObject::POPObject() {
    cout << "POPObject created (by JobMgr) on machine:" << (const char*)POPSystem::GetHost() << popcendl;
}

POPObject::~POPObject() {
    cout << "POPObject on machine " << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

void POPObject::firstMethod() {
    cout << "First method is called on " << (const char*)POPSystem::GetHost() << popcendl;
}

void POPObject::secondMethod() {
    cout << "Second method is called on " << (const char*)POPSystem::GetHost() <<popcendl;
}

@pack(POPObject);
