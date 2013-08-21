#include <stdio.h>
#include "popcfactoriel.ph"

int main(int argc, char** argv)

{	  
  printf("\nFacto: START test\n\n");
  POPCfactoriel facto;

  int f = facto.compute(10);

  if (f==3628800) 
    printf("Facto: test succedded %d! = %d\n", 10, f);
  else
    printf("Facto: test failed %d! not egal to %d\n", 10, f);
  return 0;
}
