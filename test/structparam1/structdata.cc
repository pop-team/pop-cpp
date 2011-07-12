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

