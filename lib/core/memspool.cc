/**
 * File : memspool.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of the memory management
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 */

#include <stdio.h>
#include <stdlib.h>

#include "pop_memspool.h"
#include "pop_exception.h"

pop_memspool::pop_memspool() {
}

pop_memspool::~pop_memspool() {
    Free();
}

void* pop_memspool::Alloc(int sz) {
    if(sz<=0) {
        return nullptr;
    }

    void* data;
    if((data=malloc(sz))==nullptr) {
        pop_exception::pop_throw(errno);
    }
    memtemp.push_back(data);
    return data;
}

void pop_memspool::Managed(void* data) {
    if(data) {
        memtemp.push_back(data);
    }
}

void pop_memspool::Free() {
    for(auto& tmp : memtemp){
        free(tmp);
    }
    memtemp.clear();
}
