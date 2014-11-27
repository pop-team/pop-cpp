#ifndef CLASSA_H
#define CLASSA_H
#include "classB.ph"

parclass ClassA
{
	classuid(1000);

public:
	ClassA(int anid);
	~ClassA();

	conc async void saveReference(ClassB &newRef);

private:
	ClassB * myRef;
	int id;
};
#endif
