#include <stdio.h>
#include "data.h"

Data::Data()
{
	printf("Creating object of class Data\n");
	te = Enum1;
}

Data::~Data()
{
	printf("Destroying object of class Data\n");
}

void Data::SetInternalData(int d)
{
	theData = d;
}

int Data::GetInternalData()
{
	return theData;
}

void Data::Serialize(POPBuffer &buf, bool pack)
{
	if (pack){
		buf.Pack(&theData, 1);
		// Serialize the enum
		int i = (int)te;
		buf.Pack(&i, 1);
	} else {
		buf.UnPack(&theData, 1);
		// Unserialize the enum
		int i; 
		buf.UnPack(&i, 1);
		te = (TestEnum)i;
	}
}

