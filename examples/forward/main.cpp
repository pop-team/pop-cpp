#include "radio.ph"
#include "application.ph"

#include <stdio.h>

int main(int argc, char* argv[])
{
  printf("Start test case 0\n"); 

  Application a; 
  Radio r;
  r.set_application(a); 
  r.get_application();

  return 0; 
}
