#include "demopopc.ph"
#include <unistd.h>

POPCobject::POPCobject(int newID, int wanted, int minp)
{
	printf("POPCobject with ID=%d created (by JobMgr) on machine:%s\n", newID, (const char*)POPSystem::GetHost());
	iD=newID;
}

POPCobject::POPCobject(int newID, POPString machine)
{
	printf("POPCobject with ID=%d created on machine:%s\n", newID, (const char*)POPSystem::GetHost());
	iD=newID;
}

POPCobject::~POPCobject()
{
	printf("POPCobject:%d on machine:%s is being destroyed\n", iD, (const char*)POPSystem::GetHost());
	iD=-1;
}

void POPCobject::sendIDto(POPCobject &o)
{
	printf("POPCobject:%d on machine:%s is sending his iD to object:%d\n", iD, (const char*)POPSystem::GetHost(), o.getID());
	o.recAnID(iD);
}

int  POPCobject::getID()
{
	return iD;
}

void POPCobject::recAnID(int i)
{
	printf("POPCobject:%d on machine:%s is receiving id = %d\n", iD, (const char*)POPSystem::GetHost(), i);
}

void POPCobject::wait(int sec)
{
	printf("POPCobject:%d on machine:%s is waiting %d sec.\n", iD, (const char*)POPSystem::GetHost(), sec);
	sleep(sec);
}

@pack(POPCobject);
