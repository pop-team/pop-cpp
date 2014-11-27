#include <stdio.h>
#include "ParObject.ph"

ParObject::ParObject()
{
  printf("Heritparam3: Creating object ParObject on localhost\n");
}

ParObject::~ParObject()
{
  printf("Heritparam3: Destroying the object ParObject... %d,%d\n\n", theData.GetInternalData(), theData.GetMyData());
}

void ParObject::SetData(HeritData data1, Data &data2)
{
  Data D;
  D.SetInternalData(23);
  theData=data1;
  printf("Heritparam3: data2.GetInternalData = %d\n", data2.GetInternalData());
  data2.SetInternalData(13);
  data2 = D;
}

HeritData ParObject::GetData()
{
  return theData;
}

@pack(ParObject);
