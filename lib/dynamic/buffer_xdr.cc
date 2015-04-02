/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of SUN-XDR message buffer.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_BufferXDR instead of pop_buffer_xdr
 */
#include "popc_intface.h"

#include <rpc/types.h>
#include <rpc/xdr.h>
// #include "pop_interface.h"
#include "pop_buffer_xdr.h"
#include "pop_exception.h"
#include "popc_logger.h"

pop_buffer_xdr::pop_buffer_xdr() {
    Reset();
}

pop_buffer_xdr::~pop_buffer_xdr() {}

void pop_buffer_xdr::Reset() {
    unpackpos=20;
    packeddata.clear();
    packeddata.resize(unpackpos);
}

void pop_buffer_xdr::Pack(const int *data, int n) {
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
void pop_buffer_xdr::UnPack(int *data, int n) {
    if(n<=0) {
        return;
    }
    char *dest=packeddata.data()+unpackpos;

    int sz=4*n;

    CheckUnPack(sz);

    XDR xdr;
    xdrmem_create(&xdr,dest,sz,XDR_DECODE);
    xdr_vector(&xdr,(char *)data,n,sizeof(int),(xdrproc_t)xdr_int);
    xdr_destroy(&xdr);

    unpackpos+=sz;
}

void pop_buffer_xdr::Pack(const unsigned *data, int n) {
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
void pop_buffer_xdr::UnPack(unsigned *data, int n) {
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

void pop_buffer_xdr::Pack(const long *data, int n) {
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

void pop_buffer_xdr::UnPack(long *data, int n) {
    if(n<=0) {
        return;
    }
    char *dest=packeddata.data()+unpackpos;

    int sz=4*n;
    CheckUnPack(sz);

    XDR xdr;
    xdrmem_create(&xdr,dest,sz,XDR_DECODE);
    xdr_vector(&xdr, (char*)data,n,sizeof(long),(xdrproc_t)xdr_long);
    xdr_destroy(&xdr);

    unpackpos+=sz;
}

void pop_buffer_xdr::Pack(const unsigned long *data, int n) {
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

void pop_buffer_xdr::UnPack(unsigned long *data, int n) {
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

void pop_buffer_xdr::Pack(const short *data, int n) {
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

void pop_buffer_xdr::UnPack(short *data, int n) {
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

void pop_buffer_xdr::Pack(const unsigned short *data, int n) {
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

void pop_buffer_xdr::UnPack(unsigned short *data, int n) {
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

void pop_buffer_xdr::Pack(const bool *data, int n) {
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
void pop_buffer_xdr::UnPack(bool *data, int n) {
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

void pop_buffer_xdr::Pack(const char *data, int n) {
    if(n<=0) {
        return;
    }
    int t=packeddata.size();
    packeddata.resize(t+((n-1)/4+1)*4);
    memcpy(packeddata.data()+t,data,n);
}

void pop_buffer_xdr::UnPack(char *data, int n) {
    if(n<=0) {
        return;
    }
    CheckUnPack(n);
    packeddata.size();
    memcpy(data, (packeddata.data())+unpackpos,n);
    unpackpos+=((n-1)/4+1)*4;
}

void pop_buffer_xdr::Pack(const unsigned char *data, int n) {
    Pack((char *)data,n);
}

void pop_buffer_xdr::UnPack(unsigned char *data, int n) {
    UnPack((char *)data,n);
}

void pop_buffer_xdr::Pack(const float *data, int n) {
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

void pop_buffer_xdr::UnPack(float *data, int n) {
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

void pop_buffer_xdr::Pack(const double *data, int n) {
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

void pop_buffer_xdr::UnPack(double *data, int n) {
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

void pop_buffer_xdr::Pack(const signed char *data, int n) {
    Pack((char *)data,n);
}

void pop_buffer_xdr::UnPack(signed char *data, int n) {
    UnPack((char *)data,n);
}

void pop_buffer_xdr::CheckUnPack(int sz) {
    if(static_cast<std::size_t>(sz+unpackpos) > packeddata.size()) {
        LOG_ERROR("Wrong buffer format: %d + %d > %d", sz, unpackpos, packeddata.size()); // TODO LW: Why is it allowed to have <
        pop_exception::paroc_throw(POPC_BUFFER_FORMAT, "Wrong buffer format in pop_buffer_xdr::CheckUnPack");
    }
}

/**
 * Send the packed data to the matching combox
 * @param s
 * @param conn
 * @return
 */
bool pop_buffer_xdr::Send(pop_combox &s, pop_connection *conn) {
    // Pack the header (20 bytes)
    char *dat = packeddata.data();

    if(dat == NULL) {
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

    LOG_DEBUG_T("XDR", "Send methodid=%d", header.GetMethodID());
    LOG_DEBUG_T("XDR", "Send classId=%d", header.GetClassID());

    memcpy(dat, h, 20);

    return s.Send(dat, n, conn) >= 0;
}

/**
 *
 */
bool pop_buffer_xdr::Recv(pop_combox &s, pop_connection *conn) {
    int h[5];
    int n, i;

    // Recv the header
    char *dat = (char *)h;
    n = 20;
    do {
        if((i = s.Recv(dat, n, conn)) <= 0) {
            LOG_DEBUG("combox recv returned %d", i);
            return false;
        }
        n -= i;
        dat += i;
    } while(n);

    Reset();
    n = popc_ntohl(h[0]);
    if(n < 20) {
        LOG_ERROR("[CORE] XDR Buffer - Bad message header (size error:%d)", n);
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
        LOG_ERROR("Unknown type %d", type);
        return false;
    }

    LOG_DEBUG_T("XDR", "Read methodid=%d", header.GetMethodID());
    LOG_DEBUG_T("XDR", "Read classId=%d", header.GetClassID());

    packeddata.resize(n);
    n -= 20;
    dat = packeddata.data()+20;

    i = 0;

    while(n) {
        if((i = s.Recv(dat,n, conn)) <= 0) {
            LOG_DEBUG("combox recv returned %d", i);
            return false;
        }
        dat += i;
        n -= i;
    }

    return true;
}

int pop_buffer_xdr::get_size() {
    return packeddata.size();
}

char* pop_buffer_xdr::get_load() {
    char *dat = packeddata.data();

    if(!dat) {
        return NULL;
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
        return NULL;
    }

    memcpy(dat, h, 20);

    return packeddata.data();
}

void pop_buffer_xdr::load(char* data, int length) {
    int h[5];

    Reset();
    memcpy(packeddata.data(), data, length);
    memcpy(h, packeddata.data(), 20);

    int n = popc_ntohl(h[0]);
    if(n < 20) {
        LOG_ERROR("[CORE] XDR Buffer - Bad message header (size error:%d)", n);
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
bool pop_buffer_xdr::RecvCtrl(pop_combox &s, pop_connection *conn) {
    while(true) {
        pop_connection * t = (pop_connection *) s.Wait();
        if(!t) {
            pop_exception::paroc_throw("Remote Object not alive (1)");
        }

        if(!Recv(s, t)) {
            pop_exception::paroc_throw(errno);
        }

        if(header.GetType() == TYPE_RESPONSE) {
            if(header.GetClassID() == 0 && header.GetMethodID() == 6) {
                return true;
            } else {
                pop_message_header h = header;
                int unpackposold = unpackpos;
                auto packeddataold = packeddata;
                auto t = (pop_connection *) s.Wait();

                if(!t) {
                    pop_exception::paroc_throw("Remote Object not alive (2)");
                }

                if(!Recv(s, t)) {
                    pop_exception::paroc_throw(errno);
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
