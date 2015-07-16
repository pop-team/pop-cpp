#include "pop_timer.h"

parclass TestMethod {
public:
    TestMethod()@{od.url("localhost");};

    seq void TestSeq1();
    seq void TestSeq2();

    classuid(1001);

private:
    Timer timer;

};
