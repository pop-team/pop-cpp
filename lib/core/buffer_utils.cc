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

#include "paroc_buffer_utils.h"
#include "paroc_exception.h"

template <class T>
void packarray(paroc_buffer &buf, T *param, int size, int flag, paroc_memspool* /*temp*/) {
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

//TODO This should probably be removed
template void packarray<char> (paroc_buffer &buf, char *param, int size, int flags, paroc_memspool *tmp);
template void packarray<unsigned char> (paroc_buffer &buf, unsigned char *param, int size, int flags, paroc_memspool *tmp);
template void packarray<int> (paroc_buffer &buf, int  *param, int size, int flags, paroc_memspool *tmp);
template void packarray<long> (paroc_buffer &buf, long *param, int size, int flags, paroc_memspool *tmp);
template void packarray<unsigned> (paroc_buffer &buf, unsigned  *param, int size, int flags, paroc_memspool *tmp);
template void packarray<short> (paroc_buffer &buf, short *param, int size, int flags, paroc_memspool *tmp);
template void packarray<unsigned short> (paroc_buffer &buf, unsigned short *param, int size, int flags, paroc_memspool *tmp);
template void packarray<double> (paroc_buffer &buf, double *param, int size, int flags, paroc_memspool *tmp);
template void packarray<float> (paroc_buffer &buf, float *param, int size, int flags, paroc_memspool *tmp);
