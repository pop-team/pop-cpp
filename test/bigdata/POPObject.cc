#include "POPObject.ph"
#include <unistd.h>

/**
 * @author clementval
 * @date 2012.07.11
 * This program tests passing array with the standard C++ declaration instead of specific POP-C++ one. 
 */

POPObject::POPObject()
{	
   cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject()
{
   cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

void POPObject::displayArray(int length, char array[]){
	array[2] = 'b';
	array[5] = 'c';
	array[10495910] = 'z';
	array[60495998] = 'w';
}

@pack(POPObject);