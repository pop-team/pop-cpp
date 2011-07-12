#include <stdio.h>
#include "parobject.ph"

//---------------------------------------------------------------

int main(int argc, char** argv)
{
	printf ("\nTemplateParam1: Starting test...\n");

	ParObject ob;
	X tParam;

	tParam.SetIdent(123);
	ob.SetTheData(tParam);
	tParam.SetIdent(0);

	printf("TemplateParam1: Ident is currently = %d\n", tParam.GetIdent());
	tParam = ob.GetTheData();
	printf("TemplateParam1: Ident is currently = %d\n", tParam.GetIdent());

	if (ob.GetTheData().GetIdent()==123)
		printf("TemplateParam1: test succeeded, destroying objects...\n");
	else
		printf("TemplateParam1: test failed, destroying objects...\n");

	return 0;
}
