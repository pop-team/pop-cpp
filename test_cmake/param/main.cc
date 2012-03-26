#include <stdio.h>

#include "ParObject.ph"
#include "data.h"

int main(int argc, char** argv)
{

	printf("\nParam: Starting test..\n");

	int b = 10;
	Data a;
	ParObject o("localhost");
	printf("Param: Current internal data =%d\n", o.GetData().GetInternalData());

	a.SetInternalData(b);
	o.SetData(a);
	b = o.GetData().GetInternalData();
	printf("Param: Current internal data =%d\n", b);

	if (b==10) printf("Param: test succeeded, destroying objects...\n");
	else printf("Param: Test failed, bad value transmission\n");

	return 0;
}

