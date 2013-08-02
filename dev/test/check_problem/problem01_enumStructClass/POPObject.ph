#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_



typedef unsigned int BeforeType;

enum BeforeEnum { IT1, IT2 };

struct BeforeStruct {
	double weight;
	int number;
};

class BeforeClass {
public:
	BeforeClass();
private:
		
};

parclass POPObject
{
	classuid(1500);

public:
	POPObject() @{ od.search(0, 0, 0); };
	~POPObject();


	
	sync seq void dummyMethod();	

	/*class InnerClass {
	public:
		InnerClass();	
	private:
		int number;
	};	*/
		
private:
//	typedef unsigned long InnerType; //NOT SUPPORTED FOR THE MOMENT
	BeforeType i;

	struct InnerStruct {
		double weight;
		int number;
	};	
	
	
	enum InnerEnum { ITEM1, ITEM2 }; 
};

typedef bool AfterType;

struct AfterStruct {
	double weight;
	int number;
};	

class AfterClass {
public:
	AfterClass();
private:
		
};
	
	
enum AfterEnum { ITEM1, ITEM2 }; 
#endif /*POPOBJECT_PH_*/