/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Additional methods for marshalling.
 *
 *
 */

#include "pop_buffer_utils.h"
#include "paroc_exception.h"

template <class T>
void packarray(pop_buffer &buf, T *param, int size, int flag, paroc_memspool* /*temp*/) {
    if(flag & FLAG_MARSHAL) {
        int n=(param!=nullptr) ?  size : 0;
        buf.Pack(&n,1);
        if(n>0) {
            buf.Pack(param,n);
        }
    } else {
        int n;
        buf.UnPack(&n,1);
        if(n>0) {
            buf.UnPack(param,n);
        } else {
            param=nullptr;
        }
    }
}
