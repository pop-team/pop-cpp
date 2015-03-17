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

#include "paroc_memspool.h"
#include "paroc_exception.h"

paroc_memspool::paroc_memspool() {
}

paroc_memspool::~paroc_memspool() {
    Free();
}

void* paroc_memspool::Alloc(int sz) {
    if(sz<=0) {
        return nullptr;
    }

    void* data;
    if((data=malloc(sz))==nullptr) {
        paroc_exception::paroc_throw(errno);
    }
    memtemp.push_back(data);
    return data;
}

void paroc_memspool::Managed(void* data) {
    if(data) {
        memtemp.push_back(data);
    }
}

void paroc_memspool::Free() {
    for(auto& tmp : memtemp){
        free(tmp);
    }
    memtemp.clear();
}
