#include "child.ph"
#include "mother.ph"

#include <stdio.h>

int main(int argc, char** argv)
{
	printf("Start pure virtual test ...\n");
	Child c;
	c.method_pv();
	printf("Test finished ...\n");
}
