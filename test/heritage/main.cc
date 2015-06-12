/**
 * @author  P.Kuonen
 * @date    2012.09.04
 * This program tests using hierarchy of class as parameters
 */
#include <stdlib.h>
#include <iostream>
#include "mother.ph"
#include "child.ph"

//TODO(BW) This breaks C++ Semantics...
//TODO(BW) This should ALWAYS call Mother functions whatever is passed to the function...
void callMethod(Mother c, int v) {
    c.Method1();
    c.SetVal(v);
    c.Method1();
    cout << "Heritage: GetVal=" << c.GetVal() << popcendl;
}

int main(int argc, char** argv) {
    cout << "\nHeritage: Starting test..." << popcendl;

    cout << "Heritage: Creation of object c of class Mother" << popcendl;
    Mother c;

    cout << "Heritage: Creation of object c1 of class Child" << popcendl;
    Child c1;

    cout << "Heritage: Call with Mother, c" << popcendl;
    callMethod(c, 1);

    cout << "Heritage: Call with Child, c1" << popcendl;
    callMethod(c1, 2);

    cout << "Heritage: Call callMethod of Mother with Child, c1" << popcendl;
    c.callMethod(c1, 3);

    cout << "Heritage: Call callMethod of Child with Mother, c" << popcendl;
    c1.callMethod(c, 4);

    cout << "Heritage: Terminated, destroying objects..." << popcendl;

    return 0;
}
