/** 
 *
 */

#include <unistd.h>
#include <stdio.h>
#include "pop_xmp_object.h"


int main(int argc, char* argv[])
{
  printf("POP-C++ Test Case: XMP Support\n"); 


  // Declare and initialize two XMP process of type POPXMPObject
  POPXMPObject xmp; 
  printf("Group object name is %s\n", xmp.get_class_name()); 
  xmp.initialize(1);   

  xmp.execute_xmp_1();
  xmp.execute_xmp_1();

  xmp.finalize();

  printf("POP-C++ Test Case: XMP Support finished\n"); 

  return 0; 
}
