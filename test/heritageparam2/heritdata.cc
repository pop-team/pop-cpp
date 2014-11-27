#include <stdio.h>
#include "heritdata.h"

HeritData::HeritData() {}

HeritData::~HeritData() {}

void HeritData::SetInternalData(int d) {Data::SetInternalData(d);}

int HeritData::GetInternalData() {return Data::GetInternalData();}

void HeritData::SetMyData(int d) {myData = d;}

int HeritData::GetMyData() {return myData;}

void HeritData::Serialize(POPBuffer &buf, bool pack)
{
	//int a;
	Data::Serialize(buf, pack);
	if (pack)
	{
		//a=Data::GetInternalData();
		//buf.Pack(&a,1);
		buf.Pack(&myData,1);
	}
	else
	{
		//buf.UnPack(&a,1);
		//Data::SetInternalData(a);
		buf.UnPack(&myData,1);
	}
}

