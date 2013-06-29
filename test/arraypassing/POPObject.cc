#include "POPObject.ph"
#include <unistd.h>

/**
 * @author clementval
 * @date 2012.07.11
 * This program tests passing array with the standard C++ declaration instead of specific POP-C++ one. 
 */

POPObject::POPObject()
{	
   //std::cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << std::endl;
   printf("POPCobject created (by JobMgr) on machine:%s\n", GetAccessPoint().GetAccessString());
}

POPObject::~POPObject()
{
   //std::cout << "POPCobject: on machine:" << GetAccessPoint().GetAccessString() <<" is being destroyed" << std::endl;
   printf("POPCobject: on machine:%s is being destroyed\n", GetAccessPoint().GetAccessString());
}

void POPObject::displayArray(int length, int array[]){
	//std::cout << "In parallel object" << std::endl;
	printf("In parallel object\n");
	for(int i=0; i<length;i++){
		//std::cout << "item[" << i << "]=" << array[i] << std::endl;
		printf("item[%d]=%d\n",i, array[i]);
		array[i] = array[i]+1;
	}
}

@pack(POPObject);
