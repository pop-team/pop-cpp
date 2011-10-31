#ifndef _PAROBJECT_PH_
#define _PAROBJECT_PH_
#include "classdata.h"

parclass ParObject        
{

classuid(1001);

public:
	 ParObject() @{od.url("localhost");};
	 ParObject (paroc_string machine) @{od.url(machine);};
   ParObject(float f) @{od.power(f);};
	~ ParObject ();

	seq async void SetData(ClassData data);
	seq sync ClassData GetData();
  seq sync void Get(ClassData &data);

private:
	ClassData theData;
};
#endif
