#ifndef PAROC_MEMSPOOL_H
#define PAROC_MEMSPOOL_H

#include "paroc_list.h"
#include "paroc_interface.h"

typedef void * VOIDPTR;

class paroc_memspool
{
 public:
  paroc_memspool();
  ~paroc_memspool();
  VOIDPTR Alloc(int sz);
  void Managed(VOIDPTR data);

  void Free();
 protected:
  paroc_list<VOIDPTR> memtemp;
};

typedef  paroc_memspool POPMemSpool;

template <class T> class paroc_container
{
 public:
  paroc_container(T *&x,int count);
  ~paroc_container();
 private:
  T *data;
};

template <class T> class paroc_interface_container
{
 public:
  paroc_interface_container(T *&x,int count);
  ~paroc_interface_container();
 private:
  T *data;
  int n;
};

template<class T> 
paroc_container<T>::paroc_container(T *&x,int count)
{
  x=data=new T[count];
}

template<class T> 
paroc_container<T>::~paroc_container()
{
  delete [] data;
}

template<class T> 
paroc_interface_container<T>::paroc_interface_container(T *&x,int count)
{
  x=data=(T *)malloc(count*sizeof(T));
  n=count;
  for (T *tmp=data;count>0; count--, tmp++) new(tmp) T(paroc_interface::_paroc_nobind);
}

template<class T> 
paroc_interface_container<T>::~paroc_interface_container()
{
  if (n>0)
    {
      for (T *tmp=data;n>0; n--, tmp++) tmp->~T();
      free(data);
    }
}

#endif
