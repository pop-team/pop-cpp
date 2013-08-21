#include <stdio.h>
#include "ParObject.ph"

ParObject::ParObject()
{
  printf("Object ParObject on localhost\n");
  theData.SetInternalData(0);
}

ParObject::ParObject(paroc_string machine)
{
  printf("Param: Creating object ParObject on %s\n",(const char *)paroc_system::GetHost());
  theData.SetInternalData(1);
}

ParObject::ParObject(float f)
{
  printf("Param: Creating object ParObject with power %f\n",f);
  theData.SetInternalData(2);
}

ParObject::~ParObject()
{
  printf("Param: Destroying the object ParObject... %d\n", theData.GetInternalData());
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
