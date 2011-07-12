#include <stdio.h>

#include "ParObject.ph"
#include "data.h"
#include "structdata.h"

int main(int argc, char** argv)
{

	printf("\nStructparam2: Starting test..\n");

	int v;
	StructData b;
	Data a;
	ParObject o("localhost");

	a.SetInternalData(10);
	b.SetInternalData(a);
	b.SetMyData(100);
	o.SetData(b);

	printf("Structparam2: Current object internal data = %d, %d\n",
		   o.GetData().GetMyData(),
		   o.GetData().GetInternalData().GetInternalData());

	a.SetInternalData(20);
	b.SetInternalData(a);
	b.SetMyData(200);
	o.SetData(b);

	v = o.GetData().GetInternalData().GetInternalData();
	printf("Structparam2: Current object internal data = %d, %d\n",
		   o.GetData().GetMyData(),
		   o.GetData().GetInternalData().GetInternalData());

	a.SetInternalData(0);
	b.SetInternalData(a);
	b.SetMyData(0);
	printf("Structparam2: Current b internal data = %d, %d\n",
		   b.GetMyData(), b.GetInternalData().GetInternalData());

	o.Get(b);

	if ((v==20) &&
			(b.GetMyData()==200) &&
			(b.GetInternalData().GetInternalData()==20))
		printf("Structparam2: test succeeded, destroying objects...\n");
	else
		printf("Structparam2: Test failed, bad value transmission\n");

	return 0;
}

