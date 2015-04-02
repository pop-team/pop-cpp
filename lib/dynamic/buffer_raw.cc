/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of raw message buffer.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_BufferRAW instead of pop_buffer_raw
 */

#include <stdio.h>
#include <string.h>
//#include "paroc_interface.h"
#include "pop_buffer_raw.h"
#include "paroc_exception.h"
#include "popc_logger.h"

pop_buffer_raw::pop_buffer_raw() {
    Reset();
}

pop_buffer_raw::~pop_buffer_raw() {}

void pop_buffer_raw::Reset() {
    unpackpos=20;
    //packeddata.RemoveAll();
    packeddata.resize(20);
}

void pop_buffer_raw::Pack(const char *data, int n) {
    if(n<=0) {
        return;
    }
    int t=packeddata.size();
    packeddata.resize(t+((n-1)/4+1)*4);
    memcpy(packeddata.data()+t,data,n);
}

void pop_buffer_raw::UnPack(char *data, int n) {
    if(n<=0) {
        return;
    }
    //CheckUnPack(n); // Error with this check in 64 bits
    packeddata.size();
    memcpy(data, packeddata.data()+unpackpos,n);
    unpackpos+=((n-1)/4+1)*4;
}

void pop_buffer_raw::Pack(const int *data, int n) {
    Pack((const char *)data,n*sizeof(int));
}

void pop_buffer_raw::UnPack(int *data, int n) {
    UnPack((char *)data,n*sizeof(int));
}

void pop_buffer_raw::Pack(const unsigned *data, int n) {
    Pack((const char *)data,n*sizeof(unsigned));

}
void pop_buffer_raw::UnPack(unsigned *data, int n) {
    UnPack((char *)data,n*sizeof(unsigned));
}

void pop_buffer_raw::Pack(const long *data, int n) {
    Pack((const char *)data,n*sizeof(long));
}

void pop_buffer_raw::UnPack(long *data, int n) {
    UnPack((char *)data,n*sizeof(long));
}

void pop_buffer_raw::Pack(const unsigned long *data, int n) {
    Pack((const char *)data,n*sizeof(unsigned long));
}

void pop_buffer_raw::UnPack(unsigned long *data, int n) {
    UnPack((char *)data,n*sizeof(unsigned long));
}

void pop_buffer_raw::Pack(const short *data, int n) {
    Pack((const char *)data,n*sizeof(short));
}

void pop_buffer_raw::UnPack(short *data, int n) {
    UnPack((char *)data,n*sizeof(short));
}

void pop_buffer_raw::Pack(const unsigned short *data, int n) {
    Pack((const char *)data,n*sizeof(unsigned short));
}

void pop_buffer_raw::UnPack(unsigned short *data, int n) {
    UnPack((char *)data,n*sizeof(unsigned short));
}

void pop_buffer_raw::Pack(const bool *data, int n) {
    Pack((const char *)data,n*sizeof(bool));
}

void pop_buffer_raw::UnPack(bool *data, int n) {
    UnPack((char *)data,n*sizeof(bool));
}


void pop_buffer_raw::Pack(const unsigned char *data, int n) {
    Pack((char *)data,n);
}

void pop_buffer_raw::UnPack(unsigned char *data, int n) {
    UnPack((char *)data,n);
}

void pop_buffer_raw::Pack(const float *data, int n) {
    Pack((char *)data,n*sizeof(float));
}

void pop_buffer_raw::UnPack(float *data, int n) {
    UnPack((char *)data,n*sizeof(float));
}

void pop_buffer_raw::Pack(const double *data, int n) {
    Pack((char *)data,n*sizeof(double));
}

void pop_buffer_raw::UnPack(double *data, int n) {
    UnPack((char *)data,n*sizeof(double));
}

// added by lwk
void pop_buffer_raw::Pack(const signed char *data, int n) {
    Pack((char *)data,n); // TODO lwk: Check that this cast is not problematic
}

void pop_buffer_raw::UnPack(signed char *data, int n) {
    UnPack((char *)data,n);
}

void pop_buffer_raw::CheckUnPack(int sz) {
    if(static_cast<std::size_t>(sz+unpackpos) > packeddata.size()) {
        paroc_exception::paroc_throw(POPC_BUFFER_FORMAT, "Wrong buffer format in pop_buffer_raw::CheckUnPack");
    }
}

/**
 * Send the packed data to the matching combox
 * @param s
 * @param conn
 * @return
 */
bool pop_buffer_raw::Send(paroc_combox &s, paroc_connection *conn) {
    // Pack the header (20 bytes)
    char *dat = packeddata.data();

    if(dat == nullptr) {
        LOG_ERROR("fail 1");
        return false;
    }

    int n = packeddata.size();
    int h[5];
    memset(h, 0, 5 * sizeof(int));

    int type = header.GetType();

    h[0] = n;
    h[1] = type;

    switch(type) {
    case TYPE_REQUEST:
        h[2] = header.GetClassID();
        h[3] = header.GetMethodID();
        h[4] = header.GetSemantics();
        break;
    case TYPE_EXCEPTION:
        h[2] = header.GetExceptionCode();
        break;
    case TYPE_RESPONSE:
        h[2] = header.GetClassID();
        h[3] = header.GetMethodID();
        break;
    default:
        return false;
    }
    memcpy(dat, h, 20);
    if(s.Send(dat, n, conn) < 0) {
        LOG_WARNING("Fail to send a message!");
        return false;
    }
    return true;
}

// Propagation of exceptions back to caller...
bool pop_buffer_raw::Recv(paroc_combox &s, paroc_connection *conn) {
    int h[5];
    int n, i;

    // Recv the header
    char *dat = (char*)h;
    n = 20;
    do {
        if((i = s.Recv(dat,n, conn)) <= 0) {
            LOG_ERROR("[CORE] combox recv returned %d", i);
            return false;
        }
        n -= i;
        dat += i;
    }   while(n);

    Reset();
    n = h[0];
    if(n < 20) {
        LOG_ERROR("[CORE] - Buffer RAW - bad message header (size error:%d)", n);
        return false;
    }

    int type = h[1];
    header.SetType(type);
    switch(type) {
    case TYPE_REQUEST:
        header.SetClassID(h[2]);
        header.SetMethodID(h[3]);
        header.SetSemantics(h[4]);
        break;
    case TYPE_EXCEPTION:
        header.SetExceptionCode(h[2]);
        break;
    case TYPE_RESPONSE:
        header.SetClassID(h[2]);
        header.SetMethodID(h[3]);
        break;
    default:
        LOG_ERROR("Unknown type %d", type);
        return false;
    }

    packeddata.resize(n);
    n -= 20;

    dat = packeddata.data() + 20;

    // Recv data if there is some
    i = 0;

    while(n) {
        if((i = s.Recv(dat, n, conn)) <= 0) {
            LOG_ERROR("[CORE] combox recv returned %d", i);
            return false;
        }
        dat += i;
        n -= i;
    }

    return true;
}

int pop_buffer_raw::get_size() {
    return packeddata.size();
}

char* pop_buffer_raw::get_load() {
    // Pack the header (20 bytes)
    char *dat = packeddata.data();

    if(!dat) {
        return nullptr;
    }

    int n = packeddata.size();
    int h[5];
    memset(h,0, 5 * sizeof(int));

    int type = header.GetType();

    h[0] = n;
    h[1] = type;

    switch(type) {
    case TYPE_REQUEST:
        h[2] = header.GetClassID();
        h[3] = header.GetMethodID();
        h[4] = header.GetSemantics();
        break;
    case TYPE_EXCEPTION:
        h[2] = header.GetExceptionCode();
        break;
    case TYPE_RESPONSE:
        h[2] = header.GetClassID();
        h[3] = header.GetMethodID();
        break;
    default:
        LOG_ERROR("fail 2");
        return nullptr;
    }

    memcpy(dat, h, 20);

    return packeddata.data();
}

void pop_buffer_raw::load(char* data, int length) {
    memcpy(packeddata.data(), data, length);
}

#ifdef OD_DISCONNECT
bool pop_buffer_raw::RecvCtrl(paroc_combox &s, paroc_connection *conn) {
    while(true) {
        paroc_connection* t = (paroc_connection*) s.Wait();
        if(!t) {
            paroc_exception::paroc_throw("Remote Object not alive (1)");
        }

        if(!Recv(s, t)) {
            paroc_exception::paroc_throw(errno);
        }

        if(header.GetType() == TYPE_RESPONSE) {
            if(header.GetClassID() == 0 && header.GetMethodID() == 6) {
                return true;
            } else {
                paroc_message_header h = header;
                int unpackposold = unpackpos;

                auto packeddataold = packeddata;
                auto t = (paroc_connection *) s.Wait();

                if(!t) {
                    paroc_exception::paroc_throw("Remote Object not alive (2)");
                }

                if(!Recv(s, t)) {
                    paroc_exception::paroc_throw(errno);
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
