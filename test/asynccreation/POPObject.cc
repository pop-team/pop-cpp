#include "POPObject.ph"
#include <unistd.h>

/**
 * @author clementval
 * @date 2012.07.11
 * This program tests passing array with the standard C++ declaration instead of specific POP-C++ one. 
 */

POPObject::POPObject()
{	
   cout << "POPObject is processing its construction (5 secondes delay) on machine:" <<  (const char*)POPSystem::GetHost() << popcendl;
	sleep(5);
   cout << "POPObject created (by JobMgr) on machine:" <<  (const char*)POPSystem::GetHost() << popcendl;
}

POPObject::~POPObject()
{
   cout << "POPObject: on machine:" << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

void POPObject::firstMethod(){
	cout << "First method is called on" <<  (const char*)POPSystem::GetHost() << popcendl;
}

void POPObject::secondMethod(){
	cout << "Second method is called on" <<  (const char*)POPSystem::GetHost() <<popcendl;
}

@pack(POPObject);