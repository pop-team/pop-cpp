#include <stdio.h>
#include "toto.ph"

int main(int argc, char** argv)
{
  try
 {
	  printf("\nthis: Starting test...\n");
	  Toto t;
	  t.work();

    if (t.getIdent()==10)	  
	    printf("this: test succeeded, destroying objects ...\n");
    else
      printf("this: test failed, destroying objects ...\n");
	}

  catch (POPException e)
	{printf("this: test failed, error no.%d, destroying objects:\n",
	  e.Code());}
  return 0;
}

