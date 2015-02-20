#include "POPCobject.ph"
#include <unistd.h>
#include <stdio.h>

POPCobject::POPCobject() {
    printf("  POPCobject created on machine \"%s\"\n",POPGetHost().c_str());
}

POPCobject::~POPCobject() {
    printf("  POPCobject on machine \"%s\" is being destroyed\n", POPGetHost().c_str());
}

void POPCobject::m2(POPCobject &o) {
    printf("  m2 called on \"%s\" \n",POPGetHost().c_str());
}

void POPCobject::m4(StructData &d) {
    d.SetMyData(2*d.GetMyData());
    printf("  m4 called on \"%s\" \n",POPGetHost().c_str());
}

void POPCobject::m300(StructData d) {
    d.SetMyData(3*d.GetMyData());
    printf("  m300 called on \"%s\" \n",POPGetHost().c_str());
}

void POPCobject::m400(StructData d) {
    printf("  m400 called on \"%s\" \n",POPGetHost().c_str());
}


void POPCobject::m5(POPCobject *o) {
    printf("  m5 called on \"%s\" \n",POPGetHost().c_str());
}

void POPCobject::m6(POPCobject *o) {
    printf("  m6 called on \"%s\" \n",POPGetHost().c_str());
}

void POPCobject::m7(StructData *d) {
    printf("  m7 called on \"%s\" \n",POPGetHost().c_str());
}

void POPCobject::m8(StructData *d) {
    printf("  m8 called on \"%s\" \n",POPGetHost().c_str());
}


StructData POPCobject::m12(int v) {
    StructData d;
    Data i;
    d.SetMyData(v);
    i.SetInternalData(d.GetMyData()-v);
    d.SetInternalData(i);

    printf("  m12 called on \"%s\"\n",POPGetHost().c_str());
    return d;
}

POPCobject& POPCobject::m20() {
    printf("  m20 called\n");
    return *this;
}

@pack(POPCobject);
