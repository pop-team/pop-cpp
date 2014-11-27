/** 
 * @author  P.Kuonen
 * @date    2012.09.04
 * This program tests the call back functionning
 */
#include <stdio.h>
#include "toto.ph"

int main(int argc, char** argv)
{
  try
  {
    printf("\nCallBack: Starting test...\n");
    Toto t;
    t.SetIdent(1234);

    if (t.GetIdent()==-1)
    {	  
      printf("CallBack: test succeeded, destroying objects ...\n");
      return 0;
    }
    else
    {
      printf("CallBack: test failed, destroying objects ...\n");
      return 1;
    }
  }
  catch (POPException e)
  {
     printf("CallBack: test failed, error no.%d, destroying objects:\n",
	  e.Code());
     return 1;
  }
  return 0;
}

