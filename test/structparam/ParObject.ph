#ifndef _PAROBJECT_PH_
#define _PAROBJECT_PH_
#include "data.h"

struct StructData {
    Data theData;
    int myData;
};

parclass ParObject {

    classuid(1001);

public:
    ParObject() @{od.url("localhost");};
    ParObject(POPString machine) @{od.url(machine);};
    ParObject(float f) @{od.power(f);};
    ~ ParObject();

    seq async void SetData(StructData data);
    seq sync StructData GetData();
    seq sync void Get(StructData &data);

private:
    StructData theData;
};



#endif
