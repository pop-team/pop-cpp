#include <stdio.h>
#include "integer.ph"
#include <unistd.h>

Integer::Integer() {
    printf("Creation of object Integer with accesspoint %s\n", GetAccessPoint().GetAccessString().c_str());
}

Integer::~Integer() {
    printf("Destroying Integer object %s\n", GetAccessPoint().GetAccessString().c_str());
}

void Integer::Set(int val) {
    data=val;
}

int Integer::Get() {
    return data;
}

void Integer::Add(Integer &other) {
    data += other.Get();
}

@pack(Integer);
