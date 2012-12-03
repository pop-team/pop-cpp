/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/11/30
 * @brief 
 *
 *
 */
 
#include "popc_group_broker.h"
 
 
POPC_GroupBroker::POPC_GroupBroker() 
{
 
}
 
POPC_GroupBroker::~POPC_GroupBroker()
{

}



void POPC_GroupBroker::add_method_info(unsigned classuid, popc_method_info *methods, int sz)
{
	if (sz <= 0 || methods == NULL) return;
	popc_class_info &t = methodnames.AddHeadNew();
	t.cid = classuid;
	t.methods = methods;
	t.sz = sz;
}


bool POPC_GroupBroker::invoke(unsigned method[3], paroc_buffer &buf, paroc_connection *peer)
{

}