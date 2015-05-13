#include "demopopc.ph"
#include <unistd.h>

POPCobject::POPCobject(int newID, int wanted, int minp) {
    printf("POPCobject with ID=%d created (by JobMgr) on machine:%s\n", newID,
           GetAccessPoint().GetAccessString().c_str());
    iD = newID;
}

POPCobject::POPCobject(int newID, const std::string& url) {
    printf("POPCobject with ID=%d created on machine:%s\n", newID, GetAccessPoint().GetAccessString().c_str());
    iD = newID;
}

POPCobject::POPCobject(int newID, int node) {
    printf("POPCobject with ID=%d created on machine:%s\n", newID, GetAccessPoint().GetAccessString().c_str());
    iD = newID;
}

POPCobject::~POPCobject() {
    printf("POPCobject:%d on machine:%s is being destroyed\n", iD, GetAccessPoint().GetAccessString().c_str());
    iD = -1;
}

void POPCobject::sendIDto(POPCobject& o) {
    printf("POPCobject:%d on machine:%s is sending his iD to object:%d\n", iD,
           GetAccessPoint().GetAccessString().c_str(), o.getID());
    o.recAnID(iD);
}

int POPCobject::getID() {
    return iD;
}

void POPCobject::recAnID(int i) {
    printf("POPCobject:%d on machine:%s is receiving id = %d\n", iD, GetAccessPoint().GetAccessString().c_str(), i);
}

void POPCobject::wait(int sec) {
    printf("POPCobject:%d on machine:%s is waiting %d sec.\n", iD, GetAccessPoint().GetAccessString().c_str(), sec);
    sleep(sec);
}

@pack(POPCobject);
