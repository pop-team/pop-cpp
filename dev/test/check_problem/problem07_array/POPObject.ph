#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_


parclass POPObject
{
	classuid(1500);

public:
	POPObject() @{ od.search(0, 0, 0); };
	~POPObject();
	
	sync seq void dummyMethod(int n, [in, out, size=n] int* i);	
		
private:

};

#endif /*POPOBJECT_PH_*/
