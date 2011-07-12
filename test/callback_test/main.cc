#include <stdio.h>
#include "toto.ph"

int main(int argc, char** argv)
{
	try
	{
		printf("\nCallBack: Starting test...\n");
		Toto t;
		t.SetIdent(1234);
		printf("CallBack: Value of SetIdent:%d\n",t.GetIdent());
		printf("CallBack: test succeeded, destroying objects ...\n");
	}

	catch (POPException e)
	{
		printf("CallBack: test failed, error no.%d, destroying objects:\n",
			   e.Code());
	}
	return 0;
}

