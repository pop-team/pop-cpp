#ifndef _PAROBJECT_PH_
#define _PAROBJECT_PH_
#include "popintvector.h"

parclass ParObject
{

	classuid(1001);

public:
	ParObject() @{ od.node(1); od.executable("./ParObject.obj"); };
	ParObject (POPString machine) @{ od.node(1); od.executable("./ParObject.obj"); };
	ParObject(float f) @{ od.node(1); od.executable("./ParObject.obj"); };
	~ ParObject ();

	seq async void SetData(POPintVector data);
	seq sync POPintVector GetData();

private:
	POPintVector theData;
};
#endif
