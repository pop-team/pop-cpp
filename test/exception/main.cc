/** 
 * @author  P.Kuonen
 * @date    2012.09.04
 * This program tests exception propagation in POP-C++
 */
#include <stdio.h>
#include "exception.ph"


int main(int argc, char **argv)
{ 
  printf("\nException: Starting test..\n");
  ClassExcep e1;
  printf("Exception: Object created..\n");

  for (int j=0; j<2; j++)
    for (int i=0; i<3; i++)
    {
      try
	  {
        printf("\n");
		switch(i)
		{
		  case 0 : e1.SeqSync(j) ; break; 
		  case 1 : e1.ConcSync(j) ; break;
		  case 2 : e1.MutexSync(j) ; break;
		  default: printf("Exception: No call !\n"); break;
		} //switch
	  } //try

     catch (POPException *e)
       {printf("Exception: main has catched the POP exception (%d)!!\n", i);}    
     catch(std::exception& e)
       {printf("Exception: main has catched the std::exception '%s' (%d)!!\n", e.what(), i);}
     catch(int e)
       {printf("Exception: main has catched the int exception %d (%d)!!\n", e, i);}
     catch(...)
       {printf("Exception: main has catched the unknown exception (%d)!!\n", i);}
    } //for

  printf("Exception: test succeeded, destroying objects...\n");
  return 0;
}

