#ifndef _PAROC_PROXY_H
#define _PAROC_PROXY_H

#include <strings.h>
#include <stdio.h>

#include "socketpair.h"
#include "paroc_accesspoint.h"

#include "paroc_service_base.ph"


//checkpoint in millisecond
#define PROXY_CHECKPOINT 10*1000

/*
Environment variables used by Proxy:
- PAROC_PROXY_NETMASK
- PAROC_PROXY_PORTS xxx:yyy the port range from xxx to yyy
*/

parclass Proxy: public paroc_service_base
{
public:
  Proxy([in] char challenge[256], int port) @{ host=paroc_utils::MakeContact(paroc_system::GetHost(), port); };
  ~Proxy();
	
  seq bool CreateDelegate([in] paroc_accesspoint &object, [out] paroc_accesspoint &delegate);
  
  classuid(100);
	
protected:

  bool HandleProxy(paroc_combox &delegate, paroc_accesspoint &object);
  bool ShouldProxy(paroc_combox *inf, int obj_ip);


  int startport;
  int endport;	

  int  netmask;

  paroc_accesspoint parent;
  CSocketPairFactory fact;  

};


#endif
