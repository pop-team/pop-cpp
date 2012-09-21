#include <stdio.h>
#include "ParObject.ph"

ParObject::ParObject()
{
	printf("VectorX: Creating object ParObject on localhost\n");
}

ParObject::ParObject(POPString machine)
{
	printf("VectorX: Creating object ParObject on %s\n",(const char *)POPSystem::GetHost());
}

ParObject::ParObject(float f)
{
	printf("VectorX: Creating object ParObject with power %f\n",f);
}

ParObject::~ParObject()
{
	printf("VectorX: Destroying the object ParObject... %d\n",  theData.size());
}

void ParObject::SetData(POPxVector data)
{
	theData=data;
}

POPxVector ParObject::GetData()
{
	return theData;
}

@pack(ParObject);
