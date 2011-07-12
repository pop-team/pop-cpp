/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: implementation of the memory management
 */

#include <stdio.h>
#include <stdlib.h>

#include "paroc_memspool.h"
#include "paroc_exception.h"

paroc_memspool::paroc_memspool()
{
}

paroc_memspool::~paroc_memspool()
{
	Free();
}

VOIDPTR paroc_memspool::Alloc(int sz)
{
	if (sz<=0) return NULL;

	VOIDPTR data;
	if ((data=malloc(sz))==NULL) paroc_exception::paroc_throw(errno);
	memtemp.AddTail(data);
	return data;
}

void paroc_memspool::Managed(VOIDPTR data)
{
	if (data!=NULL) memtemp.AddTail(data);
}

void paroc_memspool::Free()
{
	POSITION pos=memtemp.GetHeadPosition();
	while (pos!=NULL)
	{
		VOIDPTR tmp=memtemp.GetNext(pos);
		free(tmp);
	}
	memtemp.RemoveAll();
}


