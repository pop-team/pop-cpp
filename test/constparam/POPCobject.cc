#include "POPCobject.ph"
#include <unistd.h>
#include <stdio.h>

void fonction1(const StructData d) {
    ;
}

void fonction2(const POPCobject& o) {
    ;
}


POPCobject::POPCobject() {
    printf("  Const: POPCobject created on machine \"%s\"\n",POPGetHost().c_str());
}

POPCobject::~POPCobject() {
    printf("  Const: POPCobject on machine \"%s\" is being destroyed\n", POPGetHost().c_str());
}

void POPCobject::m2(POPCobject const &o) {
    fonction2(o);
    printf("  Const: m2 called on \"%s\" \n",POPGetHost().c_str());
}

void POPCobject::m4(StructData const &d) {
    fonction1(d);
    printf("  Const: m4 called on \"%s\" \n",POPGetHost().c_str());
}

void POPCobject::m300(StructData const d) {
    fonction1(d);
    printf("  Const: m300 called on \"%s\" \n",POPGetHost().c_str());
}

void POPCobject::m400(StructData const d) {
    fonction1(d);
    printf("  Const: m400 called on \"%s\" \n",POPGetHost().c_str());
}


const StructData POPCobject::m12(int v) {
    StructData d;
    Data i;
    d.SetMyData(d.GetMyData()+v);
    i.SetInternalData(d.GetInternalData().GetInternalData()-v);
    d.SetInternalData(i);

    printf("  Const: m12 called on \"%s\"\n",POPGetHost().c_str());
    return d;
}

POPCobject const & POPCobject::m20() {
    POPCobject * o = new POPCobject(GetAccessPoint());
    printf("  Const: m20 called on \"%s\"\n",POPGetHost().c_str());
    return *o;
}


@pack(POPCobject);
