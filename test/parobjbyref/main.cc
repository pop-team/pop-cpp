#include "POPObject.ph"

/**
 * @author  clementval
 * @date    2012.07.11
 * This program tests compilation without the @pack directive. Compilation should work and print a warning message.
 */
int main(int argc, char** argv) {
    try {
        printf("Method with void parameter: Starting test...\n");
        POPObject o1(10001);
        o1.voidMethod(o1);

        POPObject o2(10002);
        o1.voidMethod(o2);
        o2.voidMethod(o1);

        printf("Method with void parameter: test succeeded, destroying objects ...\n");

    } catch(std::exception& e) {
        printf("Exception: %s\n", e.what());
        return 1;
    }
    return 0;
}
