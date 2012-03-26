#include "POPCobject.ph"

POPCobject::POPCobject()
{
	printf("JobManager: POPCobject no.0 (default) created on machine \"%s\"\n", (const char*)POPSystem::GetHost());
	iD=0;
}

POPCobject::POPCobject(int newID, POPString machine)
{
	printf("JobManager: POPCobject no.%d (URL) created on machine \"%s\"\n", newID, (const char*)POPSystem::GetHost());
	iD=newID;
}

POPCobject::POPCobject(int newID, double p)
{
	printf("JobManager: POPCobject no.%d (Power) created on machine \"%s\"\n", newID, (const char*)POPSystem::GetHost());
	iD=newID;
}

POPCobject::POPCobject(int newID, int m)
{
	printf("JobManager: POPCobject no.%d (Memory) created on machine \"%s\"\n", newID, (const char*)POPSystem::GetHost());
	iD=newID;
}

POPCobject::POPCobject(int newID)
{
	printf("JobManager: POPCobject no.%d (Protocol) created on machine \"%s\"\n", newID, (const char*)POPSystem::GetHost());
	iD=newID;
}

POPCobject::~POPCobject()
{
	printf("JobManager: POPCobject no.%d on machine \"%s\" is being destroyed\n", iD, (const char*)POPSystem::GetHost());
	iD=-1;
}

@pack(POPCobject);
