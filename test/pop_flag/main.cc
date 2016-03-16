/**
 * @author  B.Wicth
 * @date    2016.16.03
 * This program tests that the compiler sets correctly _POP_
 */
#include <stdio.h>

int main(int argc, char** argv) {
#ifdef _POP_
    printf("pop_flag: test succeeded\n");
    return 0;
#else
    printf("pop_flag: Test failed, invalid define by the compiler\n");
    return 1;
#endif
}
