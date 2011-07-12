#ifndef POPC_OBJECT_MONITOR_PH
#define POPC_OBJECT_MONITOR_PH

#include "paroc_service_base.ph"


/**
 * @class ObjectMonitor
 * @brief Monitor parallel object life-time, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 * ObjectMonitor is an application-scope service which manages parallel objects within the application
 */
parclass ObjectMonitor: virtual public paroc_service_base
{
public:

	/** @brief Constructor
	 * @param challenge challenge string which will be required on stopping the service
	*/
	ObjectMonitor([in] const paroc_string &challenge) @{od.runLocal(true);};
	~ObjectMonitor();

	/** @brief Kill all parallel objects.
	 * This method is automatically called upon abnormal termination of the main program.
	*/
	async conc virtual void KillAll();

	/** @brief Register the object accesspoint with the ObjectMonitor
	 * @param p the object access point
	 * This method is called automatically upon creating a parallel object
	*/

	async seq virtual void ManageObject([in] paroc_accesspoint &p);

	/** @brief Unregister the object accesspoint with the ObjectMonitor
	 * @param p the object access point
	 * This method is called automatically upon destroying the parallel object
	*/
	async seq virtual void UnManageObject([in] paroc_accesspoint &p);


	/** @brief  check number of running parallel objects
	 * @return number of parallel objects alive
	*/
	sync conc virtual int CheckObjects();

	classuid(4);
protected:
	paroc_accesspoint_list objects;
	bool isActive;
};

#endif

//[in, proc=marshalstring]
