#include "method.ph"
#include <stdio.h>
#include <unistd.h>

void MethodCall();

int main(int argc, char** argv) {
    printf("cpp11: Starting test..\n");

    MethodCall();
    printf("The result should look like:\n!b\n1\n2\n3\n4\n");

    printf("cpp11: test succeeded, destroying objects..\n");

    return 0;
}

void MethodCall() {
    TestMethod t;
    sleep(1);

    t.TestSeq1();
    t.TestSeq2();
}
