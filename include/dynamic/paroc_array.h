/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: array template used by POP-C++ runtime
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

#include "debug.h"

template<class T> inline void paroc_construct_element(T *data, int n)
{
	for (;n-->0;data++) new(data) T; // Calls the constructor
};

template<class T> inline void paroc_destruct_element(T *data, int n)
{
	for (;n-->0;data++)  data->~T(); // Calls the destructor
};


// Do not call const and destr for non-class types (to avoid a waste of time)
typedef char string64[64];
inline void paroc_construct_element(string64* /*data*/, int /*n*/) {};
inline void paroc_destruct_element(string64*  /*data*/, int /*n*/) {};

inline void paroc_construct_element(unsigned int* /*data*/, int /*n*/) {};
inline void paroc_destruct_element(unsigned int*  /*data*/, int /*n*/) {};

inline void paroc_construct_element(long* /*data*/, int /*n*/) {};
inline void paroc_destruct_element(long*  /*data*/, int /*n*/) {};

inline void paroc_construct_element(unsigned long* /*data*/, int /*n*/) {};
inline void paroc_destruct_element(unsigned long*  /*data*/, int /*n*/) {};

inline void paroc_construct_element(short* /*data*/, int /*n*/) {};
inline void paroc_destruct_element(short*  /*data*/, int /*n*/) {};

inline void paroc_construct_element(unsigned short* /*data*/, int /*n*/) {};
inline void paroc_destruct_element(unsigned short*  /*data*/, int /*n*/) {};

inline void paroc_construct_element(bool* /*data*/, int /*n*/) {};
inline void paroc_destruct_element(bool*  /*data*/, int /*n*/) {};

inline void paroc_construct_element(char* /*data*/, int /*n*/) {};
inline void paroc_destruct_element(char*  /*data*/, int /*n*/) {};

inline void paroc_construct_element(unsigned char* /*data*/, int /*n*/) {};
inline void paroc_destruct_element(unsigned char*  /*data*/, int /*n*/) {};

inline void paroc_construct_element(float* /*data*/, int /*n*/) {};
inline void paroc_destruct_element(float*  /*data*/, int /*n*/) {};

inline void paroc_construct_element(double* /*data*/, int /*n*/) {};
inline void paroc_destruct_element(double*  /*data*/, int /*n*/) {};


/**
 * @class paroc_array
 * @brief C++ class : Array template used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
template<class T> class paroc_array
{
public:
	paroc_array(int asize=0,int grow=0);
	paroc_array(paroc_array &val);

	~paroc_array();
	int GetSize();
	void SetSize(int asize);
	inline operator T*();
	paroc_array & operator =(paroc_array & val);
	void RemoveAll();
	void InsertAt(int index,const T & e,int count=1);
	void InsertAt(int index,const T * e,int count=1);

	void RemoveAt(int index,int count=1);
	int Find(T &e, int startIndex=0);
	void Shrink();
	void SetGrowby(int g);
	int  GetGrowby();
	void DisableDestructors(bool disable=true);

protected:
	T *data;
	int size;
	int actualsize;
	int growby;
	bool autodelete;
};

template<class T>
paroc_array<T>::paroc_array(int asize,int grow)
{
	size=actualsize=0;
	data=0;
	growby=(grow<0) ? 0 : grow;
	SetSize(asize);
	autodelete=true;
}

template<class T>
paroc_array<T>::paroc_array(paroc_array & val)
{
	size=actualsize=0;
	data=0;
	growby=0;
	autodelete=true;

	int n=val.GetSize();
	SetSize(n);
	if (n>0)
	{
		memcpy(data,(T *)val, n*sizeof(T));
	}
}

template<class T>
paroc_array<T>::~paroc_array()
{
	RemoveAll();
}

template<class T>
int paroc_array<T>::GetSize()
{
	return size;
}

template<class T>
void paroc_array<T>::SetSize(int asize)
{
	if (asize<=actualsize)
	{
		if (asize<0) asize=0;
		if (asize>size) paroc_construct_element(data+size,asize-size);
		else if (autodelete) paroc_destruct_element(data+asize,size-asize);
		size=asize;
	}
	else
	{
		int newsize=asize+ (growby<=0 ? asize/3: growby);
		T *data1;
		if ((data1=(T *)realloc(data,sizeof(T)*newsize))==0) throw errno;

		data=data1;
		actualsize=newsize;
		paroc_construct_element(data+size,asize-size);
		size=asize;
	}
}

template<class T>
paroc_array<T>::operator T*()
{
	return data;
}

template<class T>
paroc_array<T> & paroc_array<T>::operator =(paroc_array & val)
{
	int n=val.GetSize();
	SetSize(n);
	memcpy(data, (T *)val, n*sizeof(T));
	return *this;
}

template<class T>
void paroc_array<T>::RemoveAll()
{
	if (data!=0)
	{
		if (autodelete) paroc_destruct_element(data,size);
		free(data);
	}
	data=0;
	size=actualsize=0;
}

template<class T>
void paroc_array<T>::InsertAt(int index, const T & e,int count)
{
	if (count<=0) return;
	if (index<0) index=size;
	int t=size-1;

	SetSize( index>size ? index+count : size+count);
	T *dat=data+t;
	T *dat1=dat+count;
	while (t>=index)
	{
		*(dat+count)=*dat;
		t--;
		dat--;
		dat1--;
	}

	dat=data+index;
	while (count-->0)
	{
		*dat=e;
		dat++;
	}
}

template<class T>
void paroc_array<T>::InsertAt(int index,const T * e,int count)
{
	if (count<=0) return;
	if (index<0) index=size;
	int t=size-1;

	SetSize( index>size ? index+count : size+count);
	T *dat=data+t;
	T *dat1=dat+count;
	while (t>=index)
	{
		*dat1=*dat;
		t--;
		dat--;
		dat1--;
	}
	dat=data+index;
	while (count-->0)
	{
		*dat=*e;
		dat++;
		e++;
	}
}

template<class T> void paroc_array<T>::RemoveAt(int index,int count)
{
	if (index+count>size) count=size-index;
	if (count<=0) return;
	if (autodelete) paroc_destruct_element(data+index,count);
	for (int i=index+count;i<size;i++)
		memcpy(data+i-count,data+i,sizeof(T));

	size-=count;
}

template<class T> int  paroc_array<T>::Find(T &e, int startIndex)
{
	if (startIndex<0) startIndex=0;
	T *t=data;
	for (int i=startIndex;i<size;i++)
	{
		if (memcmp(t,&e,sizeof(T))==0) return i;
		t++;
	}
	return -1;
}

template<class T> void paroc_array<T>::Shrink()
{

	if (size<actualsize)
	{
		if (size<=0) RemoveAll(); else
		{
			T *newData=(T *)realloc(data,sizeof(T)*size);
			if (newData==0) throw errno;
			data=newData;
			actualsize=size;
		}
	}
}

template<class T> void paroc_array<T>::SetGrowby(int g)
{
	if (g>=0) growby=g;
}
template<class T> int paroc_array<T>::GetGrowby()
{
	return growby;
}

template<class T>  void paroc_array<T>::DisableDestructors(bool disable)
{
	autodelete=!disable;
}

#endif


///new
