#ifndef PAROC_OBJECT_MONITOR_PH
#define PAROC_OBJECT_MONITOR_PH

#include "paroc_service_base.ph"

parclass ObjectMonitor: virtual public paroc_service_base
{
public:
	ObjectMonitor([in] const paroc_string &challenge);
	~ObjectMonitor();
	async conc virtual void KillAll();

	async seq virtual void ManageObject([in] paroc_accesspoint &p);
	async seq virtual void UnManageObject([in] paroc_accesspoint &p);

	sync conc virtual int CheckObjects();

	classuid(4);
protected:
	paroc_accesspoint_list objects;
};

#endif

//[in, proc=marshalstring] 
