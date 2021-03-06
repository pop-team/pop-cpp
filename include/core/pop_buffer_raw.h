/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief raw buffer declaration
 *
 *
 */

#ifndef _POP_BUFFER_RAW_H
#define _POP_BUFFER_RAW_H

#include <vector>

#include "pop_buffer.h"

/**
 * @class pop_buffer_raw
 * @brief Raw buffer declaration, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
class pop_buffer_raw : public pop_buffer {
public:
    pop_buffer_raw();
    ~pop_buffer_raw();
    virtual void Reset();

    virtual void Pack(const int* data, int n);
    virtual void UnPack(int* data, int n);

    virtual void Pack(const unsigned* data, int n);
    virtual void UnPack(unsigned* data, int n);

    virtual void Pack(const long* data, int n);
    virtual void UnPack(long* data, int n);

    virtual void Pack(const unsigned long* data, int n);
    virtual void UnPack(unsigned long* data, int n);

    virtual void Pack(const short* data, int n);
    virtual void UnPack(short* data, int n);

    virtual void Pack(const unsigned short* data, int n);
    virtual void UnPack(unsigned short* data, int n);

    virtual void Pack(const bool* data, int n);
    virtual void UnPack(bool* data, int n);

    virtual void Pack(const char* data, int n);
    virtual void UnPack(char* data, int n);

    virtual void Pack(const unsigned char* data, int n);
    virtual void UnPack(unsigned char* data, int n);

    virtual void Pack(const float* data, int n);
    virtual void UnPack(float* data, int n);

    virtual void Pack(const double* data, int n);
    virtual void UnPack(double* data, int n);

    // added by lwk
    virtual void Pack(const signed char* data, int n);
    virtual void UnPack(signed char* data, int n);

    using pop_buffer::Send;
    virtual bool Send(pop_combox& s, pop_connection* conn);
    using pop_buffer::Recv;
    virtual bool Recv(pop_combox& s, pop_connection* conn);

    virtual int get_size();
    virtual char* get_load();
    virtual void load(char* data, int length);

#ifdef OD_DISCONNECT
    virtual bool RecvCtrl(pop_combox& s, pop_connection* conn = 0);
#endif

protected:
    void CheckUnPack(int sz);

    int unpackpos;
    std::vector<char> packeddata;
};

#endif
