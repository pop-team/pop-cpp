#include "secondobject.ph"
#include <unistd.h>

/**
 * @author clementval
 * @date 2012.07.11
 * This program tests compilation without the @pack directive. Compilation should work and print a warning message.
 */

SecondObject::SecondObject() : value(10) {
    cout << "SecondObject created on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

SecondObject::~SecondObject() {
    cout << "SecondObject: on machine:" << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

int SecondObject::getValue() {
    return value;
}

