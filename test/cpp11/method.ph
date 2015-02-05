#include "timer.h"

parclass TestMethod {
public:
    TestMethod()@{od.url("localhost");};

    async seq void TestSeq1();
    async seq void TestSeq2();

    classuid(1001);

private:
    Timer timer;

};
