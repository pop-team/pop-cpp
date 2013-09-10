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

void POPObject::displayArray(int length, int array[]){
	cout << "In parallel object" << popcendl;
	for(int i=0; i<length;i++){
		cout << "item[" << i << "]=" << array[i] << popcendl;
		array[i] = array[i]+1;
	}
}

@pack(POPObject);