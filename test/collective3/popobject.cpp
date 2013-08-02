#include "popobject.ph"
#include "popgroup.ph"
#include <iostream>

POPObject::POPObject()
{
  std::cout << "POPObject created" << std::endl;   
}

POPObject::~POPObject()
{
  std::cout << "POPObject end" << std::endl;   
}

void POPObject::create_group()
{
  std::cout << "creating group" << std::endl;
  POPGroup group; 
  group.initialize(2); 

  group.finalize();    
}

@pack(POPObject); 
