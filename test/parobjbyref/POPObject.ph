#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_

/**
 * @author clementval
 * @date 2012.07.11
 * This program tests compilation without the @pack directive. Compilation should work and print a warning message.
 */

parclass POPObject {
    classuid(1500);

public:
    POPObject(int id) @{ od.url("localhost");};
    ~POPObject();
    sync seq void voidMethod(POPObject& o);
    sync conc int GetId();


private:
    int id;

};


#endif /*POPOBJECT_PH_*/
