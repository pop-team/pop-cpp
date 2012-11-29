#include "pop_xmp_object.h"
#include "paroc_string.h"

#include <stdio.h>

POPXMPObject::POPXMPObject()
{
  od.executable("./pop_xmp_object.obj"); 

  printf("POPXMP object created\n"); 

  POPString codefile; 
  od.getExecutable(codefile); 
  printf("OD exec %s\n", codefile.GetString()); 
}

POPXMPObject::~POPXMPObject()
{
  printf("POPXMP object terminated\n"); 
}
