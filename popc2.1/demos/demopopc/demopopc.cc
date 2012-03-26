#include "demopopc.ph"
#include <unistd.h>

POPCobject::POPCobject(int newID, int wanted, int minp)
{
//	printf("POPCobject with ID=%d created (by JobMgr) on machine:%s\n", newID, (const char*)POPSystem::GetHost());
   cout << "POPCobject with ID=" << newID << " created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
	iD=newID;
}

POPCobject::POPCobject(int newID, POPString machine)
{
//	printf("POPCobject with ID=%d created on machine:%s\n", newID, (const char*)POPSystem::GetHost());
   cout << "POPCobject with ID="<< newID <<" created on machine:"<< (const char*)POPSystem::GetHost() << popcendl;
	iD=newID;
}

POPCobject::~POPCobject()
{
//	printf("POPCobject:%d on machine:%s is being destroyed\n", iD, (const char*)POPSystem::GetHost());
   cout << "POPCobject:"<< iD << " on machine:" << (const char*)POPSystem::GetHost() <<" is being destroyed\n" << popcendl;
	iD=-1;
}

void POPCobject::sendIDto(POPCobject &o)
{
	//printf("POPCobject:%d on machine:%s is sending his iD to object:%d\n", iD, (const char*)POPSystem::GetHost(), o.getID());
   cout << "POPCobject:" << iD <<" on machine:"<< (const char*)POPSystem::GetHost() << " is sending his iD to object:" << o.getID() << popcendl;
	o.recAnID(iD);
}

int  POPCobject::getID()
{
	return iD;
}

void POPCobject::recAnID(int i)
{
//	printf("POPCobject:%d on machine:%s is receiving id = %d\n", iD, (const char*)POPSystem::GetHost(), i);
   cout << "POPCobject:" << iD << " on machine:" << (const char*)POPSystem::GetHost()<< " is receiving id =" << i << popcendl;
}

void POPCobject::wait(int sec)
{
//	printf("POPCobject:%d on machine:%s is waiting %d sec.\n", iD, (const char*)POPSystem::GetHost(), sec);
   cout << "POPCobject:" << iD << " on machine:" << (const char*)POPSystem::GetHost() << " is waiting "<< sec <<" sec" << popcendl;
	sleep(sec);
}

@pack(POPCobject);
