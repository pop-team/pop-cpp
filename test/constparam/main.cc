/**
 * @author  P.Kuonen
 * @date    2012.09.04
 * This program tests the const modifier
 */
#include "POPCobject.ph"
#include "structdata.h"
#include <stdio.h>
#include <unistd.h>

#ifndef __WIN32__
    #define SLEEP(_x_) sleep(_x_);
#else
    #define SLEEP(_x_) Sleep((_x_) * 1000);
#endif

int main(int argc, char** argv) {
    POPCobject o1, o2;
    StructData d;

    printf("\nConst: Starting test....\n");
    printf(" Const: call to m2\n");
    SLEEP(1);
    o1.m2(o2);
    printf("Const: call to m4\n");
    SLEEP(1);
    o1.m4(d);
    printf("Const: call to m300\n");
    SLEEP(1);
    o1.m300(d);
    printf("Const: call to 400\n");
    SLEEP(1);
    o1.m400(d);
    printf("Const: call to m12\n");
    SLEEP(1);
    d=o1.m12(10);
    printf("Const: call to m20\n");
    SLEEP(1);
    o2=o1.m20();
    printf("Const: test succeeded, destroying objects...\n");
    return 0;
}

