#include "popobject.ph"

/**
 * @author  clementval
 * @date    2012.08.29
 * This program tests compilation without the @pack directive. Compilation should work and print a warning message.
 */
int main(int argc, char** argv) {
    try {
        printf("NoPack 2: test started...\n");
        POPObject o;
        o.createSecondObject();
        printf("NoPack 2: test succeeded, destroying objects...\n");
    } catch (POPException& ex) {
        printf("NoPack 2: test failed. %s\n", ex->what());
    }
    return 0;
}
