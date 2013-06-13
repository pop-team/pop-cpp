#ifndef CLASSA_H
#define CLASSA_H

parclass ClassB;

parclass ClassA
{
	classuid(1000);

public:
	ClassA(int anid);
	~ClassA();

	sync seq void doSmth();
	sync seq void saveRef(ClassB &ref);	
	
private:
	ClassB* myRef;
	int id;
};


parclass ClassB
{
	classuid(1001);
public:
	ClassB(int anid);
	~ClassB();
	
	sync seq void doSmth();

private:
	int id;
};
#endif
