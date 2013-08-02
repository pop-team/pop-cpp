#ifndef _PAROBJECT_PH_
#define _PAROBJECT_PH_
#include "heritdata.h"

parclass ParObject        
{

classuid(1001);

public:
	 ParObject() @{ od.node(1); od.executable("./ParObject.obj"); };
	~ParObject ();

	seq sync void SetData([in, out]HeritData data1, [in, out]Data data2);
	seq sync HeritData GetData();

private:
	HeritData theData;
};

#endif
