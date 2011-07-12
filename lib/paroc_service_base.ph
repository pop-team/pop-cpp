#ifndef _PAROC_SERVICE_BASE_PH
#define _PAROC_SERVICE_BASE_PH

#include "paroc_accesspoint.h"
#include "paroc_list.h"
typedef paroc_list<paroc_accesspoint> paroc_accesspoint_list;

parclass paroc_service_base
{
public:
	paroc_service_base([in] const paroc_string &challenge);

	paroc_service_base();

	seq sync virtual void Start();
	seq sync virtual bool Stop([in] const paroc_string &challenge);

	__hidden virtual int AddRef();
	__hidden virtual int DecRef();
	__hidden virtual bool CanKill();

	classuid(0);

private:
	paroc_string mychallenge;
	bool daemonMode;
};

int paroc_service_log(const char *format,...);

#endif
