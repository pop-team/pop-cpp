/**
 * File : virtual_jobmgr.ph
 * Author : Valentin Clement
 * Description : Declaration of the parallel object VirtualJobMgr (POP-C++ Global Services)
 * Creation date : 2010/11/12
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval	2010/11/12  
 */

#ifndef VIRTUAL_JOBMGR_PH
#define VIRTUAL_JOBMGR_PH


#include "jobmgr.ph"

#include "ESXWrapper.h"
#include "WrapperFactory.h"
#include "popvm.h"

#include <list>

#define ADVANCE_VM 2

/**
 * @author Valentin Clement
 * Declaration of the virtual version of the JobMgr. This version overwrite the methods that need to be different in a Virtual 
 * mode
 */
parclass VirtualJobMgr: public JobMgr
{

public:
   //Class Unique Identifier
   classuid(9999);

   //VirtualJobMgr constrcutor
	VirtualJobMgr(bool daemon, [in] const POPString &virtconf, [in] const POPString &conf, 
      [in] const POPString &challenge, const POPString &url, 
      const paroc_accesspoint &nodeAccess, const paroc_accesspoint &clonerRef, 
      const paroc_accesspoint &psmRef) @{ od.url(url); od.runLocal(true); od.service(true);};
   
   //VirtualJobMgr destructor
   ~VirtualJobMgr();

   //Check the VM availability
   sync seq bool checkVM(Request req);

   //Reserve for a Job on a VM
   sync conc virtual int Reserve(const paroc_od &od, float &inoutfitness, POPString popAppId, POPString reqID);

   //Cancel a reservation of a VM
	//seq async virtual void CancelReservation([in, size=howmany] int *req, int howmany);

   //Methods used to call the Update protected methods
  // void updateJobsReservation();

   //Called by the application services when the application is finished
   async conc void ApplicationEnd(POPString popAppId, bool initiator);

   sync seq void AddClone(POPvm clone, POPString original_name);

   sync conc paroc_accesspoint getPOPClonerRef();

protected:
   //Execute a parallel object on a worker VM
   virtual int Exec(char **arguments, char **env, int &pid, POPString popAppId, POPString reqID);

   //Prepare the VM for the execution
   virtual bool PrepareVM(char** argv, int* n, POPString popAppId, POPString reqID);

   

   VPopCWrapper* vWrapper;          //Pointer to the VM Wrapper
   int guestPort;                   //Port for the key exchange between the worker and the admin
   POPString localKey;              //Local PKI

   std::list<POPvm> vm_list;        //List containing all the worker VM information

   int maxvm;                       //Maximum of worker VM
   int vm_clone_base;               //Number of VM to clone at first startup (0 disable startup cloning, -1 automatic cloning)
   int vm_last_number;              //Number of the last VM in the config file. Used to name the clone VM
   POPString vm_prefix;             //Prefix for display name of the cloned VM
   paroc_accesspoint vm_clonerRef;  //Access Point to the POPCloner object


};
int paroc_service_log(const char *format,...);
int popc_node_log(const char *format,...);

#endif

