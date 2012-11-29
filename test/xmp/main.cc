/** 
 *
 */

#include <stdio.h>
#include "popc_xmp.h"
#include "pop_xmp_object.h"


int main(int argc, char* argv[])
{
  printf("POP-C++ Test Case: XMP Support\n"); 


  // Declare and initialize two XMP process of type POPXMPObject
  POPXMP<POPXMPObject> xmp_bloc(2); 

  




  printf("POP-C++ Test Case: XMP Support finished\n"); 

  return 0; 
}
