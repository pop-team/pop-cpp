#include <stdio.h>
#include "classA.ph"


int main(int argc, char **argv) {


    ClassA objectA(2);
    ClassB objectB(1);

    objectA.doSmth();
    objectB.doSmth();
    objectA.saveRef(objectB);

    return 0;

}
