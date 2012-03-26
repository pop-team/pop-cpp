#ifndef _INTEGER_PH
#define _INTEGER_PH

parclass Integer
{
	classuid(1000);

public:	
	Integer(int maxhop, int timeout) @{ od.power(80,60); od.memory(500,500); od.bandwidth(50,78); od.search(maxhop, 0, timeout);};
	Integer() @{ od.power(80,60); od.memory(10,20); od.bandwidth(50,78); od.search(10, 200,0); };
	Integer(POPString machine) @{ od.url(machine); };
	~Integer();

	seq async void Set(int val);
	conc int Get();
	mutex void Add(Integer &other);

private:
	int data;

};

#endif
