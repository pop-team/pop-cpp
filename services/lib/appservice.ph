/**
 * File : appservice.ph
 * Author : Tuan Anh Nguyen
 * Description : declaration of the application scope service
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 * clementval   2010/11/08  Add the generation of the POP Application Unique ID and Getter for this ID.
 */

#ifndef APPCORESERVICE_PH
#define APPCORESERVICE_PH

#include "codemgr.ph"
#include "remotelog.ph"
#include "objectmonitor.ph"
#include "batchmgr.ph"


struct ServiceEntry {
    std::string name;
    pop_service_base *service;
};

/**
 * @class AppCoreService
 * @brief Parclass : Application service interface, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 * The accesspoint of AppCoreService will be passed to the JobCoreService during the parallel object creation.
 * In addition, users can also register new service instances to AppCoreService.
 * This service is an agregation of three services: CodeMgr, RemoteLog and ObjectMonitor
 */
parclass AppCoreService:
public CodeMgr, public RemoteLog, public ObjectMonitor, public BatchMgr {
public:

    /**
     * @brief Constructor
     * @param challenge The challenge string will will be required on stoping the service
     * @param daemon start in daemon mode
     * @param codelocation location of the AppCoreService executable
    */
    AppCoreService(const std::string &challenge, bool daemon, const std::string & codelocation) @{ od.url(pop_system::GetHost()); od.executable(codelocation); od.runLocal(true); od.service(true);} ;
    ~AppCoreService();



    /**
     * ViSaG : clementval
     * Getter for the POP Application ID
     */
    sync conc std::string GetPOPCAppID();
    /* ViSaG */


    /*!@brief Query a user supplied service
     * @param name name of the service (string)
     * @param service the instance of the service of the given name is returned
     * @return true if the service of given name exists. Othewise, false is return
    */
    seq sync bool QueryService(const std::string &name, [out] pop_service_base &service);

    /*!@brief Query a user supplied service
     * @param name name of the service (string)
     * @param service the instance of the service of the given name is returned
     * @return true if the service of given name exists. Othewise, false is return
    */
    seq sync bool QueryService(const std::string &name, [out] pop_accesspoint &service);

    /*!@brief Register a new service to AppCoreService
     * @param name name of the service (string)
     * @param newservice the new service (parallel object)
     * @return true if successful. Otherwise, false is returned
    */
    seq sync bool RegisterService(const std::string &name, const pop_service_base &newservice);

    /*!@brief Unregister a service
     * @param name name of the service (string)
     * @return true if successful. Otherwise, false is returned
    */
    seq sync bool UnregisterService(const std::string &name);
    classuid(20);


private:
    std::vector<ServiceEntry> servicelist;
    void LoadAddOn();

    /**
     * ViSaG : clementval
     * Variable holding the POPAppID
     */
    std::string _popcAppId;


};


int popc_appservice_log(const char *format,...);


#endif

