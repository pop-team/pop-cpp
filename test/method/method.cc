#include "method.ph"
#include <stdio.h>
#include <unistd.h>

TestMethod::TestMethod()
{
	timer.Start();
}

void TestMethod::TestConc1()
{
	double s=timer.Elapsed();
	sleep(30);
	double e=timer.Elapsed();
	printf("TestConc1 : %g-%g\n",s,e);
}

void TestMethod::TestConc2()
{
	double s=timer.Elapsed();
	sleep(25);
	double e=timer.Elapsed();
	printf("TestConc2 : %g-%g\n",s,e);
}

void TestMethod::TestConc3()
{
	double s=timer.Elapsed();
	sleep(8);
	double e=timer.Elapsed();
	printf("TestConc3 : %g-%g\n",s,e);
}

void TestMethod::TestSeq1()
{
	double s=timer.Elapsed();
	sleep(10);
	double e=timer.Elapsed();
	printf("TestSeq1 : %g-%g\n",s,e);
}


void TestMethod::TestSeq2()
{
	double s=timer.Elapsed();
	sleep(10);
	double e=timer.Elapsed();
	printf("TestSeq2 : %g-%g\n",s,e);
}

void TestMethod::TestSeq3()
{
	double s=timer.Elapsed();
	sleep(5);
	double e=timer.Elapsed();
	printf("TestSeq3 : %g-%g\n",s,e);
}

void TestMethod::TestMutex()
{
	double s=timer.Elapsed();
	sleep(5);
	double e=timer.Elapsed();
	printf("TestMutex : %g-%g\n",s,e);
}

void TestMethod::TestFinal()
{
	double s=timer.Elapsed();
	sleep(2);
	double e=timer.Elapsed();
	printf("TestFinal : %g-%g\n",s,e);
}

void MethodCall()
{
	TestMethod t;
	sleep(1);

	t.TestConc1();
	//  sleep(1);
	t.TestSeq1();
	//  sleep(1);
	t.TestSeq2();
	//  sleep(1);
	t.TestConc2();

	//  sleep(1);
	t.TestMutex();

	t.TestConc3();
	sleep(1);
	t.TestSeq3();
	t.TestConc3();

	printf("Wait results...\n");
//  sleep(120);
}


int main (int argc, char **argv)
{
	printf("Method: Starting test..\n");
	
	MethodCall();
	printf("Invocation order: TestConc1, TestSeq1, TestSeq2, TestCon2, TestMutex, TestConc3, TestSeq3, TestConc3\nThe result should look like:\n=====================\nMETHOD   \tSTART\tEND\nTestSeq1\t1\t11\nTestSeq2\t11\t21\nTestConc2\t1\t26\nTestConc1\t1\t31\nTestMutex\t31\t36\nTestSeq3\t36\t41\nTestConc3\t36\t44 (twice)\n=====================\n");
	
	printf("Method: test succeeded, destroying objects..\n");
	
	return 0;
}


@pack(TestMethod);
