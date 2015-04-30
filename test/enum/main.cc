#include "POPObject.ph"

/**
 * @author  clementval
 * @date    2011.11.28
 * This program is testing enum declaration inside a parclass
 */
int main(int argc, char** argv)

{
    POPObject o;
    for (int i = 0; i < 7; i++) {
        o.executeSmthToday(i);
    }
    for (int i = 10; i < 23; i++) {
        o.executeSmthThisMonth(i);
    }
    return 0;
}
