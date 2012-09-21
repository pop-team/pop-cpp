#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_

/**
 * @author clementval
 * @date 2012.09.04
 * This program tests 
 */

parclass POPObject {
	classuid(1500);

public:
	POPObject() @{ od.url("localhost"); };
	~POPObject();

	sync seq void displayArray(int length, char array[]);
	
};


#endif /*POPOBJECT_PH_*/
