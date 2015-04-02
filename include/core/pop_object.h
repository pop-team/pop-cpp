/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief base class for parallel object implementation
 *
 * UPDATES :
 * Authors      Date              Comment
 * clementval   2011/01/17  Add COUT support
 * clementval 2011/9/13   Add the method GetAccessPointForThis() to be able to handle the THIS keyword correctly
 *
 */

#ifndef _POP_OBJECTBASE_H
#define _POP_OBJECTBASE_H

#include "pop_accesspoint.h"
#include "pop_event.h"

//Added by clementval
#include <iostream>
#include <sstream>

// TODO LW: This creates a bug in case the user does a for(...) cout ... without {} 
#define cout pop_system::_popc_cout.str(""); \
             pop_system::_popc_cout
#define popcendl std::endl; \
             rprintf(pop_system::_popc_cout.str().c_str())
//End of add

/**
 * @class pop_object
 * @brief Base class for parallel object implementation, used by POP-C++ runtime.
 *
 * @author Tuan Anh Nguyen
 */
class pop_object {
public:
    pop_object();
    virtual ~pop_object();

    int GetRefCount();

    virtual int AddRef();
    virtual int DecRef();
    virtual bool CanKill();

    const pop_accesspoint & GetAccessPoint() const;

    //Get the access point and set the variable _noaddref to TRUE in this access point
    const pop_accesspoint & GetAccessPointForThis();

    virtual int eventwait(int event=ANY_EVENT, int timeout=-1); //timeout in milliseconds
    virtual void eventraise(int event);

    static int argc;
    static char **argv;

private:
    int refcount;
    pop_mutex lock;
    EventQueue _pop_events;

protected:
    pop_mutex _pop_omutex;
    //Added by clementval
    //std::ostringstream _popc_cout;
    //End of add
};

#endif
