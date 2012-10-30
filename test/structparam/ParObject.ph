#ifndef _PAROBJECT_PH_
#define _PAROBJECT_PH_
#include "data.h"

typedef struct aData
{
    Data theData;
    int myData;
} StructData;


parclass ParObject        
{

classuid(1001);

public:
	 ParObject() @{ od.node(1); od.executable("./ParObject.obj"); };
	 ParObject (paroc_string machine) @{ od.node(1); od.executable("./ParObject.obj"); };
   ParObject(float f) @{ od.node(1); od.executable("./ParObject.obj"); };
	 ~ParObject();

	seq async void SetData(StructData data);
	seq sync StructData GetData();
  seq sync void Get(StructData &data);

private:
	StructData theData;
};



#endif
