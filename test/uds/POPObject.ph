#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_

parclass POPObject {
    classuid(1500);

public:
    POPObject() @{ od.url("localhost"); od.executable("./POPObject.obj");};
    ~POPObject();

    sync seq void firstMethod();
    async seq void secondMethod();
};

#endif /*POPOBJECT_PH_*/
