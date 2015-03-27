#include "POPObject.ph"

#include <unistd.h>

POPObject::POPObject() {
    cout << "POPObject created (by JobMgr) on machine:" << POPSystem::GetHost() << popcendl;
}

POPObject::~POPObject() {
    cout << "POPObject on machine " << POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

void POPObject::firstMethod() {
    cout << "First method is called on " << POPSystem::GetHost() << popcendl;
}

void POPObject::secondMethod() {
    cout << "Second method is called on " << POPSystem::GetHost() <<popcendl;
}

@pack(POPObject);
