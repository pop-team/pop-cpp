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
	counter = 0;
   cout << "POPObject created (by JobMgr) on machine:" <<  (const char*)POPSystem::GetHost() << popcendl;
}

POPObject::~POPObject()
{
   cout << "POPObject on machine " << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

int POPObject::getCounter(){
	return counter;
}

void POPObject::increment(){
	counter++;
}

@pack(POPObject);
