#include <stdio.h>
#include "ParObject.ph"

ParObject::ParObject()
{
	printf("VectorInt1: Creating object ParObject on localhost\n");
}

ParObject::ParObject(POPString machine)
{
	printf("VectorInt1: Creating object ParObject on %s\n",(const char *)POPSystem::GetHost());
}

ParObject::ParObject(float f)
{
	printf("VectorInt1: Creating object ParObject with power %f\n",f);
}

ParObject::~ParObject()
{
	printf("VectorInt2: Destroying the object ParObject... %d, %d\n",  theData.size(), theData.GetMyData());
}

void ParObject::SetData(POPintVector data)
{
	theData=data;
}

POPintVector ParObject::GetData()
{
	return theData;
}

@pack(ParObject);
