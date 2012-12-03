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
#include "paroc_utils.h"
#include "paroc_system.h"


popc_broker_map* POPC_GroupBrokerFactory::_internal_broker_map = NULL;
ispackedfunc POPC_GroupBrokerFactory::check_if_packed = NULL;

/**
 *
 */
POPC_GroupBrokerFactory::POPC_GroupBrokerFactory(initbrokerfunc func, const char *name)
{ 
  if(_internal_broker_map == NULL) {
    _internal_broker_map = new popc_broker_map();
  }


	if (name == NULL || func == NULL) {
	  return;
	}
 
  std::string broker_name(name); 
	(*_internal_broker_map)[broker_name] = func; 
}

/**
 *
 */
POPC_GroupBroker* POPC_GroupBrokerFactory::create(const char *objname)
{
  if((*_internal_broker_map).empty() || objname == NULL) {
    return NULL;
  }
  
  std::string object_name(objname);
  return (*_internal_broker_map)[object_name]();
}

/**
 *
 */
void POPC_GroupBrokerFactory::list_all(popc_list_string &objlist)
{
  if((*_internal_broker_map).empty()) {
    return;
  }
  
  popc_broker_map::iterator it; 
  
  for ( it = (*_internal_broker_map).begin() ; it != (*_internal_broker_map).end(); it++ ) {
 		POPString &str = objlist.AddTailNew();
    str = ((*it).first).c_str();
  }
}

/**
 *
 */
bool POPC_GroupBrokerFactory::test(const char *objname)
{
 if((*_internal_broker_map).empty()) {
    return false;
  }
  
  std::string objectname(objname); 
  if((*_internal_broker_map)[objectname] != NULL) {
    return true; 
  }
  
  return false; 
}
