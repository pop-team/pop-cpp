#include <stdio.h>
#include "ParObject.ph"

ParObject::ParObject()
{
  printf("Structparam: Creating object ParObject on localhost\n");
}

ParObject::ParObject(paroc_string machine)
{
  printf("Structparam: Creating object ParObject on %s\n",(const char *)paroc_system::GetHost());
}

ParObject::ParObject(float f)
{
  printf("Structparam: Creating object ParObject with power %f\n",f);
}

ParObject::~ParObject()
{
  printf("Structparam: Destroying the object ParObject... %d, %d\n",  theData.myData, theData.theData.theData);
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
