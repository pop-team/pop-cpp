#include "pop_xmp_object_object.h"
#include <stdio.h>


POPXMPObject_popcobject::POPXMPObject_popcobject()
{
  printf("REMOTE OBJECT: Created successfully\n"); 
}

POPXMPObject_popcobject::~POPXMPObject_popcobject()
{
  printf("REMOTE OBJECT: Destructor\n"); 
}

void POPXMPObject_popcobject::execute_xmp_1()
{
  printf("REMOTE OBJECT: Execute XMP 1\n"); 
}

void POPXMPObject_popcobject::set_value(int val)
{
  printf("REMOTE OBJECT: Set Value %d\n", val); 
}