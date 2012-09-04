#include "POPObject.ph"
#include <unistd.h>

/**
 * @author clementval
 * @date 2012.08.04
 * This program tests creation of many parallel objects
 */

POPObject::POPObject()
{		
   cout << "POPObject is processing its construction on machine:" <<  (const char*)POPSystem::GetHost() << popcendl;
}

POPObject::~POPObject()
{
   cout << "POPObject on machine " << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

@pack(POPObject);
