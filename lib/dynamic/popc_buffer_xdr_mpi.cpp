/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief Implementation of a XDR buffer aware of MPI receive and send process.
 *
 *
 */

#include "popc_intface.h"

#include "pop_interface.h"
#include "popc_buffer_xdr_mpi.h"
#include "pop_exception.h"
#include "popc_logger.h"

/**
 * Buffer constructor. Start with a stable state.
 */
popc_buffer_xdr_mpi::popc_buffer_xdr_mpi() {
    Reset();
}

/**
 * Buffer destrcutor
 */
popc_buffer_xdr_mpi::~popc_buffer_xdr_mpi() {
}

/**
 * Reset the entire buffer. Erase all its content.
 */
void popc_buffer_xdr_mpi::Reset() {
    unpackpos=20;
    packeddata.clear();
    packeddata.resize(unpackpos);
}

/**
 * Pack an array of integer inside the buffer
 * @param data  pointer to the first element of the array
 * @param n     number of element in the array
 */
void popc_buffer_xdr_mpi::Pack(const int *data, int n) {
    if(n<=0) {
        return;
    }
    int oldsize=packeddata.size();
    packeddata.resize(n*4+oldsize);
    char *dest=packeddata.data()+oldsize;

    XDR xdr;
    xdrmem_create(&xdr,dest,n*4,XDR_ENCODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(int),(xdrproc_t)xdr_int);
    xdr_destroy(&xdr);
}

/**
 * UnPack an array of integer inside the buffer
 * @param data  pointer to the array
 * @param n     number of element to unpack
 */
void popc_buffer_xdr_mpi::UnPack(int *data, int n) {
    if(n<=0) {
        return;
    }

    char *dest = packeddata.data() + unpackpos;
    int sz = 4 * n;
    CheckUnPack(sz);
    XDR xdr;
    xdrmem_create(&xdr, dest, sz, XDR_DECODE);
    xdr_vector(&xdr, (char *)data, n, sizeof(int), (xdrproc_t)xdr_int);
    xdr_destroy(&xdr);
    unpackpos += sz;
}

void popc_buffer_xdr_mpi::Pack(const unsigned *data, int n) {
    if(n<=0) {
        return;
    }
    int oldsize=packeddata.size();
    packeddata.resize(n*4+oldsize);
    char *dest=packeddata.data()+oldsize;

    XDR xdr;
    xdrmem_create(&xdr,dest,n*4,XDR_ENCODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(int),(xdrproc_t)xdr_u_int);
    xdr_destroy(&xdr);

}
void popc_buffer_xdr_mpi::UnPack(unsigned *data, int n) {
    if(n<=0) {
        return;
    }

    int sz=4*n;
    CheckUnPack(sz);

    char *dest=packeddata.data()+unpackpos;
    XDR xdr;
    xdrmem_create(&xdr,dest,sz,XDR_DECODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(unsigned),(xdrproc_t)xdr_u_int);
    xdr_destroy(&xdr);

    unpackpos+=sz;
}

void popc_buffer_xdr_mpi::Pack(const long *data, int n) {
    if(n<=0) {
        return;
    }
    int oldsize=packeddata.size();
    packeddata.resize(n*4+oldsize);
    char *dest=packeddata.data()+oldsize;

    XDR xdr;
    xdrmem_create(&xdr,dest,n*4,XDR_ENCODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(long),(xdrproc_t)xdr_long);
    xdr_destroy(&xdr);
}

void popc_buffer_xdr_mpi::UnPack(long *data, int n) {
    if(n<=0) {
        return;
    }
    char *dest=packeddata.data()+unpackpos;

    int sz=4*n;
    CheckUnPack(sz);

    XDR xdr;
    xdrmem_create(&xdr,dest,sz,XDR_DECODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(long),(xdrproc_t)xdr_long);
    xdr_destroy(&xdr);

    unpackpos+=sz;
}

void popc_buffer_xdr_mpi::Pack(const unsigned long *data, int n) {
    if(n<=0) {
        return;
    }
    int oldsize=packeddata.size();
    packeddata.resize(n*4+oldsize);
    char *dest=packeddata.data()+oldsize;

    XDR xdr;
    xdrmem_create(&xdr,dest,n*4,XDR_ENCODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(long),(xdrproc_t)xdr_u_long);
    xdr_destroy(&xdr);
}

void popc_buffer_xdr_mpi::UnPack(unsigned long *data, int n) {
    if(n<=0) {
        return;
    }
    char *dest=packeddata.data()+unpackpos;

    int sz=n*4;
    CheckUnPack(sz);

    XDR xdr;
    xdrmem_create(&xdr,dest,sz,XDR_DECODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(long),(xdrproc_t)xdr_u_long);
    xdr_destroy(&xdr);

    unpackpos+=sz;
}

void popc_buffer_xdr_mpi::Pack(const short *data, int n) {
    if(n<=0) {
        return;
    }
    int oldsize=packeddata.size();
    packeddata.resize(((n-1)/2+1)*4+oldsize);
    char *dest=packeddata.data()+oldsize;

    XDR xdr;
    xdrmem_create(&xdr,dest,n*2,XDR_ENCODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(short),(xdrproc_t)xdr_short);
    xdr_destroy(&xdr);

}

void popc_buffer_xdr_mpi::UnPack(short *data, int n) {
    if(n<=0) {
        return;
    }
    char *dest=packeddata.data()+unpackpos;

    int sz=2*n;
    CheckUnPack(sz);
    XDR xdr;
    xdrmem_create(&xdr,dest,sz,XDR_DECODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(short),(xdrproc_t)xdr_short);
    xdr_destroy(&xdr);

    unpackpos+=((n-1)/2+1)*4;

}

void popc_buffer_xdr_mpi::Pack(const unsigned short *data, int n) {
    if(n<=0) {
        return;
    }
    int oldsize=packeddata.size();
    packeddata.resize(((n-1)/2+1)*4+oldsize);
    char *dest=packeddata.data()+oldsize;

    XDR xdr;
    xdrmem_create(&xdr,dest,n*2,XDR_ENCODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(short),(xdrproc_t)xdr_u_short);
    xdr_destroy(&xdr);
}

void popc_buffer_xdr_mpi::UnPack(unsigned short *data, int n) {
    if(n<=0) {
        return;
    }
    char *dest=packeddata.data()+unpackpos;

    int sz=2*n;
    CheckUnPack(sz);

    XDR xdr;
    xdrmem_create(&xdr,dest,sz,XDR_DECODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(short),(xdrproc_t)xdr_u_short);
    xdr_destroy(&xdr);

    unpackpos+=((n-1)/2+1)*4;
}

void popc_buffer_xdr_mpi::Pack(const bool *data, int n) {
    if(n<=0) {
        return;
    }
    int t=packeddata.size();
    packeddata.resize(t+((n-1)/4+1)*4);
    char *dat=packeddata.data()+t;
    while(n-->0) {
        *dat=(*data==true);
        dat++;
        data++;
    }
}
void popc_buffer_xdr_mpi::UnPack(bool *data, int n) {
    if(n <= 0) {
        return;
    }
    CheckUnPack(n);
    packeddata.size();

    char *dat = packeddata.data() + unpackpos;
    while(n-->0) {
        *data = (*dat != 0);
        dat++;
        data++;
    }
    unpackpos += ((n-1)/4+1) * 4;
}

void popc_buffer_xdr_mpi::Pack(const char *data, int n) {
    if(n<=0) {
        return;
    }
    int t=packeddata.size();
    packeddata.resize(t+((n-1)/4+1)*4);
    memcpy(packeddata.data()+t,data,n);
}

void popc_buffer_xdr_mpi::UnPack(char *data, int n) {
    if(n<=0) {
        return;
    }
    CheckUnPack(n);
    packeddata.size();
    memcpy(data, packeddata.data()+unpackpos,n);
    unpackpos+=((n-1)/4+1)*4;
}

void popc_buffer_xdr_mpi::Pack(const unsigned char *data, int n) {
    Pack((char *)data,n);
}

void popc_buffer_xdr_mpi::UnPack(unsigned char *data, int n) {
    UnPack((char *)data,n);
}

void popc_buffer_xdr_mpi::Pack(const float *data, int n) {
    if(n<=0) {
        return;
    }
    int oldsize=packeddata.size();
    packeddata.resize(n*4+oldsize);
    char *dest=packeddata.data()+oldsize;

    XDR xdr;
    xdrmem_create(&xdr,dest,n*4,XDR_ENCODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(float),(xdrproc_t)xdr_float);
    xdr_destroy(&xdr);
}

void popc_buffer_xdr_mpi::UnPack(float *data, int n) {
    if(n<=0) {
        return;
    }
    char *dest=packeddata.data()+unpackpos;

    int sz=n*4;
    CheckUnPack(sz);

    XDR xdr;
    xdrmem_create(&xdr,dest,sz,XDR_DECODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(float),(xdrproc_t)xdr_float);
    xdr_destroy(&xdr);

    unpackpos+=sz;

}

void popc_buffer_xdr_mpi::Pack(const double *data, int n) {
    if(n<=0) {
        return;
    }
    int oldsize=packeddata.size();
    packeddata.resize(n*8+oldsize);
    char *dest=packeddata.data()+oldsize;

    XDR xdr;
    xdrmem_create(&xdr,dest,n*8,XDR_ENCODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(double),(xdrproc_t)xdr_double);
    xdr_destroy(&xdr);
}

void popc_buffer_xdr_mpi::UnPack(double *data, int n) {
    if(n<=0) {
        return;
    }
    char *dest=packeddata.data()+unpackpos;

    int sz=8*n;
    CheckUnPack(sz);

    XDR xdr;
    xdrmem_create(&xdr,dest,sz,XDR_DECODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(double),(xdrproc_t)xdr_double);
    xdr_destroy(&xdr);

    unpackpos+=sz;
}

void popc_buffer_xdr_mpi::Pack(const signed char *data, int n) {
    Pack((char *)data,n);
}

void popc_buffer_xdr_mpi::UnPack(signed char *data, int n) {
    UnPack((char *)data,n);
}

void popc_buffer_xdr_mpi::CheckUnPack(int sz) {
    if(static_cast<std::size_t>(sz+unpackpos) > packeddata.size()) {
        pop_exception::paroc_throw(POPC_BUFFER_FORMAT, "Wrong packed data size");
    }
}

bool popc_buffer_xdr_mpi::Send(pop_combox &s, pop_connection *conn) {
    // Pack the header (20 bytes)
    char *dat=packeddata.data();

    if(dat == nullptr) {
        LOG_ERROR("fail 1");
        return false;
    }
    int n = packeddata.size();
    int h[5];
    memset(h, 0, 5 * sizeof(int));

    int type = header.GetType();

    h[0] = popc_htonl(n);
    h[1] = popc_htonl(type);

    switch(type) {
    case TYPE_REQUEST:
        h[2] = popc_htonl(header.GetClassID());
        h[3] = popc_htonl(header.GetMethodID());
        h[4] = popc_htonl(header.GetSemantics());
        break;
    case TYPE_EXCEPTION:
        h[2] = popc_htonl(header.GetExceptionCode());
        break;
    case TYPE_RESPONSE:
        h[2] = popc_htonl(header.GetClassID());
        h[3] = popc_htonl(header.GetMethodID());
        break;
    default:
        return false;
    }
    memcpy(dat, h, 20);

    if(s.Send(dat, n, conn) < 0) {
        return false;
    }
    return true;
}

/**
 *
 */
bool popc_buffer_xdr_mpi::Recv(pop_combox &s, pop_connection *conn) {
    int h[5];
    int n, i;

    // Recv the header
    char *dat = (char *)h;

    Reset();
    n = popc_ntohl(h[0]);
    if(n < 20) {
        LOG_ERROR("[CORE]: XDR Buffer - Bad message header (size error:%d)", n);
        return false;
    }

    int type = popc_ntohl(h[1]);
    header.SetType(type);
    switch(type) {
    case TYPE_REQUEST:
        header.SetClassID(popc_ntohl(h[2]));
        header.SetMethodID(popc_ntohl(h[3]));
        header.SetSemantics(popc_ntohl(h[4]));
        break;
    case TYPE_EXCEPTION:
        header.SetExceptionCode(popc_ntohl(h[2]));
        break;
    case TYPE_RESPONSE:
        header.SetClassID(popc_ntohl(h[2]));
        header.SetMethodID(popc_ntohl(h[3]));
        break;
    default:
        return false;
    }

    packeddata.resize(n);
    dat = packeddata.data()+20;
    n -= 20;

    i = 0;
    while(n) {
        if((i = s.Recv(dat,n, conn)) <= 0) {
            return false;
        }
        dat += i;
        n -= i;
    }
    return true;
}

/**
 * Get the size of packed data in this buffer
 * @return Size of the actual packed data
 */
int popc_buffer_xdr_mpi::get_size() {
    return packeddata.size();
}

/**
 * Get a pointer to the current data in the buffer. Set the header back into the packed data.
 * @return Pointer to the actual data in this buffer
 */
char* popc_buffer_xdr_mpi::get_load() {
    char *dat = packeddata.data();

    if(dat == nullptr) {
        return nullptr;
    }
    int n = packeddata.size();
    int h[5];
    memset(h,0, 5*sizeof(int));

    int type=header.GetType();

    h[0]=popc_htonl(n);
    h[1]=popc_htonl(type);

    switch(type) {
    case TYPE_REQUEST:
        h[2]=popc_htonl(header.GetClassID());
        h[3]=popc_htonl(header.GetMethodID());
        h[4]=popc_htonl(header.GetSemantics());
        break;
    case TYPE_EXCEPTION:
        h[2]=popc_htonl(header.GetExceptionCode());
        break;
    case TYPE_RESPONSE:
        h[2]=popc_htonl(header.GetClassID());
        h[3]=popc_htonl(header.GetMethodID());
        break;
    default:
        LOG_ERROR("fail 2");
        return nullptr;
    }
    memcpy(dat, h, 20);

    return packeddata.data();
}


/**
 * Load the buffer with data by copy.
 * @param data    Pointer to the data to be loaded
 * @param length  Size of the data to be loaded
 */
void popc_buffer_xdr_mpi::load(char* data, int length) {
    int h[5];
    Reset();
    memcpy(packeddata.data(), data, length);
    memcpy(h, packeddata.data(), 20);
    int n = popc_ntohl(h[0]);
    if(n < 20) {
        LOG_ERROR("POP-C++ Error [CORE]: XDR Buffer - Bad message header (size error:%d)", n);
        return;
    }

    int type = popc_ntohl(h[1]);
    header.SetType(type);
    switch(type) {
    case TYPE_REQUEST:
        header.SetClassID(popc_ntohl(h[2]));
        header.SetMethodID(popc_ntohl(h[3]));
        header.SetSemantics(popc_ntohl(h[4]));
        break;
    case TYPE_EXCEPTION:
        header.SetExceptionCode(popc_ntohl(h[2]));
        break;
    case TYPE_RESPONSE:
        header.SetClassID(popc_ntohl(h[2]));
        header.SetMethodID(popc_ntohl(h[3]));
        break;
    default:
        return;
    }

    packeddata.resize(length);
}


#ifdef OD_DISCONNECT
bool popc_buffer_xdr_mpi::RecvCtrl(pop_combox &s, pop_connection *conn) {
    while(true) {
        pop_connection * t = (pop_connection *) s.Wait();
        if(t == NULL) {
            pop_exception::paroc_throw("[pop_buffer_xdr.cc] : Remote Object not alive");
        }
        if(!Recv(s, t)) {
            pop_exception::paroc_throw("Recv failed");
        }
        if(header.GetType() == TYPE_RESPONSE) {
            if(header.GetClassID() == 0 && header.GetMethodID() == 6) {
                return true;
            } else {
                pop_message_header h = header;
                int unpackposold = unpackpos;
                auto packeddataold = packeddata;
                pop_connection * t = (pop_connection *) s.Wait();
                if(t == NULL) {
                    pop_exception::paroc_throw("[pop_buffer_xdr.cc] : Remote Object not alive");
                }
                if(!Recv(s, t)) {
                    pop_exception::paroc_throw("Recv failed 2");
                }
                Reset();
                header = h;
                unpackpos = unpackposold;
                packeddata = packeddataold;
                return false;
            }
        }
    }
}
#endif
