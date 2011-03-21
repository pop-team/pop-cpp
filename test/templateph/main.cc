#include <stdio.h>
#include "toto.ph"

//---------------------------------------------------------------

int main(int argc, char** argv)
{
	printf ("\nTemplate: Starting test...\n");

	Toto ob;

	ob.SetIdent(123);

	printf("Template: Ident = %d\n", ob.GetIdent());
	printf("Template: test succeeded, destroying objects...\n");
	return 0;
}
