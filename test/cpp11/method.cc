#include "method.ph"
#include <stdio.h>
#include <unistd.h>

TestMethod::TestMethod() {
    timer.Start();
}

void TestMethod::test_int_1(int& ref) {
    ref = 2;
}

void TestMethod::test_int_1(int&& ref) {
    ref = 2;
}

void TestMethod::TestSeq1() {
    int test;
    test_int_1(test);
    sleep(test);
}

void TestMethod::TestSeq2() {
    int test;
    test_int_1(test);
    sleep(test);
}

void TestMethod::TestSeq3() {
    double s=timer.Elapsed();
    sleep(5);
    double e=timer.Elapsed();
    printf("TestSeq3 : %g-%g\n",s,e);
}

void TestMethod::TestConc1() {
    double s=timer.Elapsed();
    sleep(30);
    double e=timer.Elapsed();
    printf("TestConc1 : %g-%g\n",s,e);
}

void TestMethod::TestConc2() {
    double s=timer.Elapsed();
    sleep(25);
    double e=timer.Elapsed();
    printf("TestConc2 : %g-%g\n",s,e);
}

void TestMethod::TestConc3() {
    double s=timer.Elapsed();
    sleep(8);
    double e=timer.Elapsed();
    printf("TestConc3 : %g-%g\n",s,e);
}

void TestMethod::TestMutex() {
    double s=timer.Elapsed();
    sleep(5);
    double e=timer.Elapsed();
    printf("TestMutex : %g-%g\n",s,e);
}

void TestMethod::TestFinal() {
    double s=timer.Elapsed();
    sleep(2);
    double e=timer.Elapsed();
    printf("TestFinal : %g-%g\n",s,e);
}

@pack(TestMethod);
