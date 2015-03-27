#include "POPObject.ph"

#include <unistd.h>

POPObject::POPObject(int id) : id(id) {
    cout << "POPObject " << id << " created (by JobMgr) on machine:" << POPSystem::GetHost() << popcendl;
}

POPObject::~POPObject() {
    cout << "POPObject  " << id << " on machine " << POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

void POPObject::firstMethod() {
    cout << "First method is called on POPObject  " << id << " " << POPSystem::GetHost() << popcendl;
}

void POPObject::secondMethod() {
    cout << "Second method is called on POPObject  " << id << " " << POPSystem::GetHost() <<popcendl;
}

@pack(POPObject);
