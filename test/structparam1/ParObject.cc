#include <stdio.h>
#include "ParObject.ph"

ParObject::ParObject()
{
	printf("Structparam1: Creating object ParObject on localhost\n");
}

ParObject::ParObject(POPString machine)
{
	printf("Structparam1: Creating object ParObject on %s\n",(const char *)POPSystem::GetHost());
}

ParObject::ParObject(float f)
{
	printf("Structparam1: Creating object ParObject with power %f\n",f);
}

ParObject::~ParObject()
{
	printf("Structparam1: Destroying the object ParObject... %d,%d\n", theData.GetMyData(), theData.GetInternalData().GetInternalData());
}

void ParObject::SetData(StructData data)
{
	theData=data;
}

StructData ParObject::GetData()
{
	return theData;
}

void ParObject::Get(StructData &data)
{
	data=theData;
}

@pack(ParObject);
