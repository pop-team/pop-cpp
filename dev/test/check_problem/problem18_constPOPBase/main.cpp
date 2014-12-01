#include "POPObject.h"
#include "POPData.h"

/**
 * @author  clementval
 * @date    2011.11.28
 * This program is testing various known bug in POP-C++
 */
int main(int argc, char** argv) {
    POPObject o;

    POPData d;
    d.setIntData(10);

    o.transferPOPBaseData(d);

    return 0;
}
