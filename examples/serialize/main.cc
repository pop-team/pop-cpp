#include <stdio.h>
#include "parObject.ph"
#include "data.h"

int main(int argc, char** argv)
{

	printf("\nStarting program..\n");

	int b = 10;
	Data a;
	ParObject o("localhost");
	printf("Current internal data value = %d\n", o.GetData().GetInternalData());

	a.SetInternalData(b);
	o.SetData(a);
	b = o.GetData().GetInternalData();
	printf("Current internal data value = %d\n", b);

	if (b==10) printf("Pogram terminated, destroying objects...\n");
	else printf("Program failed, bad value transmission\n");

	return 0;
}

