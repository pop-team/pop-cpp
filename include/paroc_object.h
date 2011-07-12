/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: base class for parallel object implementation
 */

#ifndef _POPC_OBJECTBASE_H
#define _POPC_OBJECTBASE_H

#include "paroc_accesspoint.h"
#include "paroc_event.h"

/**
 * @class paroc_object
 * @brief Base class for parallel object implementation, used by POP-C++ runtime.
 *
 * @author Tuan Anh Nguyen
 */
class paroc_object
{
public:
	paroc_object();
	virtual ~paroc_object();

	int GetRefCount();

	virtual int AddRef();
	virtual int DecRef();
	virtual bool CanKill();

	const paroc_accesspoint & GetAccessPoint() const;

	virtual int eventwait(int event=ANY_EVENT, int timeout=-1); //timeout in milliseconds
	virtual void eventraise(int event);

	static int argc;
	static char **argv;
private:
	int refcount;
	paroc_mutex lock;
	EventQueue _paroc_events;
protected:
	paroc_mutex _paroc_omutex;

};

#endif
