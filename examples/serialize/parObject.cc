#include <stdio.h>
#include "parObject.ph"

ParObject::ParObject()
{
	printf("Creation of object of class ParObject on localhost\n");
	theData.SetInternalData(0);
}

ParObject::ParObject(POPString machine)
{
	printf("Creation of object of class ParObject on  %s\n",
		   (const char *)POPSystem::GetHost());
	theData.SetInternalData(1);
}

ParObject::ParObject(float f)
{
	printf("Creation of object of class ParObject with power %f\n",f);
	theData.SetInternalData(2);
}

ParObject::~ParObject()
{
	printf("Destroying object of class ParObject... %d\n", theData.GetInternalData());
}

void ParObject::SetData(Data data)
{
	theData=data;
}

Data ParObject::GetData()
{
	return theData;
}

@pack(ParObject);
