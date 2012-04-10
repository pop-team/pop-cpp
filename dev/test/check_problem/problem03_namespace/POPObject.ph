#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_


namespace POPTest{

parclass POPObject
{
	classuid(1500);

public:
	POPObject() @{ od.search(0, 0, 0); };
	~POPObject();
	
	sync seq void dummyMethod();	
		
private:

};

}

#endif /*POPOBJECT_PH_*/
