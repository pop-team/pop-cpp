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
 
#include "paroc_accesspoint.h"
#include "paroc_combox.h"
#include "paroc_buffer.h" 
#include "paroc_list.h"
#include "popc_object.h"


#ifndef POPC_GROUP_BROKER_H_
#define POPC_GROUP_BROKER_H_


#define INVOKE_SYNC 1
#define INVOKE_ASYNC 2
#define INVOKE_CONSTRUCTOR 4
#define INVOKE_CONC 8
#define INVOKE_MUTEX 16



struct popc_request
{
	paroc_connection *from;
	unsigned methodId[3];
	paroc_buffer *data;
	void *userdata;
	void operator = (const popc_request& r);
	popc_request();
	popc_request(const popc_request& r);
};

struct popc_method_info
{
	unsigned mid;
	char *name;
};

struct popc_class_info
{
	unsigned cid;
	popc_method_info *methods;
	int sz;
};

typedef paroc_list<popc_class_info> popc_method_map_list;

class POPC_GroupBroker {
public:
  POPC_GroupBroker();
  virtual ~POPC_GroupBroker();
  
  
  void add_method_info(unsigned classuid, popc_method_info *methods, int sz);  
	virtual bool invoke(unsigned method[3], paroc_buffer &buf, paroc_connection *peer);  
	
	static paroc_accesspoint accesspoint;	
	
protected: 

  POPC_Object* _popc_internal_object;
	popc_method_map_list methodnames;
};

#endif /* POPC_GROUP_BROKER_H_ */