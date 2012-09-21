#include "child.h"
#include "mother.h"

#include <stdio.h>

int main(int argc, char** argv)
{
	printf("Start pure virtual test ...\n");
	Mother c;
	c.method_pv();
	printf("Test finished ...\n");
}
