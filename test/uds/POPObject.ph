#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_

parclass POPObject {
    classuid(1500);

public:
    POPObject(int id) @{ od.protocol("uds"); od.executable("./POPObject.obj");};
    ~POPObject();

    sync seq void firstMethod();
    async seq void secondMethod();

private:
    int id;
};

#endif /*POPOBJECT_PH_*/
