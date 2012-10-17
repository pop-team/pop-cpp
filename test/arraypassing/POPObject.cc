#include "POPObject.ph"
#include <unistd.h>
#include <iostream>

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
  std::cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() <<" is being destroyed" << std::endl;
}

void POPObject::displayArray(int length, int array[]){
	std::cout << "In parallel object" << std::endl;
	for(int i=0; i<length;i++){
		std::cout << "item[" << i << "]=" << array[i] << std::endl;
		array[i] = array[i]+1;
	}
}

@pack(POPObject);
