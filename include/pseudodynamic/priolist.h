#ifndef __PRIOLIST_H
#define __PRIOLIST_H

#include <assert.h>
#include "paroc_array.h"
#include "paroc_mutex.h"

template <class T, class Tprio> class CPrioList
{
public:
	CPrioList();
	~CPrioList();

	void GetData(paroc_array<int> &keys, paroc_array<T> &elems, paroc_array<Tprio> &prio);
	bool UpdatePriority(int key, Tprio prio);
	bool UpdateElement(int key, T &elem);
	bool Update(int key, T &elem, Tprio prio);

	int AddItem(T &data, Tprio prio);
	bool RemoveItem(int key);

private:
	struct PrioItem
	{
		T data;
		Tprio priority;
		int key;
		PrioItem *next;
		PrioItem *prev;
	} head;
	int count;
	int nextkey;

	paroc_mutex mylock;
};



template <class T, class Tprio>
CPrioList<T, Tprio>::CPrioList()
{
	head.next=&head;
	head.prev=&head;
	count=0;

	//Init mutex lock...
}

template <class T, class Tprio>
CPrioList<T, Tprio>::~CPrioList()
{
	PrioItem *t=head.next;
	while (t!=&head)
	{
		PrioItem *t1=t;
		t=t->next;
		delete t1;
	}
}

template <class T, class Tprio>
void CPrioList<T, Tprio>::GetData(paroc_array<int> &keys, paroc_array<T> &elems, paroc_array<Tprio> &prio)
{
	paroc_mutex_locker look(mylock);
	keys.SetSize(0);
	elems.SetSize(0);
	prio.SetSize(0);
	PrioItem *t=head.next;
	while (t!=&head)
	{
		keys.InsertAt(-1,t->key);
		elems.InsertAt(-1, t->data);
		prio.InsertAt(-1, t->priority);
		t=t->next;
	}
}

template <class T, class Tprio>
bool CPrioList<T, Tprio>::UpdatePriority(int key, Tprio newprio)
{
	paroc_mutex_locker look(mylock);
	PrioItem *t=head.next;
	while (t!=&head && t->key!=key) t=t->next;

	if (t==&head) return false;

	if (t->priority==newprio)
	{
		return true;
	}
	if (t->priority>newprio)
	{
		PrioItem *t1=t->next;
		while (t1!=&head && t1->priority>= newprio) t1=t1->next;
		if (t1!=t->next)
		{
			t->prev->next=t->next;
			t->next->prev=t->prev;

			t->next=t1;
			t->prev=t1->prev;

			t1->prev->next=t;
			t1->prev=t;
		}
	}
	else
	{
		PrioItem *t1=t->prev;
		while (t1!=&head && t1->priority< newprio) t1=t1->prev;
		if (t1!=t->prev)
		{
			t->prev->next=t->next;
			t->next->prev=t->prev;

			t->next=t1->next;
			t->prev=t1;

			t1->next->prev=t;
			t1->next=t;
		}
	}

	t->priority=newprio;
	return true;
}



template <class T, class Tprio>
bool CPrioList<T, Tprio>::UpdateElement(int key, T &elem)
{
	paroc_mutex_locker look(mylock);
	PrioItem *t=head.next;
	while (t!=&head && t->key!=key) t=t->next;

	if (t==&head) return false;
	t->data=elem;
	return true;
}

template <class T, class Tprio>
bool CPrioList<T, Tprio>::Update(int key, T &elem, Tprio newprio)
{
	paroc_mutex_locker look(mylock);
	PrioItem *t=head.next;
	while (t!=&head && t->key!=key) t=t->next;

	if (t==&head) return false;
	t->data=elem;

	if (t->priority==newprio)
	{
		return true;
	}
	if (t->priority>newprio)
	{
		PrioItem *t1=t->next;
		while (t1!=&head && t1->priority>= newprio) t1=t1->next;
		if (t1!=t->next)
		{
			t->prev->next=t->next;
			t->next->prev=t->prev;

			t->next=t1;
			t->prev=t1->prev;

			t1->prev->next=t;
			t1->prev=t;
		}
	}
	else
	{
		PrioItem *t1=t->prev;
		while (t1!=&head && t1->priority< newprio) t1=t1->prev;
		if (t1!=t->prev)
		{
			t->prev->next=t->next;
			t->next->prev=t->prev;

			t->next=t1->next;
			t->prev=t1;

			t1->next->prev=t;
			t1->next=t;
		}
	}

	t->priority=newprio;
	return true;
}


template <class T, class Tprio>
int CPrioList<T, Tprio>::AddItem(T &data, Tprio prio)
{
	paroc_mutex_locker look(mylock);
	PrioItem *t=new PrioItem;
	t->data=data;
	t->priority=prio;
	t->key=(nextkey++);

	PrioItem *t1=head.next;
	while (t1!=&head && t1->priority>=prio) t1=t1->next;

	t->next=t1;
	t->prev=t1->prev;
	t1->prev->next=t;
	t1->prev=t;
	return t->key;
}

template <class T, class Tprio>
bool CPrioList<T, Tprio>::RemoveItem(int key)
{
	paroc_mutex_locker look(mylock);
	PrioItem *t=head.next;
	while (t!=&head && t->key!=key) t=t->next;

	if (t==&head) return false;

	PrioItem *prev=t->prev;
	prev->next=t->next;
	t->next->prev=prev;

	delete t;
	return true;
}


#endif
