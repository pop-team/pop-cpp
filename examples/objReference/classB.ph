#ifndef CLASSB_H
#define CLASSB_H

parclass ClassB
{
	classuid(1001);

public:
	ClassB(int anid);
	~ClassB();

	conc async void handle();

private:
	int id;
};
#endif
