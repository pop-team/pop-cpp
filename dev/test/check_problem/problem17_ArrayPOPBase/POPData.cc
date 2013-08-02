#include "POPData.h"

POPData::POPData()
{

}

POPData::~POPData()
{

}


void POPData::setIntData(int value)
{
	intdata = value;
}
void POPData::setFloatData(float value)
{
	floatdata = value;
}
	
int POPData::getIntData()
{
	return intdata;
}

float POPData::getFloatData()
{
	return floatdata;
}

void POPData::Serialize(POPBuffer &buf, bool pack)
{
	if (pack){
		buf.Pack(&intdata, 1);
		buf.Pack(&floatdata, 1);		
	} else {
		buf.UnPack(&intdata, 1);
		buf.UnPack(&floatdata, 1);		
	}
}
