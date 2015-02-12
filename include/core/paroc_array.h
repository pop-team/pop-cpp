/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Array template used by POP-C++ runtime
 *
 *
 */

#ifndef _POPC_ARRAY_H
#define _POPC_ARRAY_H

//#ifdef __GNUC__
#include <new>
//#endif

#include <errno.h>
#include <memory.h>
#include <stdlib.h>

#include <typeinfo>

#define FATAL {fprintf(stderr, "Fatal error on %s %s %d", __FILE__, __FUNCTION__, __LINE__); exit(-1);}

template<typename T>
inline void paroc_construct_element(T *data, int n) {
    for(; n-->0; data++) {
        new(data) T;    // Calls the constructor
    }
}

template<typename T>
inline void paroc_destruct_element(T *data, int n) {
    for(; n-->0; data++) {
        data->~T();    // Calls the destructor
    }
}

//Arrays have no destructors, therefore, it necessary to overload
//these functions

template<typename X, std::size_t N>
inline void paroc_construct_element(X (*)[N] /*data*/, int /*n*/) {}

template<typename X, std::size_t N>
inline void paroc_destruct_element(X (*)[N]  /*data*/, int /*n*/) {}

/**
 * @class paroc_array
 * @brief C++ class : Array template used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
template<class T> class paroc_array {
public:
    paroc_array(int asize=0);
    paroc_array(paroc_array &val);

    ~paroc_array();
    int size();
    void resize(int asize);
    paroc_array & operator =(paroc_array & val);
    void RemoveAll();
    void InsertAt(int index,const T & e,int count=1);
    void InsertAt(int index,const T * e,int count=1);

    void RemoveAt(int index,int count=1);
    int Find(T &e, int startIndex=0);
    void Shrink();

    T& operator[](std::size_t i){
        return m_data[i];
    }

    const T& operator[](std::size_t i) const {
        return m_data[i];
    }

    T* data(){
        return m_data;
    }

    const T* data() const {
        return m_data;
    }

protected:
    T *m_data;
    int m_size;
    int actualsize;
    int __fake_1;
    bool __fake; //For some obscure reasons, cannot be rmeoved
};

template<class T>
paroc_array<T>::paroc_array(int asize) {
    m_size=actualsize=0;
    m_data=0;
    resize(asize);
}

template<class T>
paroc_array<T>::paroc_array(paroc_array & val) {
    m_size=actualsize=0;
    m_data=0;

    int n=val.size();
    resize(n);
    if(n>0) {
        memcpy(m_data,(T *)val, n*sizeof(T));
    }
}

template<class T>
paroc_array<T>::~paroc_array() {
    RemoveAll();
}

template<class T>
int paroc_array<T>::size() {
    return m_size;
}

template<class T>
void paroc_array<T>::resize(int asize) {
    if(asize<=actualsize) {
        if(asize<0) {
            asize=0;
        }
        if(asize>m_size) {
            paroc_construct_element(m_data+m_size,asize-m_size);
        } else {
            paroc_destruct_element(m_data+asize,m_size-asize);
        }
    } else {
        int newsize=asize+ asize/3;
        if(newsize == asize){
            ++newsize;
        }
        T *data1;
        if((data1=(T *)realloc(m_data,sizeof(T)*newsize))==0) {
            FATAL;
        }

        m_data=data1;
        actualsize=newsize;
        paroc_construct_element(m_data+m_size,asize-m_size);
    }

    m_size=asize;
}

template<class T>
paroc_array<T> & paroc_array<T>::operator =(paroc_array & val) {
    int n=val.size();
    resize(n);
    memcpy(m_data, val.m_data, n * sizeof(T));
    return *this;
}

template<class T>
void paroc_array<T>::RemoveAll() {
    if(m_data) {
        paroc_destruct_element(m_data,m_size);
        free(m_data);
    }

    m_data=0;
    m_size=actualsize=0;
}

template<class T>
void paroc_array<T>::InsertAt(int index, const T & e,int count) {
    if(count<=0) {
        return;
    }
    if(index<0) {
        index=size();
    }
    int t=size()-1;

    resize(index>size() ? index+count : size()+count);
    T *dat=m_data+t;
    T *dat1=dat+count;
    while(t>=index) {
        *(dat+count)=*dat;
        t--;
        dat--;
        dat1--;
    }

    dat=m_data+index;
    while(count-->0) {
        *dat=e;
        dat++;
    }
}

template<class T>
void paroc_array<T>::InsertAt(int index,const T * e,int count) {
    if(count<=0) {
        return;
    }
    if(index<0) {
        index=size();
    }
    int t=size()-1;

    resize(index>size() ? index+count : size()+count);
    T *dat=m_data+t;
    T *dat1=dat+count;
    while(t>=index) {
        *dat1=*dat;
        t--;
        dat--;
        dat1--;
    }
    dat=m_data+index;
    while(count-->0) {
        *dat=*e;
        dat++;
        e++;
    }
}

template<class T> void paroc_array<T>::RemoveAt(int index,int count) {
    if(index+count>size()) {
        count=size()-index;
    }
    if(count<=0) {
        return;
    }
    paroc_destruct_element(m_data+index,count);
    for(int i=index+count; i<size(); i++) {
        memcpy(m_data+i-count,m_data+i,sizeof(T));
    }

    m_size-=count;
}

template<class T> int  paroc_array<T>::Find(T &e, int startIndex) {
    if(startIndex<0) {
        startIndex=0;
    }
    T *t=m_data;
    for(int i=startIndex; i<size(); i++) {
        if(memcmp(t,&e,sizeof(T))==0) {
            return i;
        }
        t++;
    }
    return -1;
}

template<class T> void paroc_array<T>::Shrink() {

    if(m_size<actualsize) {
        if(m_size<=0) {
            RemoveAll();
        } else {
            T *newData=(T *)realloc(m_data,sizeof(T)*size());
            if(newData==0) {
                FATAL;
            }
            m_data=newData;
            actualsize=m_size;
        }
    }
}

#endif
