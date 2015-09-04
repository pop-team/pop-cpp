#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_

/**
 * @author clementval
 * @date 2012.07.11
 * This program tests passing array with the standard C++ declaration instead of specific POP-C++ one.
 */

parclass POPObject {
    classuid(1500);

public:
    POPObject()@{od.url("localhost"); od.executable("./POPObject.obj");};
    ~POPObject();

    sync seq void displayArray(int length, int array[]);

private:

};


#endif /*POPOBJECT_PH_*/
