#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_


parclass POPObject
{
	classuid(1500);

public:
	POPObject() @{ od.search(0, 0, 0); };
	~POPObject();
	
	sync seq const int* dummyMethod();	
		
private:

	int dummyInt;

};

#endif /*POPOBJECT_PH_*/
