#include <stdio.h>
#include "structdata.h"

StructData::StructData() {}

StructData::~StructData() {}

void StructData::SetInternalData(Data d) {theData = d;}

Data StructData::GetInternalData() {return theData;}

void StructData::SetMyData(int d) {myData = d;}

int StructData::GetMyData() {return myData;}

void StructData::Serialize(POPBuffer &buf, bool pack)
{
  int temp;
  if (pack)
  {
    buf.Pack(&myData,1);
    temp=theData.GetInternalData();
    buf.Pack(&temp,1);
  }
  else
  {
    buf.UnPack(&myData,1);
    buf.UnPack(&temp,1);
    theData.SetInternalData(temp);
  }
}

