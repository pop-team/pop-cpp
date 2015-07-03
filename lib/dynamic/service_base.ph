/**
 * File : paorc_service_base.ph
 * Author : Tuan Anh Nguyen
 * Description : Basic interfaces for the POP-C++ runtime services
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 */

#ifndef _POP_SERVICE_BASE_PH
#define _POP_SERVICE_BASE_PH

#include "pop_accesspoint.h"

typedef std::vector<pop_accesspoint> pop_accesspoint_list;

/**
 * @class pop_service_base
 * @brief Parclass : Base class for all POP-C++ runtime services, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 * pop_service_base implements two main methods to start and to stop the service.
 */
parclass pop_service_base=0 {
public:
    /** @brief  Constructor
     * @param challenge The challenge string will will be require on stoping the service
    */
    pop_service_base([in] const std::string &challenge);

    pop_service_base();

    /** @brief Start the service.
     * This method will make the object running even if there is no reference to the object.
    */
    seq sync virtual void Start();

    /** @brief Start the service.
     * This method will make the object running even if there is no reference to the object.
     * @param challenge
    */
    seq sync virtual void Start(const std::string &challenge);


    /** @brief Stop the service.
     * @param challenge The challenge string will be tested with the one previously provided through the constructor.
     * @return true if the service has been stopped successfully. Otherwise, false is returned.
    */
    seq sync virtual bool Stop([in] const std::string &challenge);

    __hidden virtual int AddRef();
    __hidden virtual int DecRef();
    __hidden virtual bool CanKill();

    classuid(0);

protected:
    std::string mychallenge;
    pop_accesspoint appservice;
    bool daemonMode;
};


/**
 * @class JobCoreService
 * @brief Parclass : Provide the POP-C++ application-runtime service interface for creating parallel object, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 * JobCoreService provides an abstraction for POP-C++ applications to access the POP-C++ job service for creating parallel objects
 */
parclass JobCoreService:
public pop_service_base {
public:

    /** @brief  Constructor
     * @param challenge The challenge string will will be require on stoping the service
    */
    JobCoreService([in] const std::string &challenge);

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
    sync conc virtual int CreateObject(pop_accesspoint &localservice, const std::string &objname, const pop_od &od, int howmany, [in, out,size=howmany] pop_accesspoint *jobcontacts, int howmany2, [in, out, size=howmany2] pop_accesspoint *remotejobcontacts)=0;

    sync conc virtual pop_accesspoint getPSMRef()=0;

    classuid(10);


};

#define RESERVE_TIMEOUT 120
#define ALLOC_TIMEOUT 60

#endif
