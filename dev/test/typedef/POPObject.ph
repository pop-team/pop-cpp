#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_

parclass POPObject
{
	classuid(1500);

public:
	POPObject() @{ od.search(0, 0, 0); };
	~POPObject();

	typedef short SmallNumber;

private:
	SmallNumber one;
	
};



#endif /*POPOBJECT_PH_*/
