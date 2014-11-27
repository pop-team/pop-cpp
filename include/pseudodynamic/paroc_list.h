/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: list data structure
 */

#ifndef POPC_LIST_H
#define POPC_LIST_H

#include <errno.h>
#include <assert.h>
typedef void * POSITION;

/**
 * @class paroc_list
 * @brief List data structure (template), used by POP-C++ runtime.
 *
 * @author Tuan Anh Nguyen
 */
template <class T>class paroc_list
{
	public:
	paroc_list();
	~paroc_list();
	POSITION GetHeadPosition();
	POSITION GetTailPosition();
	T & GetNext(POSITION & pos);
	T & GetPrev(POSITION & pos);
	T & GetAt(POSITION pos);
	void SetAt(POSITION pos,T &dat);

	void InsertBefore(POSITION pos,T &dat);
	void InsertAfter(POSITION pos,T &dat);
	void AddHead(T &dat);
	void AddTail(T &dat);
	T & AddHeadNew();
	T & AddTailNew();

	void operator = (paroc_list &list);

	void RemoveHead();
	void RemoveTail();
	void RemoveAll();
	void RemoveAt(POSITION pos);

	bool IsEmpty();
	int GetCount();
	protected:
	struct ListElement
	{
		T data;
		ListElement *next,*prev;
	} Head;
	int count;
};


template <class T>
paroc_list<T>::paroc_list()
{
	Head.next=Head.prev=&Head;
	count=0;
}

template <class T>
paroc_list<T>::~paroc_list()
{
	RemoveAll();
}

template <class T>
POSITION paroc_list<T>::GetHeadPosition()
{
	return (Head.next!=&Head) ? (POSITION ) Head.next : 0;
}

template <class T>
POSITION paroc_list<T>::GetTailPosition()
{
	return (Head.prev!=&Head) ? (POSITION ) Head.prev : 0;
}

template <class T>
T & paroc_list<T>::GetNext(POSITION & pos)
{
	ListElement *e=(ListElement *)pos;
	assert(e!=NULL);

	T &dat=e->data;
	e=e->next;
	pos=(e!=&Head) ? (POSITION)e : 0;
	return dat;
}

template <class T>
T & paroc_list<T>::GetPrev(POSITION & pos)
{
	ListElement *e=(ListElement *)pos;
	assert(e!=NULL);

	T &dat=e->data;
	e=e->prev;
	pos=(e!=&Head) ? (POSITION)e : 0;
	return dat;
}

template <class T>
inline T & paroc_list<T>::GetAt(POSITION pos)
{
	assert(pos!=NULL);
	return ((ListElement *)pos)->data;
}


template <class T>
inline void paroc_list<T>::SetAt(POSITION pos,T &dat)
{
	((ListElement *)pos)->data=dat;
}


template <class T>
void paroc_list<T>::InsertBefore(POSITION pos,T &dat)
{
	ListElement *e=new ListElement;
	if (e==0) throw ENOMEM;

	ListElement *t=(ListElement *)pos;
	e->data=dat;
	e->next=t;
	e->prev=t->prev;
	t->prev->next=e;
	t->prev=e;
	count++;
}


template <class T>
void paroc_list<T>::InsertAfter(POSITION pos,T &dat)
{
	ListElement *e=new ListElement;
	if (e==0) throw ENOMEM;

	ListElement *t=(ListElement *)pos;
	e->data=dat;
	e->prev=t;
	e->next=t->next;
	t->next=e;
	e->next->prev=e;
	count++;
}


template <class T>
void paroc_list<T>::AddHead(T &dat)
{
	ListElement *e=new ListElement;
	if (e==0) throw ENOMEM;
	e->data=dat;
	e->next=Head.next;
	e->prev=&Head;
	e->next->prev=e;
	Head.next=e;
	count++;
}

template <class T>
void paroc_list<T>::AddTail(T &dat)
{
	ListElement *e=new ListElement;
	if (e==0) throw ENOMEM;
	e->data=dat;
	e->prev=Head.prev;
	e->next=&Head;
	e->prev->next=e;
	Head.prev=e;
	count++;
}

template <class T>
T & paroc_list<T>::AddHeadNew()
{
	ListElement *e=new ListElement;
	if (e==0) throw ENOMEM;
	e->next=Head.next;
	e->prev=&Head;
	e->next->prev=e;
	Head.next=e;
	count++;
	return e->data;
}

template <class T>
T & paroc_list<T>::AddTailNew()
{
	ListElement *e=new ListElement;
	if (e==0) throw ENOMEM;
	e->prev=Head.prev;
	e->next=&Head;
	e->prev->next=e;
	Head.prev=e;
	count++;
	return e->data;
}

template <class T>
void paroc_list<T>::operator = (paroc_list &list)
{
	RemoveAll();
	POSITION pos=list.GetHeadPosition();
	while (pos!=NULL)
	{
		AddTail(list.GetNext(pos));
	}
}

template <class T>
void paroc_list<T>::RemoveHead()
{
	if (!count) return;
	ListElement *e=Head.next;
	Head.next=Head.next->next;
	Head.next->prev=&Head;
	delete e;
	count--;
}

template <class T>
void paroc_list<T>::RemoveTail()
{
	if (!count) return;
	ListElement *e=Head.prev;
	Head.prev=Head.prev->prev;
	Head.prev->next=&Head;
	count--;
	delete e;
}

template <class T>
void paroc_list<T>::RemoveAt(POSITION pos)
{
	if (pos==NULL) return;
	ListElement *e=(ListElement *)pos;
	e->next->prev=e->prev;
	e->prev->next=e->next;
	delete e;
	count--;
}

template <class T>
void paroc_list<T>::RemoveAll()
{
	while (Head.next!=&Head) RemoveHead();
	count=0;
}


template <class T>
bool paroc_list<T>::IsEmpty()
{
	return (Head.next==&Head);
}

template <class T>
int paroc_list<T>::GetCount()
{
	return count;

}


#endif





