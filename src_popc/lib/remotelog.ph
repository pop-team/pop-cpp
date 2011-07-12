#ifndef REMOTELOG_H
#define REMOTELOG_H

#include "paroc_service_base.ph"

parclass RemoteLog: virtual public paroc_service_base
{
public:
	RemoteLog([in] const paroc_string &challenge) @{ host=paroc_system::GetHost(); };
	~RemoteLog();
	async seq void Log([in] const paroc_string &info);

	classuid(3);
};

#endif

