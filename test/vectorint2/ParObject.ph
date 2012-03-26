#ifndef _PAROBJECT_PH_
#define _PAROBJECT_PH_
#include "popintvector.h"

parclass ParObject
{

	classuid(1001);

public:
	ParObject() @{od.url("localhost");};
	ParObject (POPString machine) @{od.url(machine);};
	ParObject(float f) @{od.power(f);};
	~ ParObject ();

	seq async void SetData(POPintVector data);
	seq sync POPintVector GetData();

private:
	POPintVector theData;
};
#endif
