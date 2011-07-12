#ifndef _INTEGER_PH
#define _INTEGER_PH

parclass Integer
{
	classuid(1000);

public:
	Integer() @{od.power(50,20);};
	Integer(int wanted, int minp) @{ od.power(wanted,minp);};
	Integer(POPString machine) @{ od.url(machine);};
	~Integer();

	seq async void Set(int val);
	conc int Get();
	mutex void Add(Integer &other);

private:
	int data;

};

#endif
