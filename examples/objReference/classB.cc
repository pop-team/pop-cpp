#include <stdio.h>
#include "classB.ph"

ClassB::ClassB(int anid)
{
	id=anid;
	printf("Create object of ClassB with id=%d\n",id);
}

ClassB::~ClassB()
{
	printf("Destroy object of ClassB\n");
}

void ClassB::handle()
{
	printf("Handling callback method... id=%d\n",id);
}

@pack(ClassB);
