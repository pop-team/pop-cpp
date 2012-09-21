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

ClassA& ClassA::saveReference()
{
	printf("Save reference of object of ClassA with id=%d\n",id);
	myRef = new ClassB(id+1); 
	return this;
}

@pack(ClassA);
