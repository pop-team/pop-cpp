#include "POPObject.ph"

/**
 * @author  clementval
 * @date    2011.11.28
 * This program is testing the bug number 15 in the known bug list of POP-C++
 */
int main(int argc, char** argv) {
    cout << "Showing problem number 0 - array as parameter" << popcendl;
    POPObject o;
    int n = 10;
    int i[n];
    for (int j = 0; j < 10; j++) {
        i[j] = j;
    }

    o.dummyMethod(n, i);
    return 0;
}
