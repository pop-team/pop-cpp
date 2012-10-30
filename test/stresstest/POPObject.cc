#include "POPObject.ph"
#include <unistd.h>

/**
 * @author clementval
 * @date 2012.08.22
 * This program tests asynchronous parallel object allocation
 */

POPObject::POPObject()
{	
   std::cout << "POPObject is processing its construction (5 secondes delay) on machine:" <<  GetAccessPoint().GetAccessString() << std::endl;
	counter = 0;
   std::cout << "POPObject created (by JobMgr) on machine:" <<  GetAccessPoint().GetAccessString() << std::endl;
}

POPObject::~POPObject()
{
   std::cout << "POPObject on machine " << GetAccessPoint().GetAccessString() <<" is being destroyed" << std::endl;
}

int POPObject::getCounter(){
	return counter;
}

void POPObject::increment(){
	counter++;
}

@pack(POPObject);
