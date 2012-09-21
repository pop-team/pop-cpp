/**
 * File : virtual_secure_jobmgr.cc
 * Author : Valentin Clement
 * Description :  Implementation of the parallel object VirtSecureJobMgr (POP-C++ Global Services). This object inherits from 
 *                VirtualJobMgr
 * Creation date : 2010/12/09
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval	2010/12/09	Creation of this file for the ViSaG project
 */

#include "virtual_secure_jobmgr.ph"
#include "virtual_popc_security_manager.ph"
#include "codemgr.ph"
#include "appservice.ph"
#include <timer.h>
/**
 * ViSaG : clementval
 * Constructor of the Virtual Secure JobMgr
 * @param daemon
 * @param virtconf   Path of the virtual configuration file
 * @param conf       Path of the JobMgr configuration file
 * @param challenge  Challenge string to shutdown the service
 * @param url
 * @param nodeAccess Access point of the local PSN
 * @param clonerRef  Access point of the local POPCloner
 * @param psmRef     Access point of the local PSM
 */
VirtSecureJobMgr::VirtSecureJobMgr(bool daemon, const POPString &virtconf, const POPString &conf, const POPString &challenge, 
   const POPString &url, const paroc_accesspoint &nodeAccess, const paroc_accesspoint &clonerRef, 
   const paroc_accesspoint &psmRef) : VirtualJobMgr(daemon, virtconf, conf, challenge, url, nodeAccess, clonerRef, psmRef) {
   
   //Get the local PKI and save it on a global variable
   VirtualPOPCSecurityManager psm(psmRef);
   _localPublicKey = psm.getLocalPKI();


}

/**
 * ViSaG : clementval
 * Virtual Secure JobMgr destructor
 */
VirtSecureJobMgr::~VirtSecureJobMgr(){}







/* ############################################# 
 * ##### VirtualJobMgr overwritten methods #####
 * ############################################# */

/** 
 * ViSaG : clementval
 * Allocate resource for a job
 * @param localservice  Access point of the local services
 * @param objname       Name of the object to allocate resource for
 * @param od            Object description for this object
 * @param howmany       Number of object to be created
 * @param fitness
 * @param jobcontact    Access point of the POP-C++ global services
 * @param reserveIDs    Result array of the reserved IDs
 * @param requestInfo
 * @param iptrace
 * @param tracesize
 * @return 
 */
bool VirtSecureJobMgr::AllocResource(const paroc_accesspoint &localservice, const POPString &objname, const paroc_od &od, int howmany, float *fitness, paroc_accesspoint *jobcontacts, int *reserveIDs, int requestInfo[3], int iptrace[MAX_HOPS], int tracesize)
{
	bool ret=false;
	if(!od.isSearchSet()){
		if (howmany<1) return false;
		
		if (!AddRequest(requestInfo))
		{
			paroc_service_log("Local resource has already been traversed!");
			return false;
		}
		POPString codefile;
	
		//MATCHING LOCALLY
		popc_node_log("Resource discovery request: obj=%s, local service: %s (trace=%d)",(const char *)objname,localservice.GetAccessString(),tracesize);
		try
		{
			if (CheckPauseList(localservice))
			{
				popc_node_log("Local resource matching is temporary paused due to previous errors!");
			}
			else if (MatchUser(localservice))
			{
	
				CodeMgr codemgr(localservice);
				if (codemgr.QueryCode(objname,paroc_system::platform,codefile))
				{
					if (MatchAndReserve(od,fitness,jobcontacts,reserveIDs, howmany)) ret=true;
				}
			}
		}
		catch (...)
		{
			popc_node_log("Exception on resource discovery");
			return false;
		}
		if (ret)
		{
			bool allok=true;
			for (int i=0;i<howmany && allok;i++) if (fitness[i]<1) allok=false;
			if (allok) return true;
		}
	
		if (tracesize<0 || tracesize>=MAX_HOPS)
		{
			popc_node_log("Stop forwarding due to trace size (value=%d)", tracesize);
			return ret;
		}
		AddTrace(iptrace, tracesize);
	}

	//Creation of a request to find the appropriate resources on the grid 
	
	//Create an interface to communicate with the local POPCSearchNode
	POPCSearchNode localPSN(_localPSN);
	//Create the request of resource discovery
	Request r;
	//Set the request's node identifier
	r.setNodeId(localPSN.getPOPCSearchNodeId());
	//Recover the od Max depth or env var POPC_SEARCHMAXHOP. If both are not set, MAXHOP constant is defined in JobMgr.ph
	int maxhopint=0;
   //popc_node_log("OD_SEARCH : depth=%d, size=%d, time=%d", od.getSearchMaxDepth(), od.getSearchMaxReqSize(), od.getSearchWaitTime());
	if((maxhopint=od.getSearchMaxDepth()) > 0){
		r.setMaxHops(maxhopint);
		//popc_node_log("JobMgr : Max hop set via OD : %d", maxhopint);
	} else {
		//Recover the max Hop env variable
		char *maxhop;
		if((maxhop=getenv("POPC_SEARCHMAXHOP"))){
			maxhopint = atoi(maxhop);
			//popc_node_log("JobMgr : Max hop set via ENV Variable : %d", maxhopint);
		} else {
			maxhopint = MAXHOP;
			//popc_node_log("JobMgr : Max hop env variable is not set. Default value %d will be used", maxhopint);
		}
	}
	//Setting the value of max hop in the request
	r.setMaxHops(maxhopint);
	
	//Recover the maximum size of the request. This is not implemented yet
	int maxsizeint;
	if((maxsizeint = od.getSearchMaxReqSize()) > 0){
		//popc_node_log("JobMgr : Request max size set via OD : %d", maxsizeint);
		//To be implemented
	}
	//Recover the od waiting time or env var POPC_SEARCHTIMEOUT. If both are not set, TIMEOUT constant is defined in JobMgr.ph
	int timeoutint = 0;
	if((timeoutint = od.getSearchWaitTime()) >= 0){
		//popc_node_log("JobMgr : Timeout set via OD : %d", timeoutint);
	} else {
		//Recover the timeout in the POPC_SEARCHTIMEOUT env variable
		char *timeout;
		if((timeout=getenv("POPC_SEARCHTIMEOUT"))){
			timeoutint = atoi(timeout);
			//popc_node_log("JobMgr : Timeout set via ENV Variable : %d", timeoutint);
		}else {
			timeoutint = TIMEOUT;
			//popc_node_log("JobMgr : Timeout env variable is not set. Default value %d will be used", timeoutint);
		}
	}	
	//Set operating system
	POPString r_arch;
	od.getArch(r_arch);
	if(r_arch != NULL)
		r.setOperatingSystem(r_arch);
	//Set min and expected mem
	float r_minMem, r_expMem;
	od.getMemory(r_minMem, r_expMem);
	if(r_minMem > 0)
		r.setMinMemorySize(r_minMem);
	if(r_expMem > 0)
		r.setExpectedMemorySize(r_expMem);
	//Set min and expected bandwidth
	float r_minB, r_expB;
	od.getBandwidth(r_expB, r_minB);
	if(r_minB > 0)
		r.setMinNetworkBandwidth(r_minB);
	if(r_expB > 0)	
		r.setExpectedNetworkBandwidth(r_expB);      
	//Set min and expected power
	float r_minPower, r_expPower;
	od.getPower(r_expPower, r_minPower);
	if(r_minPower > 0)
		r.setMinPower(r_minPower);
	if(r_expPower > 0)
		r.setExpectedPower(r_expPower);


   AppCoreService appservice(localservice);
   POPString popAppId = appservice.GetPOPCAppID();
   r.setPOPAppId(appservice.GetPOPCAppID());
   //Set the PKI in the 
   
   POPString vmPKI;
   bool vmFound=false;
   //Get the PKI of the VM
   std::list<POPvm>::iterator it;
   for(it=vm_list.begin(); it != vm_list.end(); it++){
      if(strcmp((*it).getReservedPOPAppId().GetString(), popAppId.GetString()) == 0){
         popc_node_log("VM PKI found");
         vmPKI = (*it).getPKI();
         vmFound = true;
         break;
      }   
   }
   if(vmFound){
      popc_node_log("Set the VM pki: %s", vmPKI.GetString());
      
      r.setPKI(vmPKI);
   } else {
      //Set the double PKI in the 
      r.setPKI(_localPublicKey);
   }

   POPString reqID = localPSN.getUID();
   r.setUniqueId(reqID);
   

	//Launch the discovery and recover the responses	
	POPCSearchNodeInfos responses = localPSN.launchDiscovery(r, timeoutint);
	//Check if there is any responses
	if(responses.getNodeInfos().size() == 0){
      popc_node_log("[VSJM]ERROR: NO RESOURCES FOUND");
		paroc_exception::paroc_throw("No ressource found for execution");
	}
	// Distribute object creation request on responses
	list<POPCSearchNodeInfo> nodes;
	nodes = responses.getNodeInfos();
	list<POPCSearchNodeInfo>::iterator ni;
	int jobindex = 0;
	int n_response = responses.getNodeInfos().size();
	int failedReservation=0;
	ni = nodes.begin();
	for(jobindex = 0; jobindex < howmany; jobindex++){
		paroc_accesspoint n_ac;
		n_ac.SetAccessString(ni->nodeId);
		//Contact the POPSearchNode
      POPCSearchNode n(n_ac);				
		paroc_accesspoint jm_ap = n.getJobMgrRef();
		//Contact the JobMgr
		JobMgr jobmgr(jm_ap);	
		float t=0;
		//Try to reserve on remote JobMgr 
		reserveIDs[jobindex] = jobmgr.Reserve(od, t, popAppId, reqID);	
		//if reserve ID is egal to 0, the reservation process failed. If we can't reserver on any responding machine, we trow an exception
		if(reserveIDs[jobindex] == 0){
			jobindex--;
			failedReservation++;
			if(failedReservation==n_response)
				return false;
		} else {
			//setting the remote JobMgr info to execute the parallel object
			jobcontacts[jobindex].SetAccessString(jm_ap.GetAccessString());
         POPString pki(ni->getPKI());
         VirtualPOPCSecurityManager psm(_localPSM);
         POPString emptyPOPAppID;
         psm.writePKI(emptyPOPAppID, pki); //TODO write to the good VM
			//Setting the fitness
			fitness[jobindex] = t;
		}
		ni++;
		//Back to the beginning if we are at the end of the list
		if(ni == nodes.end())
			ni = nodes.begin();
		ret = true;
	}
	//End of add
   popc_node_log("Return from allocresource %s", (ret)?"true":"false");
	return ret;
}




/**
 * ViSaG : wyssen, clementval
 * This method prepares the worker guest and adds the ssh command to start the object
 * to the argv array which is then executed.
 * @param argv Pointer to the arguments
 * @param n    Pointer to the local counter variable for moving inside the arguments array
 * @return     True if the worker guest could be prepared, false if there was a problem.
 */
bool VirtSecureJobMgr::PrepareVM(char** argv, int* n, POPString popAppId, POPString reqID)
{
   string workerState;
   string workerIp;
   bool hasBeenReverted=false;

   //Retrieve the VM reserved for this job
   POPvm *reservedVM;
   std::list<POPvm>::iterator it;
   for(it=vm_list.begin(); it != vm_list.end(); it++){
      if(strcmp((*it).getReservedPOPAppId().GetString(), popAppId.GetString()) == 0){
         popc_node_log("[VSJM] VM_RETRIEVED:%s", (*it).getName().GetString());
         reservedVM = &(*it);               
         break;
      }   
   }

   //If machine is not running, revert to the clean snapshot.
   if(vWrapper->_popc_domainState((*reservedVM), &workerState) < 0){
      popc_node_log("[VSJM] VIRTUAL: Failed to get state of VM.");
      return false;
   }

   if(workerState.compare("running") != 0){
      string snapshotName((*reservedVM).getSnapshotName().GetString());
      if(vWrapper->_popc_domainRevertToSnapshot((*reservedVM), snapshotName) < 0){
         popc_node_log("[VSJM] VIRTUAL: Could not revert to the snapshot.");
         return false;
      }
      hasBeenReverted=true;
   } else {
      popc_node_log("[VSJM] VIRTUAL: Machine runs already.");
      hasBeenReverted=false;
   }
   
   //Get the IP address of the worker guest
   if(vWrapper->_popc_domainGetIpAddress((*reservedVM)) < 0)
      return false;

   if(reservedVM->getIPAddress().Length() <= 0){
      popc_node_log("[VSJM] VIRTUAL: IP address could not be retrived");
      return false;
   }

   workerIp.append(reservedVM->getIPAddress().GetString());

   //Get local public key 
   if(!(reservedVM->hasPKI())){
      if(vWrapper->_popc_getLocalPublicKey((*reservedVM)) < 0){
         popc_node_log("[VSJM] VIRTUAL: Cannot get the VM public key");
         return false;
      }
   }
   popc_node_log("[VSJM] VIRTUAL: VM PKI is %s", (*reservedVM).getPKI().GetString());

   //Send VM PKI to the main Node
   VirtualPOPCSecurityManager vpsm(_localPSM);
   //Write the PKI on the local PSM
   POPString emptyPOPAppID;
   vpsm.writePKI(emptyPOPAppID, (*reservedVM).getPKI());
   //Write the PKI on the Main Node
   vpsm.reroutePKIToMain(popAppId, (*reservedVM).getPKI());

   //Send the initiator PKI everytime because it could be a different one each time
   POPString initiatorPKI = vpsm.getKeyFromReqMap(popAppId, reqID);
   if(vWrapper->_popc_sendPublicKey((*reservedVM), initiatorPKI) < 0){
      popc_node_log("[VSJM] VIRTUAL: Cannot send public key to worker guest (2).");
      return false;
   }


   //Send the Main node PKI if the VM just been reverted   
   if(hasBeenReverted){
      //Retrieve the main node PKI and send it 
      POPString mainNodePKI = vpsm.getMainPKIFromMapping(popAppId);
      if(strcmp(initiatorPKI.GetString(), mainNodePKI.GetString()) != 0){
         if(vWrapper->_popc_sendPublicKey((*reservedVM), mainNodePKI) < 0){
            popc_node_log("[VSJM] VIRTUAL: Cannot send public key to worker guest.");
            return false;
         }
      }
      
      //Send the Admin VM PKI 
      if(vWrapper->_popc_sendLocalPublicKey((*reservedVM)) < 0){
         popc_node_log("[VSJM] VIRTUAL: Cannot send local public key to worker guest.");
         return false;
      }
   }

   //Prepare ssh command
   char *tmp=getenv("POPC_RSH");
   if(tmp == NULL)
      argv[(*n)++] = (char*)"/usr/bin/ssh";
   else
      argv[(*n)++] = tmp;
   
   argv[*n] = new char[workerIp.size()+1]; //This alloc will be deleted by the JobMgr service
   argv[*n][workerIp.size()] = NULL;
   memcpy(argv[(*n)++], workerIp.c_str(), workerIp.size());
   
   return true;
}

/**
 * ViSaG : clementval
 * Write a pki on a VM authorized_keys file
 * @param popAppId   The POP Application ID
 * @param pki        The PKI to write
 */
void VirtSecureJobMgr::writePKIToVM(POPString popAppId, POPString pki){
//   popc_node_log("[VSJM] Write PKI to VM : %s / %s", popAppId.GetString(), pki.GetString());
   if(popAppId.Length() < 0){
      popc_node_log("[VSJM] ERROR: Unable to find the right VM, the POPAppID is empty");
      return;
   } else {
      std::list<POPvm>::iterator it;
      for(it=vm_list.begin(); it != vm_list.end(); it++){
         if(strcmp((*it).getReservedPOPAppId().GetString(), popAppId.GetString()) == 0){
            if(vWrapper->_popc_sendPublicKey((*it), pki) < 0){
               popc_node_log("[VSJM] ERROR: Can't write the PKI to the VM");
            }
            return;
         }
      }
   }
}

/**
 * ViSaG : clementval
 * Retrieve the PKI of a specific VM
 * @param popAppId   The POP Application ID
 * @return The PKI if found, an empty POPString if not found
 */
POPString VirtSecureJobMgr::getVMPKI(POPString popAppId){
   popc_node_log("[VSJM] Find VM PKI for ID %s", popAppId.GetString());
   if(popAppId.Length() < 0){
      popc_node_log("[VSJM] ERROR: Cannot find VM PKI. POPAppID is NULL");
      POPString dummy("");
      return dummy;
   }
   std::list<POPvm>::iterator it;
   for(it=vm_list.begin(); it != vm_list.end(); it++){
      if(strcmp((*it).getReservedPOPAppId().GetString(), popAppId.GetString()) == 0){
         popc_node_log("[VSJM] VM PKI FOUND");
         return (*it).getPKI();
      }
   }
   POPString dummy("");
   popc_node_log("[VSJM] VM PKI NOT FOUND");
   return dummy;
}

