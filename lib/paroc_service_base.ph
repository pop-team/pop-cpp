/**
 * File : paorc_service_base.ph
 * Author : Tuan Anh Nguyen
 * Description : Basic interfaces for the POP-C++ runtime services
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 */

#ifndef _POPC_SERVICE_BASE_PH
#define _POPC_SERVICE_BASE_PH

#include "paroc_accesspoint.h"
#include "paroc_list.h"
typedef paroc_list<paroc_accesspoint> paroc_accesspoint_list;

/**
 * @class paroc_service_base
 * @brief Parclass : Base class for all POP-C++ runtime services, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 * paroc_service_base implements two main methods to start and to stop the service.
 */
parclass paroc_service_base=0
{
public:
	/** @brief  Constructor
	 * @param challenge The challenge string will will be require on stoping the service
	*/
	paroc_service_base([in] const paroc_string &challenge);

	paroc_service_base();

	/** @brief Start the service.
	 * This method will make the object running even if there is no reference to the object.
	*/
	seq sync virtual void Start();

	/** @brief Start the service.
	 * This method will make the object running even if there is no reference to the object.
	 * @param challenge
	*/
	seq sync virtual void Start(const paroc_string &challenge);


	/** @brief Stop the service.
	 * @param challenge The challenge string will be tested with the one previously provided through the constructor.
	 * @return true if the service has been stopped successfully. Otherwise, false is returned.
	*/
	seq sync virtual bool Stop([in] const paroc_string &challenge);

	__hidden virtual int AddRef();
	__hidden virtual int DecRef();
	__hidden virtual bool CanKill();

	classuid(0);

protected:
	paroc_string mychallenge;
	paroc_accesspoint appservice;
	bool daemonMode;
};


/**
 * @class JobCoreService
 * @brief Parclass : Provide the POP-C++ application-runtime service interface for creating parallel object, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 * JobCoreService provides an abstraction for POP-C++ applications to accesss the POP-C++ job service for creating parallel objects
 */
parclass JobCoreService: public paroc_service_base
{
public:

	/** @brief  Constructor
	 * @param challenge The challenge string will will be require on stoping the service
	*/
	JobCoreService([in] const paroc_string &challenge);

	/** @brief Perform resource discovery and create the parallel object on the remote resource.
	 * @param localservice the application scope service access point. This accesspoint will be used to connect to the CodeMgr to check for supported platform and executable URL
	 * @param objname name of the parallel object.
	 * @param od the object description (resource requirements).
	 * @param howmany number of parallel objects to be created.
	 * @param objcontacts if successfully created, the object's accesspoints will be stored in this parameter
    * @param howmany2            Size of the remotejobcontact array
    * @param remotejobcontacts   Store the job contact of the JobMgr which has created the object
	 * @return 0 (successful) or error code otherwise.
	*/
	sync conc virtual int CreateObject(paroc_accesspoint &localservice, const paroc_string &objname, const paroc_od &od, int howmany, [in, out,size=howmany] paroc_accesspoint *jobcontacts, int howmany2, [in, out, size=howmany2] paroc_accesspoint *remotejobcontacts)=0;

   sync conc virtual paroc_accesspoint getPSMRef()=0;

	classuid(10);


};

#define RESERVE_TIMEOUT 120
#define ALLOC_TIMEOUT 60

#endif
