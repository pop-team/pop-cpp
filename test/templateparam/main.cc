#include <stdio.h>
#include "parobject.ph"

//---------------------------------------------------------------

int main(int argc, char** argv)
{
  printf ("\nTemplateParam: Starting test...\n");
 
  ParObject ob;
  X tParam;

  tParam.SetIdent(123);
  ob.SetTheData(tParam);
  tParam.SetIdent(0);

  printf("TemplateParam: Ident is currently = %d\n", tParam.GetIdent());
	tParam = ob.GetTheData();
  printf("TemplateParam: Ident is currently = %d\n", tParam.GetIdent());

  if (ob.GetTheData().GetIdent()==123)
  {
    printf("TemplateParam: test succeeded, destroying objects...\n");
    return 0;
  }
  else
  {
    printf("TemplateParam: test failed, destroying objects...\n");
    return 1;
  }
}
