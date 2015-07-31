#include "method.ph"
#include <vector>

TestMethod::TestMethod() {
    //Nothing to do here
}

int TestMethod::TestString1(std::string value) {
    cout << value << popcendl;
    return value.size();
}

int TestMethod::TestString2(std::string& value) {
    cout << value << popcendl;
    return value.size();
}

int TestMethod::TestString3(const std::string& value) {
    cout << value << popcendl;
    return value.size();
}

int TestMethod::TestVector1(std::vector<int> value) {
    cout << value[2] << popcendl;
    return value[2] + value.size();
}

int TestMethod::TestVector2(std::vector<int>& value) {
    cout << value[2] << popcendl;
    return value[2] + value.size();
}

int TestMethod::TestVector3(const std::vector<int>& value) {
    cout << value[2] << popcendl;
    return value[2] + value.size();
}
