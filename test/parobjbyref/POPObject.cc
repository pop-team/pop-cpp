#include "POPObject.ph"
#include <unistd.h>

/**
 * @author clementval
 * @date 2012.07.11
 * This program tests passing array with the standard C++ declaration instead of specific POP-C++ one. 
 */

POPObject::POPObject()
{	
   std::cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << std::endl;
}

POPObject::~POPObject()
{
   std::cout << "POPCobject: on machine:" << GetAccessPoint().GetAccessString() <<" is being destroyed" << std::endl;
}

void POPObject::voidMethod(POPObject& o){
	std::cout << "Method with void param is called" << std::endl;
}

@pack(POPObject);