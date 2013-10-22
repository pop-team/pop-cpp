/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of the batch creation mechanism of parallel objects, used by POP-C++ runtime
 *
 */

#ifndef POPC_ALLOCOBJ_H
#define POPC_ALLOCOBJ_H
#include <paroc_mutex.h>

class paroc_allocobj
{
public:
	paroc_allocobj(int count);
	~paroc_allocobj();
	void release();

private:
	bool holding;
	static paroc_mutex lock;
};

template<class T> T * pnew(int np)
{
	paroc_allocobj t(np);
	return new T[np];
}


#endif
