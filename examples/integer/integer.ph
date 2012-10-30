#ifndef _INTEGER_PH
#define _INTEGER_PH

parclass Integer
{
	classuid(1000);

public:	
	Integer() @{ od.node(1); od.executable("./integer.obj"); };
	~Integer();

	seq async void Set(int val);
	conc int Get();
	mutex void Add([in]Integer &other);

private:
	int data;

};

#endif
