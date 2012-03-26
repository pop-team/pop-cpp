/**
 * File : secure_jobmgr.ph
 * Author : Valentin Clément
 * Description : Declarataion of the parallel object SecureJobMgr
 * Creation date : 2010/12/07
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval  2010/12/07  Creation of this file
 */



#include "secure_jobmgr.ph"

#include "popc_security_manager.ph"
#include "codemgr.ph"
#include "appservice.ph"

/**
 * ViSaG : clementval
 * Secure Job Manager constructor
 * @param deamon
 * @param conf
 * @param challenge
 * @param url
 * @param nodeAccess
 * @param psmRef
 */
SecureJobMgr::SecureJobMgr(bool daemon, const POPString &conf, const POPString &challenge, 
   const POPString &url, const paroc_accesspoint &nodeAccess, const paroc_accesspoint &psmRef) 
   : JobMgr(daemon, conf, challenge, url, nodeAccess, psmRef) {

   //Give the JobMgr reference to the PSM
   POPCSecurityManager psm(psmRef);
   psm.setJobMgrRef(GetAccessPoint());

   //Get a local copy of the PKI
   _localPublicKey = psm.getLocalPKI();
}

/**
 * ViSaG : clementval
 * Secure JobMgr destructor
 */
SecureJobMgr::~SecureJobMgr(){
   popc_node_log("VSJobMgr destroyed ...");
}


/* ##### JobMgr overwritten methods ##### */

/**
 * ViSaG : clementval
 * Allocate resources for the job execution
 * @param localservice
 * @param objname
 * @param od
 * @param howmany
 * @param fitness
 * @param jobcontacts 
 * @param reserveIDs
 * @param requestInfo
 * @param iptrace
 * @param tracesize
 */
bool SecureJobMgr::AllocResource(const paroc_accesspoint &localservice, const POPString &objname, const paroc_od &od, int howmany, float *fitness, paroc_accesspoint *jobcontacts, int *reserveIDs, int requestInfo[3], int iptrace[MAX_HOPS], int tracesize)
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
   popc_node_log("OD_SEARCH(AR) : depth=%d, size=%d, time=%d", od.getSearchMaxDepth(), od.getSearchMaxReqSize(), od.getSearchWaitTime());
	if((maxhopint=od.getSearchMaxDepth()) > 0){
		r.setMaxHops(maxhopint);
		popc_node_log("JobMgr : Max hop set via OD : %d", maxhopint);
	} else {
		//Recover the max Hop env variable
		char *maxhop;
		if((maxhop=getenv("POPC_SEARCHMAXHOP"))){
			maxhopint = atoi(maxhop);
			popc_node_log("JobMgr : Max hop set via ENV Variable : %d", maxhopint);
		} else {
			maxhopint = MAXHOP;
			popc_node_log("JobMgr : Max hop env variable is not set. Default value %d will be used", maxhopint);
		}
	}
	//Setting the value of max hop in the request
	r.setMaxHops(maxhopint);
	
	//Recover the maximum size of the request. This is not implemented yet
	int maxsizeint;
	if((maxsizeint = od.getSearchMaxReqSize()) > 0){
		popc_node_log("JobMgr : Request max size set via OD : %d", maxsizeint);
		//To be implemented
	}
	//Recover the od waiting time or env var POPC_SEARCHTIMEOUT. If both are not set, TIMEOUT constant is defined in JobMgr.ph
	int timeoutint = 0;
	if((timeoutint = od.getSearchWaitTime()) >= 0){
		popc_node_log("JobMgr : Timeout set via OD : %d", timeoutint);
	} else {
		//Recover the timeout in the POPC_SEARCHTIMEOUT env variable
		char *timeout;
		if((timeout=getenv("POPC_SEARCHTIMEOUT"))){
			timeoutint = atoi(timeout);
			popc_node_log("JobMgr : Timeout set via ENV Variable : %d", timeoutint);
		}else {
			timeoutint = TIMEOUT;
			popc_node_log("JobMgr : Timeout env variable is not set. Default value %d will be used", timeoutint);
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
   //TODO get PKI of VM
   r.setPKI(_localPublicKey);

   POPString reqID = localPSN.getUID();
   r.setUniqueId(reqID);

	//Launch the discovery and recover the responses	
	POPCSearchNodeInfos responses = localPSN.launchDiscovery(r, timeoutint);
	//Check if there is any responses
	if(responses.getNodeInfos().size() == 0){
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
		reserveIDs[jobindex] = jobmgr.Reserve(od, t, popAppId, r.getUniqueId());	
		//if reserve ID is egal to 0, the reservation process failed. If we can't reserver on any responding machine, we trow an exception
		if(reserveIDs[jobindex] == 0){
			jobindex--;
			failedReservation++;
			if(failedReservation==n_response)
				return false;
		} else {
			//Reservation process succeed

			//setting the remote JobMgr info to execute the parallel object
			jobcontacts[jobindex].SetAccessString(jm_ap.GetAccessString());
         POPString pki(ni->getPKI());
         POPCSecurityManager psm(_localPSM);
         psm.writePKI(popAppId, pki); //TODO write to the good VM
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
	return ret;
}

