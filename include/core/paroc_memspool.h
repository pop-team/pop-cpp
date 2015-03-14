/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief POP-C++ memory management
 *
 *
 */

#ifndef POPC_MEMSPOOL_H
#define POPC_MEMSPOOL_H

#include <vector>
#include <stdlib.h>

#include "paroc_interface.h"

typedef void * VOIDPTR;

/**
 * @class paroc_memspool
 * @brief POP-C++ memory management, used by POP-C++ runtime.
 *
 * @author Tuan Anh Nguyen
 */
class paroc_memspool {
public:
    paroc_memspool();
    ~paroc_memspool();

    void* Alloc(int sz);
    void Managed(void* data);
    void Free();
protected:
    std::vector<void*> memtemp;
};

template <class T> class paroc_container {
public:
    paroc_container(int count);
    ~paroc_container();
    inline operator T *();
private:
    T *data;
};

template <class T> class paroc_interface_container {
public:
    paroc_interface_container(int count);
    ~paroc_interface_container();
    inline operator T *();
private:
    T *data;
    int n;
};

template<class T>
paroc_container<T>::paroc_container(int count) {
    data=(count>0)? new T[count] : NULL;
}

template<class T>
paroc_container<T>::~paroc_container() {
    if(data!=NULL) {
        delete [] data;
    }
}

template<class T>
paroc_container<T>::operator T* () {
    return data;
}

template<class T>
paroc_interface_container<T>::paroc_interface_container(int count) {
    data=(count>0)? reinterpret_cast<T *>(malloc(count*sizeof(T))) : NULL;
    n=count;
    for(T *tmp=data; count>0; count--, tmp++) {
        new(tmp) T(paroc_interface::_paroc_nobind);
    }
}

template<class T>
paroc_interface_container<T>::~paroc_interface_container() {
    if(n>0) {
        for(T *tmp=data; n>0; n--, tmp++) {
            tmp->~T();
        }
        free(data);
    }
}
typedef paroc_memspool POPMemspool;

template<class T>
paroc_interface_container<T>::operator T*() {
    return data;
}

#endif
