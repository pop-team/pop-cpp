#include <stdio.h>
#include "ParObject.ph"

ParObject::ParObject()
{
  printf("Classparam: Creating object ParObject on localhost\n");
}

ParObject::ParObject(paroc_string machine)
{
  printf("Classparam: Creating object ParObject on %s\n",(const char *)paroc_system::GetHost());
}

ParObject::ParObject(float f)
{
  printf("Classparam: Creating object ParObject with power %f\n",f);
}

ParObject::~ParObject()
{
  printf("Classparam: Destroying the object ParObject... %d,%d\n", theData.GetMyData(), theData.GetInternalData().GetInternalData());
}

void ParObject::SetData(ClassData data)
{
  theData=data;
}

ClassData ParObject::GetData()
{
  return theData;
}

void ParObject::Get(ClassData &data)
{
  data=theData;
}

@pack(ParObject);
