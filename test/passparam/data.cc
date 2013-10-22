#include <stdio.h>
#include "data.h"

Data::Data() {}

Data::~Data() {}

void Data::SetInternalData(int d) {theData = d;}

int Data::GetInternalData() {return theData;}

