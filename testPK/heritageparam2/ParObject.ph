#ifndef _PAROBJECT_PH_
#define _PAROBJECT_PH_
#include "heritdata.h"

/*#define parclass class
#define seq
#define conc
#define async
#define sync
#define mutex*/

parclass ParObject        
{

//classuid(1001);

public:
	 ParObject() @{od.url("localhost");};
	~ ParObject ();

	seq sync void SetData(HeritData data1, Data &data2);
	seq sync HeritData GetData();

private:
	HeritData theData;
};
#endif
