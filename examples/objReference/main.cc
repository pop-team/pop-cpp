#include <stdio.h>
#include "classA.ph"
#include "classB.ph"

int main(int argc, char **argv)
{

	ClassB objectB(1);
	ClassA objectA(2);

	objectA.saveReference(objectB);

	return 0;

}
