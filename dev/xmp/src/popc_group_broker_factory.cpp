/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/11/30
 * @brief Declaration of a base
 *
 *
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "popc_group_broker_factory.h"
#include "pop_utils.h"
#include "pop_system.h"


popc_broker_map* POPC_GroupBrokerFactory::_internal_broker_map = NULL;
ispackedfunc POPC_GroupBrokerFactory::check_if_packed = NULL;

/**
 * Create a broker factory
 * @param Function to be called to create a broker
 * @param Name associated with the broker factory
 */
POPC_GroupBrokerFactory::POPC_GroupBrokerFactory(initbrokerfunc_group func, const char *name) {
    if(_internal_broker_map == NULL) {
        _internal_broker_map = new popc_broker_map();
    }

    if(name == NULL || func == NULL) {
        return;
    }

    std::string broker_name(name);
    (*_internal_broker_map)[broker_name] = func;
}

/**
 * Create a broker of the given name
 * @param objname Name of the class of which the object will be instantiated
 * @return A pointer to the created broker
 */
POPC_GroupBroker* POPC_GroupBrokerFactory::create(const char *objname) {
    if((*_internal_broker_map).empty() || objname == NULL) {
        return NULL;
    }

    std::string object_name(objname);
    return (*_internal_broker_map)[object_name]();
}

/**
 * List all the broker factory available.
 * @param objlist Output parameter containing the list of all broker factory available.
 */
void POPC_GroupBrokerFactory::list_all(popc_list_string &objlist) {
    if((*_internal_broker_map).empty()) {
        return;
    }

    popc_broker_map::iterator it;

    for(it = (*_internal_broker_map).begin() ; it != (*_internal_broker_map).end(); it++) {
        std::string &str = objlist.AddTailNew();
        str = ((*it).first).c_str();
    }
}

/**
 * Test if a given class can be created by an available broker factory.
 * @param objname Name of the class to be tested
 * @return TRUE if there is a broker factory for this class. FALSE in any other cases.
 */
bool POPC_GroupBrokerFactory::test(const char *objname) {
    if((*_internal_broker_map).empty()) {
        return false;
    }

    std::string objectname(objname);
    if((*_internal_broker_map)[objectname] != NULL) {
        return true;
    }

    return false;
}
