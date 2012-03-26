#include <stdio.h>
#include "ParObject.ph"

ParObject::ParObject()
{
	printf("Heritparam1: Creating object ParObject on localhost\n");
}

ParObject::ParObject(POPString machine)
{
	printf("Heritparam1: Creating object ParObject on %s\n",(const char *)POPSystem::GetHost());
}

ParObject::ParObject(float f)
{
	printf("Heritparam1: Creating object ParObject with power %f\n",f);
}

ParObject::~ParObject()
{
	printf("Heritparam1: Destroying the object ParObject... %d,%d\n", theData.GetInternalData(), theData.GetMyData());
}

void ParObject::SetData(HeritData data)
{
	theData=data;
}

HeritData ParObject::GetData()
{
	return theData;
}

@pack(ParObject);
