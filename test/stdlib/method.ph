#include "pop_timer.h"

parclass TestMethod {
public:
    TestMethod()@{od.url("localhost");};

    int TestString1(std::string value);
    int TestString2(std::string& value);
    int TestString3(const std::string& value);

    int TestVector1(std::vector<int> value);
    int TestVector2(std::vector<int>& value);
    int TestVector3(const std::vector<int>& value);

    classuid(1001);
};
