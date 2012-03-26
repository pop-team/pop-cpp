#include <stdio.h>

#include "ParObject.ph"
//#include "data.h"
#include "heritdata.h"

int main(int argc, char** argv)
{

	printf("\nHeritparam1: Starting test..\n");

	int v;
	HeritData a;;
	ParObject o("localhost");

	a.SetInternalData(10);
	a.SetMyData(100);
	o.SetData(a);

	printf("Heritparam1: Current internal data =%d\n", o.GetData().GetInternalData());
	printf("Heritparam1: My current data =%d\n", o.GetData().GetMyData());

	a.SetInternalData(20);
	a.SetMyData(200);
	o.SetData(a);

	v = o.GetData().GetInternalData();
	printf("Heritparam1: Current internal data =%d\n", v);
	printf("Heritparam1: My current data =%d\n", o.GetData().GetMyData());

	if (v==20) printf("Heritparam1: test succeeded, destroying objects...\n");
	else printf("Heritparam1: Test failed, bad value transmission\n");

	return 0;
}

