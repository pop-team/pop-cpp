#include "method.ph"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    TestMethod t;

    std::string a("pop");
    t.TestSeq1(a);

    std::string b("is");
    t.TestSeq2(b);
    printf("%s\n", b.c_str());

    std::string c = t.TestSeq3();
    printf("%s\n", c.c_str());

    printf("The output should look like:\npop\nis\ncool\n!\n");

    return 0;
}
