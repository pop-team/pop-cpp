#include "pop_xmp_object.ph"
#include "paroc_string.h"

#include <stdio.h>

POPXMPObject::POPXMPObject()
{
}

POPXMPObject::~POPXMPObject()
{
  printf("POPXMP object terminated\n"); 
}






// Collective method
void POPXMPObject::execute_xmp_1()
{
  printf("Will call the execute_xmp_1() method\n"); 
}


// Non-collective method call
void POPXMPObject::set_value(int val)
{

}

@pack(POPXMPObject); 
