#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_

namespace poptest {

parclass POPObject {
    classuid(1500);

public:
    POPObject() @{ od.search(0, 0, 0); };
    ~POPObject();
    sync seq void testMethod();
};

}

#endif /*POPOBJECT_PH_*/
