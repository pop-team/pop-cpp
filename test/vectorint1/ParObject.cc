#include <stdio.h>
#include "ParObject.ph"

ParObject::ParObject()
{
	printf("VectorInt1: Creating object ParObject on localhost\n");
}

ParObject::ParObject(POPString machine)
{
	printf("VectorInt1: Creating object ParObject on %s\n",GetAccessPoint().GetAccessString());
}

ParObject::ParObject(float f)
{
	printf("VectorInt1: Creating object ParObject with power %f\n",f);
}

ParObject::~ParObject()
{
	printf("VectorInt1: Destroying the object ParObject... %d, %d\n",  static_cast<int>(theData.GetInternalData().size()), theData.GetMyData());
}

void ParObject::SetData(POPintVector data)
{
  printf("Vector size = %d\n", static_cast<int>(data.GetInternalData().size())); 
	theData=data;
}

POPintVector ParObject::GetData()
{
	return theData;
}

@pack(ParObject);
