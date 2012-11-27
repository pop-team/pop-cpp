#include "POPObject.ph"
#include <unistd.h>

/**
 * @author clementval
 * @date 2012.08.22
 * This program tests asynchronous parallel object allocation
 */

POPObject::POPObject()
{	
  std::cout << "POPObject is processing its construction (5 secondes delay) on machine:" << GetAccessPoint().GetAccessString() << std::endl;
  sleep(5);
  std::cout << "POPObject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << std::endl;
}
/*
void POPObject::AllocateObject(){
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, 1);
		int ret;
		ret = pthread_create(&_popc_async_construction_thread, &attr, POPObject_AllocatingThread, this);
		if(ret != 0){
			pthread_attr_destroy(&attr);
			return;
		}
		pthread_attr_destroy(&attr);
}
*/
POPObject::~POPObject()
{
   std::cout << "POPObject on machine " << (const char*)POPSystem::GetHost() <<" is being destroyed" << std::endl;
}

void POPObject::firstMethod(){
	std::cout << "First method is called on " <<  (const char*)POPSystem::GetHost() << std::endl;
}

void POPObject::secondMethod(){
	std::cout << "Second method is called on " <<  (const char*)POPSystem::GetHost() <<std::endl;
}

@pack(POPObject);
