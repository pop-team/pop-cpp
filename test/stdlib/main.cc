#include "method.ph"
#include <stdio.h>
#include <unistd.h>

void MethodCall();

int main(int argc, char** argv) {
    printf("cpp11: Starting test..\n");

    TestMethod obj;

    std::string test_string("Hello World!");
    std::vector<int> test_vector(9);

    test_vector[2] = 42;

    int a = obj.TestString1(test_string);

    if (a != test_string.size()) {
        cout << "Test failed, invalid return value: " << a << " should be " << test_string.size() << popcendl;
        return 1;
    }

    int b = obj.TestString2(test_string);

    if (b != test_string.size()) {
        cout << "Test failed, invalid return value: " << b << " should be " << test_string.size() << popcendl;
        return 1;
    }

    int c = obj.TestString3(test_string);

    if (c != test_string.size()) {
        cout << "Test failed, invalid return value: " << c << " should be " << test_string.size() << popcendl;
        return 1;
    }

    int d = obj.TestVector1(test_vector);

    if (d != 42 + test_vector.size()) {
        cout << "Test failed, invalid return value: " << d << " should be " << 42 + test_vector.size() << popcendl;
        return 1;
    }

    int e = obj.TestVector2(test_vector);

    if (e != 42 + test_vector.size()) {
        cout << "Test failed, invalid return value: " << e << " should be " << 42 + test_vector.size() << popcendl;
        return 1;
    }

    int f = obj.TestVector3(test_vector);

    if (f != 42 + test_vector.size()) {
        cout << "Test failed, invalid return value: " << f << " should be " << 42 + test_vector.size() << popcendl;
        return 1;
    }

    printf("stdlib: test succeeded, destroying objects..\n");

    return 0;
}
