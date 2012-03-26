#include "method.ph"
#include <stdio.h>
#include <unistd.h>

void MethodCall();

int main (int argc, char **argv)
{
	printf("Method: Starting test..\n");
	
	MethodCall();
	printf("Invocation order: TestConc1, TestSeq1, TestSeq2, TestCon2, TestMutex, TestConc3, TestSeq3, TestConc3\nThe result should look like:\n=====================\nMETHOD   \tSTART\tEND\nTestSeq1\t1\t11\nTestSeq2\t11\t21\nTestConc2\t1\t26\nTestConc1\t1\t31\nTestMutex\t31\t36\nTestSeq3\t36\t41\nTestConc3\t36\t44 (twice)\n=====================\n");
	
	printf("Method: test succeeded, destroying objects..\n");
	
	return 0;
}
