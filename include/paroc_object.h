/**
 * File : paroc_object.ph
 * Author : Tuan Anh Nguyen
 * Description : base class for parallel object implementation
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval	2011/01/17	Add COUT support
 */

#ifndef _POPC_OBJECTBASE_H
#define _POPC_OBJECTBASE_H

#include "paroc_accesspoint.h"
#include "paroc_event.h"

//Added by clementval
#include <iostream>
#include <sstream>

#define cout paroc_system::_popc_cout.str(""); \
             paroc_system::_popc_cout 
#define popcendl std::endl; \
             rprintf(paroc_system::_popc_cout.str().c_str())
//End of add

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

   //Added by clementval
   //std::ostringstream _popc_cout;
   //End of add
};

#endif
