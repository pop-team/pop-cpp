/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: POP-C++ memory management
 */

#ifndef POPC_MEMSPOOL_H
#define POPC_MEMSPOOL_H

#include "paroc_list.h"
#include "paroc_interface.h"

typedef void * VOIDPTR;

/**
 * @class paroc_memspool
 * @brief POP-C++ memory management, used by POP-C++ runtime.
 *
 * @author Tuan Anh Nguyen
 */
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

template <class T> class paroc_container
{
public:
	paroc_container(int count);
	~paroc_container();
	inline operator T *();
private:
	T *data;
};

template <class T> class paroc_interface_container
{
public:
	paroc_interface_container(int count);
	~paroc_interface_container();
	inline operator T *();
private:
	T *data;
	int n;
};

template<class T>
paroc_container<T>::paroc_container(int count)
{
	data=(count>0)? new T[count] : NULL;
}

template<class T>
paroc_container<T>::~paroc_container()
{
	if (data!=NULL) delete [] data;
}

template<class T>
paroc_container<T>::operator T* ()
{
	return data;
}

template<class T>
paroc_interface_container<T>::paroc_interface_container(int count)
{
	data=(count>0)? (T *)malloc(count*sizeof(T)) : NULL;
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
typedef paroc_memspool POPMemspool;

template<class T>
paroc_interface_container<T>::operator T*()
{
	return data;
}

#endif
