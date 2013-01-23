#include "pop_xmp_object.ph"
#include <stdio.h>



POPXMPObject::POPXMPObject()
{
  printf("REMOTE OBJECT: Created successfully (rank=%d)\n", get_rank()); 
}

POPXMPObject::~POPXMPObject()
{
  printf("REMOTE OBJECT: Destructor\n"); 
}

void POPXMPObject::execute_xmp_1()
{
  printf("REMOTE OBJECT: Execute XMP 1\n"); 
}

void POPXMPObject::set_value(int val)
{
  printf("REMOTE OBJECT(%d): Set Value %d\n", get_rank(), val); 
}

void POPXMPObject::propagate_value(int val)
{
  printf("REMOTE OBJECT(%d): Propagate Value %d\n", get_rank(), val); 
}
