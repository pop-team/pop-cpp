/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief POP-C++ memory management
 *
 *
 */

#ifndef POP_MEMSPOOL_H
#define POP_MEMSPOOL_H

#include <vector>
#include <stdlib.h>

#include "pop_interface.h"

typedef void* VOIDPTR;

/**
 * @class pop_memspool
 * @brief POP-C++ memory management, used by POP-C++ runtime.
 *
 * @author Tuan Anh Nguyen
 */
class pop_memspool {
public:
    pop_memspool();
    ~pop_memspool();

    void* Alloc(int sz);
    void Managed(void* data);
    void Free();

protected:
    std::vector<void*> memtemp;
};

template <class T>
class pop_container {
public:
    pop_container(int count);
    ~pop_container();
    inline operator T*();

private:
    T* data;
};

template <class T>
class pop_interface_container {
public:
    pop_interface_container(int count);
    ~pop_interface_container();
    inline operator T*();

private:
    T* data;
    int n;
};

template <class T>
pop_container<T>::pop_container(int count) {
    data = (count > 0) ? new T[count] : NULL;
}

template <class T>
pop_container<T>::~pop_container() {
    if (data != NULL) {
        delete[] data;
    }
}

template <class T>
pop_container<T>::operator T*() {
    return data;
}

template <class T>
pop_interface_container<T>::pop_interface_container(int count) {
    data = (count > 0) ? reinterpret_cast<T*>(malloc(count * sizeof(T))) : NULL;
    n = count;
    for (T* tmp = data; count > 0; count--, tmp++) {
        new (tmp) T(pop_interface::_pop_nobind);
    }
}

template <class T>
pop_interface_container<T>::~pop_interface_container() {
    if (n > 0) {
        for (T* tmp = data; n > 0; n--, tmp++) {
            tmp->~T();
        }
        free(data);
    }
}
typedef pop_memspool POPMemspool;

template <class T>
pop_interface_container<T>::operator T*() {
    return data;
}

#endif
