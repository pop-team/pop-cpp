#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "timer.h"

extern float benchmark_power();

int main(int, char **)
{
	Timer test;
	test.Start();
	printf("Benchmark_power=%g\n",paroc_utils::benchmark_power());
	printf("Benchmarking time: %g\n",test.Elapsed());
	return 0;
}
