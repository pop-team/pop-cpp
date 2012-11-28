#include "POPObject.ph"
#include <unistd.h>

/**
 * @author clementval
 * @date 2012.08.22
 * This program tests asynchronous parallel object allocation
 */

POPObject::POPObject(int node)
{	
  std::cout << "POPObject is processing its construction (5 secondes delay) on machine:" << GetAccessPoint().GetAccessString() << " node value=" << node << std::endl;
  sleep(5);
  std::cout << "POPObject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << std::endl;
}

POPObject::~POPObject()
{
   std::cout << "POPObject on machine " << GetAccessPoint().GetAccessString() <<" is being destroyed" << std::endl;
}

void POPObject::firstMethod(){
	std::cout << "First method is called on " <<  GetAccessPoint().GetAccessString() << std::endl;
}

void POPObject::secondMethod(){
	std::cout << "Second method is called on " <<  GetAccessPoint().GetAccessString()  <<std::endl;
}

@pack(POPObject);
