#ifndef _INTEGER_PH
#define _INTEGER_PH
#include <string.h>

parclass Integer
{
public:
	Integer(int wanted, int minp) @{ power= wanted ?: minp;};
	Integer(paroc_string machine) @{ od.url(machine);};
	~Integer();

	seq async void Set(int val);
	conc int Get();
	mutex void Add(Integer &other);
	mutex void Add([in] Integer &o1, [in] Integer &o2);

	async conc void Wait(int t);

	conc int Sum([in] int x[5000]);

private:
	int data;
};

#endif
