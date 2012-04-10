#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_




enum OutsideEnum { IT1, IT2 };

parclass POPObject
{
	classuid(1500);

public:
	POPObject() @{ od.search(0, 0, 0); };
	~POPObject();


	
	sync seq void dummyMethod();	
		
private:
	struct Test2 {
		int i;
		float t;
	} apple;
	
	enum Test { ITEM1, ITEM2 }; 
};



#endif /*POPOBJECT_PH_*/
