#ifndef _PAROBJECT_PH_
#define _PAROBJECT_PH_
#include "popxvector.h"

parclass ParObject
{

	classuid(1001);

public:
	ParObject() @{od.url("localhost");};
	ParObject (POPString machine) @{od.url(machine);};
	ParObject(float f) @{od.power(f);};
	~ ParObject ();

	seq async void SetData(POPxVector data);
	seq sync POPxVector GetData();

private:
	POPxVector theData;
};
#endif
