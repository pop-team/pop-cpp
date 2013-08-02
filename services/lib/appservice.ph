/**
 * File : appservice.ph
 * Author : Tuan Anh Nguyen
 * Description : declaration of the application scope service
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval	2010/11/08	Add the generation of the POP Application Unique ID and Getter for this ID.
 */

#ifndef APPCORESERVICE_PH
#define APPCORESERVICE_PH

#include "codemgr.ph"
#include "remotelog.ph"
#include "objectmonitor.ph"
#include "batchmgr.ph"


struct ServiceEntry
{
	char *name;
	paroc_service_base *service;
};

typedef paroc_list<ServiceEntry> paroc_list_service;


/**
 * @class AppCoreService
 * @brief Parclass : Application service interface, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 * The accesspoint of AppCoreService will be passed to the JobCoreService during the parallel object creation.
 * In addition, users can also register new service instances to AppCoreService.
 * This service is an agregation of three services: CodeMgr, RemoteLog and ObjectMonitor
 */
parclass AppCoreService: public CodeMgr, public RemoteLog, public ObjectMonitor, public BatchMgr
{
public:

	/**
	 * @brief Constructor
	 * @param challenge The challenge string will will be required on stoping the service
	 * @param daemon start in daemon mode
	 * @param codelocation location of the AppCoreService executable
	*/
	AppCoreService(const POPString &challenge, bool daemon, const POPString & codelocation) @{ od.url(paroc_system::GetHost()); od.executable(codelocation); od.runLocal(true); od.service(true);} ;
	~AppCoreService();



   /**
    * ViSaG : clementval
    * Getter for the POP Application ID
    */
   sync conc POPString GetPOPCAppID();
   /* ViSaG */


	/*!@brief Query a user supplied service
	 * @param name name of the service (string)
	 * @param service the instance of the service of the given name is returned
	 * @return true if the service of given name exists. Othewise, false is return
	*/
	seq sync bool QueryService(const POPString &name, [out] paroc_service_base &service);

	/*!@brief Query a user supplied service
	 * @param name name of the service (string)
	 * @param service the instance of the service of the given name is returned
	 * @return true if the service of given name exists. Othewise, false is return
	*/
	seq sync bool QueryService(const POPString &name, [out] paroc_accesspoint &service);

	/*!@brief Register a new service to AppCoreService
	 * @param name name of the service (string)
	 * @param newservice the new service (parallel object)
	 * @return true if successful. Otherwise, false is returned
	*/
	seq sync bool RegisterService(const POPString &name, const paroc_service_base &newservice);

	/*!@brief Unregister a service
	 * @param name name of the service (string)
	 * @return true if successful. Otherwise, false is returned
	*/
	seq sync bool UnregisterService(const POPString &name);
	classuid(20);


private:
	paroc_list_service servicelist;
	void LoadAddOn();

   /** 
    * ViSaG : clementval
    * Variable holding the POPAppID
    */
   POPString _popcAppId;


};


int popc_appservice_log(const char *format,...);


#endif

