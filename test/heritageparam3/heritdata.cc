#include <stdio.h>
#include "heritdata.h"

HeritData::HeritData()
{
  for (int i=0; i<100000; i++) toUseMemorySpace[i]=(double)i;
}

HeritData::~HeritData() {}

void HeritData::SetInternalData(int d) {Data::SetInternalData(d);}

int HeritData::GetInternalData() {return Data::GetInternalData();}

void HeritData::SetMyData(int d) {myData = d;}
void HeritData::SetMyData(int d, double v) {toUseMemorySpace[d]=v;}

int HeritData::GetMyData() {return myData;}
double HeritData::GetMyData(int i) {return toUseMemorySpace[i];}

void HeritData::Serialize(POPBuffer &buf, bool pack)
{
  Data::Serialize(buf, pack);      // (De)Serialize the "mother" data

  if (pack)
  {
    buf.Pack(&myData,1);           // Serialize my data
    buf.Pack(toUseMemorySpace,100000);
  }
  else
  {
    buf.UnPack(&myData,1);          // De-serialize my data
    buf.UnPack(toUseMemorySpace,100000);
  }
}

