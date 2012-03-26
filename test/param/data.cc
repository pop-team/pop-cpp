#include <stdio.h>
#include "data.h"

Data::Data() {printf("Param: Creating Data object\n");}

Data::~Data() {printf("Param: Destroying Data object\n");}

void Data::SetInternalData(int d) {theData = d;}

int Data::GetInternalData() {return theData;}

void Data::Serialize(POPBuffer &buf, bool pack)
{
	if (pack)
		buf.Pack(&theData, 1);
	else
		buf.UnPack(&theData, 1);
}

