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

void POPObject::displayArray(int length, char array[]){
	array[2] = 'b';
	array[5] = 'c';
	array[10495910] = 'z';
	array[60495998] = 'w';
}

@pack(POPObject);