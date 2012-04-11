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


void ClassA::doSmth(){
	cout << "Call doSmth A" << popcendl;	
}

void ClassA::saveRef(ClassB &ref)	
{
	myRef = new ClassB(ref);	
	myRef->doSmth();
}

ClassB::ClassB(int anid)
{
	id=anid;
	printf("Create object of ClassB with id=%d\n",id);
}

ClassB::~ClassB()
{
	printf("Destroy object of ClassB\n");
}


void ClassB::doSmth(){
	cout << "Call doSmth B" << popcendl;	
}


@pack(ClassA, ClassB);
