#ifndef _PAROBJECT_PH_
#define _PAROBJECT_PH_

#include "ClassA.h"
#include "ClassA.cc"
#include "X.h"

parclass ParObject          
{
classuid(1001);

public:
	ParObject() @{ od.node(1); od.executable("./ParObject.obj"); };
	ParObject(paroc_string machine) @{ od.node(1); od.executable("./ParObject.obj"); };
  ~ParObject();

	seq async void SetTheData(X d);
	conc sync X GetTheData();

private:
  ClassA<X> theData;
};

#endif
