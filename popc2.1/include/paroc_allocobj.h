#ifndef POPC_ALLOCOBJ_H
#define POPC_ALLOCOBJ_H
#include <paroc_mutex.h>

/**
 * @class paroc_message_header
 * @author Tuan Anh Nguyen
 * @brief Implementation of the batch creation mechanism of parallel objects, used by POP-C++ runtime
 * Note : This class does not seem to be used so far
 */
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
