#ifndef _INTEGER_PH
#define _INTEGER_PH

parclass Integer
{
	classuid(1000);

public:	
  Integer() @{ od.url("localhost"); };
	~Integer();

	seq async void Set(int val);
	conc int Get();
	mutex void Add(Integer &other);

private:
	int data;

};

#endif
