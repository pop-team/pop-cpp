#ifndef _PAROBJECT_PH_
#define _PAROBJECT_PH_
#include "heritdata.h"

parclass ParObject
{

	classuid(1001);

public:
	ParObject() @{ od.node(1); od.executable("./ParObject.obj"); };
	ParObject (POPString machine) @{ od.node(1); od.executable("./ParObject.obj"); };
	ParObject(float f) @{ od.node(1); od.executable("./ParObject.obj"); };
	~ ParObject ();

	seq async void SetData(HeritData data);
	seq sync HeritData GetData();

private:
	HeritData theData;
};
#endif
