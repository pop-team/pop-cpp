#include "timer.h"

parclass TestMethod
{
public:
	TestMethod();
	async conc void TestConc1();
	async conc void TestConc2();
	async conc void TestConc3();
	async seq void TestSeq1();
	async seq void TestSeq2();
	async seq void TestSeq3();

	async mutex void TestMutex();

	sync mutex void TestFinal();

	classuid(1001);

private:
	Timer timer;

};
