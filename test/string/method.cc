#include "method.ph"
#include <vector>

TestMethod::TestMethod() {}

void TestMethod::TestSeq1(std::string test) {
    cout << test << popcendl;
}

void TestMethod::TestSeq2(std::string& test) {
    cout << test << popcendl;
    test = "cool";
}

std::string TestMethod::TestSeq3() {
    return "!";
}
