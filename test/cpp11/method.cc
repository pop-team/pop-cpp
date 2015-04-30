#include "method.ph"
#include <vector>

TestMethod::TestMethod() {
    timer.Start();
}

void TestMethod::TestSeq1() {
    auto b = false;
    if (b) {
        cout << "b" << popcendl;
    } else {
        cout << "!b" << popcendl;
    }
}

void TestMethod::TestSeq2() {
    std::vector<int> x{1, 2, 3, 4};
    for (auto& v : x) {
        cout << v << popcendl;
    }
}

@pack(TestMethod);
