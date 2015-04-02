/**
 * File : objectmonitor.ph
 * Author : Tuan Anh Nguyen
 * Description : Declaration of the object monitor service
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 */

#ifndef POP_OBJECT_MONITOR_PH
#define POP_OBJECT_MONITOR_PH

#include "pop_service_base.ph"


/**
 * @class ObjectMonitor
 * @brief Monitor parallel object life-time, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 * ObjectMonitor is an application-scope service which manages parallel objects within the application
 */
parclass ObjectMonitor:
virtual public pop_service_base {
public:

    /** @brief Constructor
     * @param challenge challenge string which will be required on stopping the service
    */
    ObjectMonitor([in] const std::string &challenge) @{od.runLocal(true); od.service(true); };
    ~ObjectMonitor();

    /** @brief Kill all parallel objects.
     * This method is automatically called upon abnormal termination of the main program.
    */
    async conc virtual void KillAll();

    /** @brief Register the object accesspoint with the ObjectMonitor
     * @param p the object access point
     * This method is called automatically upon creating a parallel object
    */

    async seq virtual void ManageObject([in] pop_accesspoint &p);

    /** @brief Unregister the object accesspoint with the ObjectMonitor
     * @param p the object access point
     * This method is called automatically upon destroying the parallel object
    */
    async seq virtual void UnManageObject([in] pop_accesspoint &p);


    /** @brief  check number of running parallel objects
     * @return number of parallel objects alive
    */
    sync conc virtual int CheckObjects(bool pingObjects);

    classuid(4);
protected:
    pop_accesspoint_list objects;
    bool isActive;
};

#endif
