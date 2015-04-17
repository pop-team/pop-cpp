#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_

/**
 * @author clementval
 * @date 2012.07.11
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
