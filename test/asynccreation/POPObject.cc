#include "POPObject.ph"
#include <unistd.h>

/**
 * @author clementval
 * @date 2012.08.22
 * This program tests asynchronous parallel object allocation
 */

POPObject::POPObject()
{	
   cout << "POPObject is processing its construction (5 secondes delay) on machine:" <<  (const char*)POPSystem::GetHost() << popcendl;
	sleep(5);
   cout << "POPObject created (by JobMgr) on machine:" <<  (const char*)POPSystem::GetHost() << popcendl;
}

POPObject::~POPObject()
{
   cout << "POPObject on machine " << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

void POPObject::firstMethod(){
	cout << "First method is called on " <<  (const char*)POPSystem::GetHost() << popcendl;
}

void POPObject::secondMethod(){
	cout << "Second method is called on " <<  (const char*)POPSystem::GetHost() <<popcendl;
}

@pack(POPObject);