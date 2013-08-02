#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_

/**
 * @author clementval
 * @date 2012.08.04
 * This program tests creation of many objects
 */

parclass POPObject {
	classuid(1500);

public:
	POPObject() @{ od.url("localhost"); };
	~POPObject();
	
};


#endif /*POPOBJECT_PH_*/
