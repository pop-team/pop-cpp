#include "POPObject.ph"
#include "POPData.h"

/**
 * @author  clementval
 * @date    2011.11.28
 * This program is testing various known bug in POP-C++
 */
int main(int argc, char** argv) {
    cout << "Showing problem number 17 - Passing array of POPBase inherited objects" << popcendl;
    POPObject o;

    POPData d;
    d.setIntData(10);

    o.transferPOPBaseData(d);

    return 0;
}
