#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_



parclass POPObject
{
	classuid(1500);

public:
	POPObject() @{ od.search(0, 0, 0); };
	~POPObject();
	
	//sync seq int dummyMethod() const;	
		
	sync seq char* dummyChar();	
private:
	int internal;

};

#endif /*POPOBJECT_PH_*/
