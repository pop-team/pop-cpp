#include <stdio.h>
#include <stdlib.h>
#include "classA.ph"


ClassA::ClassA(int anid)
{
	id=anid;
	printf("Create object of ClassA with id=%d\n",id);
}

ClassA::~ClassA()
{
	delete myRef;
	printf("Destroy object of ClassA\n");
}

void ClassA::saveReference(ClassB &newRef)
{
	printf("Save reference of object of ClassA with id=%d\n",id);

	myRef = new ClassB(newRef);

	sleep(2);
	myRef->handle();
}

@pack(ClassA);
