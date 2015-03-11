#include "POPObject.ph"
#include <unistd.h>

/**
 * @author clementval
 * @date 2012.07.11
 * This program tests passing array with the standard C++ declaration instead of specific POP-C++ one.
 */

POPObject::POPObject(int x_id) {
    id = x_id;
    cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject() {
    cout << "POPCobject: on machine:" << POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

int POPObject::GetId()
{
    return id;
}

void POPObject::voidMethod(POPObject& o) {
    cout << "Method with void param is called on object "<< GetAccessPoint().GetAccessString() << " (with id=" << GetId() << ")" << popcendl;
    cout << " object " << o.GetAccessPoint().GetAccessString() << " (with id=" << o.GetId() << ") was passed as reference" << popcendl;
}

@pack(POPObject);
