#include "timer.h"

parclass TestMethod {
public:
    TestMethod()@{od.url("localhost");};

    void test_int_1(int& ref);
    void test_int_2(int&& ref);

    async seq void TestSeq1();
    async seq void TestSeq2();
    async seq void TestSeq3();
    async conc void TestConc1();
    async conc void TestConc2();
    async conc void TestConc3();
    async mutex void TestMutex();
    sync mutex void TestFinal();

    classuid(1001);

private:
    Timer timer;

};
