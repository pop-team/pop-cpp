#ifndef _PAROBJECT_PH
#define _PAROBJECT_PH
#include "data.h"

parclass ParObject
{
	classuid(1000);

public:
	ParObject() @{od.url("localhost");};
	ParObject (POPString machine) @{od.url(machine);};
	ParObject(float f) @{od.power(f);};
	~ParObject ();

	seq async void SetData(Data data);
	seq sync Data GetData();

private:
	Data theData;
};
#endif
