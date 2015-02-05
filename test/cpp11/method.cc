#include "method.ph"
#include <vector>

TestMethod::TestMethod() {
    timer.Start();
}

void TestMethod::TestSeq1() {
    auto b = false;
    if(b){
        cout << "b" << std::endl;
    }
}

void TestMethod::TestSeq2() {
    std::vector<int> x{1,2,3,4};
    for(auto& v : x){
        cout << v << std::endl;
    }
}

@pack(TestMethod);
