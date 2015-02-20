#include "POPObject.ph"
#include <unistd.h>

POPObject::POPObject() {
    cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject() {
    cout << "POPCobject: on machine:" << POPSystem::GetHost().c_str() <<" is being destroyed" << popcendl;
}

void POPObject::executeSmthToday(int sem) {
    if(sem == MON) {
        cout << "This is Monday" <<  popcendl;
    } else if(sem == TUE) {
        cout << "This is Tuesday" <<  popcendl;
    } else if(sem == WED) {
        cout << "This is Wednesday" <<  popcendl;
    } else if(sem == THU) {
        cout << "This is Thrusday" <<  popcendl;
    } else if(sem == FRI) {
        cout << "This is Friday" <<  popcendl;
    } else if(sem == SAT) {
        cout << "This is Saturday" <<  popcendl;
    } else if(sem == SUN) {
        cout << "This is Sunday" <<  popcendl;
    }
}

void POPObject::executeSmthThisMonth(int sem) {
    if(sem == JAN) {
        cout << "This is January" <<  popcendl;
    } else if(sem == FEB) {
        cout << "This is February" <<  popcendl;
    } else if(sem == MAR) {
        cout << "This is March" <<  popcendl;
    } else if(sem == APR) {
        cout << "This is April" <<  popcendl;
    } else if(sem == MAY) {
        cout << "This is May" <<  popcendl;
    } else if(sem == JUN) {
        cout << "This is June" <<  popcendl;
    } else if(sem == JUL) {
        cout << "This is July" <<  popcendl;
    } else if(sem == AUG) {
        cout << "This is August" <<  popcendl;
    } else if(sem == SEP) {
        cout << "This is September" <<  popcendl;
    } else if(sem == OCT) {
        cout << "This is October" <<  popcendl;
    } else if(sem == NOV) {
        cout << "This is November" <<  popcendl;
    } else if(sem == DEC) {
        cout << "This is December" <<  popcendl;
    }
}

@pack(POPObject);
