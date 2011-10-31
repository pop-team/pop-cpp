#include <stdio.h>
#include "classdata.h"

ClassData::ClassData() {}

ClassData::~ClassData() {}

void ClassData::SetInternalData(Data d) {theData = d;}

Data ClassData::GetInternalData() {return theData;}

void ClassData::SetMyData(int d) {myData = d;}

int ClassData::GetMyData() {return myData;}

void ClassData::Serialize(POPBuffer &buf, bool pack)
{
  int a;
  if (pack)
  {
    a = theData.GetInternalData();
    buf.Pack(&a,1);
    buf.Pack(&myData,1);
  }
  else
  {
    buf.UnPack(&a,1);
    theData.SetInternalData(a);
    buf.UnPack(&myData,1);
  }
}

