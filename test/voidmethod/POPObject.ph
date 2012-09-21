#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_

/**
 * @author clementval
 * @date 2012.07.11
 * This program tests compilation without the @pack directive. Compilation should work and print a warning message.
 */

parclass POPObject {
	classuid(1500);

public:
	POPObject() @{ od.url("localhost"); };
	~POPObject();
	sync seq void voidMethod(void);

private:
	
};


#endif /*POPOBJECT_PH_*/
