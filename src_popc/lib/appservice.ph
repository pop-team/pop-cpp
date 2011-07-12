#ifndef APPCORESERVICE_PH
#define APPCORESERVICE_PH

#include "codemgr.ph"
#include "remotelog.ph"
#include "objectmonitor.ph"

parclass AppCoreService: public CodeMgr, public RemoteLog, public ObjectMonitor
{
public:
	AppCoreService(const paroc_string &challenge, bool daemon, const paroc_string & codelocation) @{ od.url(paroc_system::GetHost()); od.executable(codelocation);};
	~AppCoreService();
	seq sync bool QueryService([in] const paroc_string &name);

	seq sync bool QueryService(const paroc_string &name, [out] paroc_service_base &service);
	seq sync bool QueryService(const paroc_string &name, [out] paroc_accesspoint &service);
	seq sync bool RegisterService(const paroc_string &name, const paroc_service_base &newservice);

	classuid(20);

};

#endif

