#include "popobject.ph"
#include "secondobject.ph"

#include <unistd.h>

/**
 * @author clementval
 * @date 2012.07.11
 * This program tests compilation without the @pack directive. Compilation should work and print a warning message.
 */

POPObject::POPObject() {
    cout << "POPObject created on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject() {
    cout << "POPObject: on machine:" << POPSystem::GetHost() << " is being destroyed" << popcendl;
}

void POPObject::createSecondObject() {
    SecondObject second;
    cout << "Get value from SecondObject: " << second.getValue() << popcendl;
}
