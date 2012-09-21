/**
 * File : popc_search_node.cc
 * Author : Valentin Clement
 * Description : Implementation of the POP-C++ Search Node. This parallel object is responsible of the resource discovery.
 * Creation date : 
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval	2010/04/19	All code added for the semester project begins with this comment //Added by clementval, ends with 
 *                         //End of add
 * clementval	2010/04/19	All code modified during the semester project begins with //Modified by clementval, ends with 
 *                         //End of modification
 * clementval 	2010/05/05	Remove useless constructor.
 * clementval	2010/05/15	Add a funcionnality of null waiting (timer + semaphor)
 * clementval	2010/05/19	Rename the Node parclass in POPSearchNode
 * clementval	2011/10/31	Fix bug with null timeout under Darwin Arch
 * clementval	2012/08/23	Fix bug with the semaphore under Darwin Arch
 */

#include "popc_search_node.ph"
#include "nodethread.h"

/**
 * POPCSearchNode's constructor with challenge string (necessary to stop the object) and deamon boolean value to put the object 
 * in a deamon mode
 * @param
 * @param
 */
POPCSearchNode::POPCSearchNode(const POPString &challenge, bool deamon) : paroc_service_base(challenge) {
	// Init variables
	logicalClock=0;
	sem_logicalClock=0;
   psn_currentJobs=0;

	// Start service as a daemon
	if(deamon) Start();
	
	// Log entry
	popc_logger(DEBUG, "[PSN] POPCSearchNode created ...");	
}

/**
 * POPCSearchNode's destructor
 */
POPCSearchNode::~POPCSearchNode(){
	popc_logger(DEBUG, "[PSN] POPCSearchNode destroyed ...");
}


// Set the ID of the POPCSearchNode
void POPCSearchNode::setPOPCSearchNodeId(POPString nodeId){
	nodeInfo.nodeId = nodeId;
	popc_logger(DEBUG,  "[PSN] POPCSearchNode id : %s", nodeInfo.nodeId.GetString());
}

// Get the ID of this POPCSearchNode
POPString POPCSearchNode::getPOPCSearchNodeId(){
    return nodeInfo.nodeId;
}

// Set the operating system
void POPCSearchNode::setOperatingSystem(POPString operatingSystem){
    nodeInfo.operatingSystem = operatingSystem;
}

// Get the operating system
POPString POPCSearchNode::getOperatingSystem(){
    return nodeInfo.operatingSystem;
}

//Set the compute power
void POPCSearchNode::setPower(float p){
    nodeInfo.power = p;
}

//Get the compute power
float POPCSearchNode::getPower(){
    return nodeInfo.power;
}

// Set the CPU Speed
void POPCSearchNode::setCpuSpeed(int cpuSpeed){
    nodeInfo.cpuSpeed = cpuSpeed;
}

// Get the CPU Speed
int POPCSearchNode::getCpuSpeed(){
    return nodeInfo.cpuSpeed;
}

// Set the memory size
void POPCSearchNode::setMemorySize(float memorySize){
    nodeInfo.memorySize = memorySize;
}

// Get the memory size
int POPCSearchNode::getMemorySize(){
    return nodeInfo.memorySize;
}

// Set the network bandwidth
void POPCSearchNode::setNetworkBandwidth(float networkBandwidth){
    nodeInfo.networkBandwidth = networkBandwidth;
}

// Get the network bandwidth
float POPCSearchNode::getNetworkBandwidth(){
    return nodeInfo.networkBandwidth;
}

// Set the disk space
void POPCSearchNode::setDiskSpace(int diskSpace){
    nodeInfo.diskSpace = diskSpace;
}

// Get the disk space
int POPCSearchNode::getDiskSpace(){
    return nodeInfo.diskSpace;
}

//Set the protocol
void POPCSearchNode::setProtocol(POPString prot){
    nodeInfo.protocol = prot;
}

//Get the protocol
POPString POPCSearchNode::getProtocol(){
    return nodeInfo.protocol;
}

//Set the encoding
void POPCSearchNode::setEncoding(POPString enc){
    nodeInfo.encoding = enc;
}

//Get the encoding
POPString POPCSearchNode::getEncoding(){
    return nodeInfo.encoding;
}



// Add a POPCSearchNode as a neighbor of this POPCSearchNode
void POPCSearchNode::addNeighbor(POPCSearchNode &node){
	popc_logger(DEBUG,  "[PSN] NODE_ADD;%s", node.GetAccessPoint().GetAccessString());
	neighborsList.push_back(new POPCSearchNode(node));
}

// Remove a POPCSearchNode as a neighbor of this POPCSearchNode
void POPCSearchNode::removeNeighbor(POPCSearchNode &node){
	popc_logger(DEBUG,  "[PSN] NODE_REMOVE;%s", node.GetAccessPoint().GetAccessString());
	list<POPCSearchNode *>::iterator i;
	for(i=neighborsList.begin(); i != neighborsList.end(); i++){
		paroc_accesspoint crt = (*i)->GetAccessPoint();
		if(strcmp(crt.GetAccessString(), node.GetAccessPoint().GetAccessString()) == 0){
			neighborsList.erase(i);
			break;
		}
	}	
}

// Remove current POPCSearchNode's neighbors. Used after resources discovery to delete
// properly the parallel objects
void POPCSearchNode::deleteNeighbors(){
	list<POPCSearchNode *>::iterator i;
	for(i=neighborsList.begin(); i != neighborsList.end(); i++)
		delete (*i);
	neighborsList.clear();
}

// Called from the timer to unlock the semaphor used when the waiting time is set to 0
void POPCSearchNode::unlockDiscovery(POPString reqid){
try{
	// Get the request identifier to unlock the right sempahore
	std::string _reqid = reqid.GetString();
   // Post the semaphore to unlock the resource discovery	
	sem_post(reqsem[_reqid]);
   // Log 
	popc_logger(DEBUG, "[PSN] Unlocked by timer: %s", _reqid.c_str());   
} catch(...) {
	popc_logger(ERROR, "[PSN] Exception caught in unlockDisc");
}
}


POPString POPCSearchNode::getUID(){
	char uId[MAXREQUNIQUEIDLENGTH];
	sprintf(uId,"%s__%d", getPOPCSearchNodeId().GetString(), logicalClock);
   POPString uniqueId(uId);
	logicalClock++;
   return uniqueId;
}

// Service's entry point for resources discovery. This method will return an
// object of type "POPCSearchNodeInfos" containing information about nodes which fit the
// request
POPCSearchNodeInfos POPCSearchNode::launchDiscovery(Request req, int timeout){
try {

   if(req.isEndRequest()){
      timeout = 1;
   } else {
   	popc_logger(DEBUG,  "[PSN] LDISCOVERY;TIMEOUT;%d", timeout);
   }
	
	// create a new unique request id with the name of the node and its
	// logical clock. This uniqueId is added to the request

    
    // "network" self-reference to current node for callback results
    // prepare results place for current request in the currently running
    // request's list.
    POPCSearchNodeInfos nInfos;
    actualReqSyn.lock();
    actualReq[req.getUniqueId()] = nInfos;
    actualReqSyn.unlock();
    

    
	popc_logger(DEBUG, "[PSN] Resource discovery timeout: %d", timeout);    
   // wait until timeout or 1st answer
	if(timeout == 0){
		sem_t* current_sem; // Creating new semaphore pointer for the current request
		// Defining name for the named semaphore
		std::stringstream semname;
		semname << "/_popc_reqid" << getNextSemCounter();
		
		// Opening the semaphore before launching the unlocker thread
   	if((current_sem = sem_open(semname.str().c_str(), O_CREAT, S_IRUSR | S_IWUSR, 0)) == SEM_FAILED){
			popc_logger(DEBUG, "[PSN] SEMFAILED TO OPEN (DARWIN)");   
		}	
			
		std::string sem_name_reqid(req.getUniqueId().GetString());
		reqsem.insert(pair<std::string,sem_t*>(sem_name_reqid, current_sem)); 

	   if(reqsem[sem_name_reqid.c_str()] == NULL)
	   	popc_logger(ERROR, "[PSN] SEMAPHORE IS NOT IN THE MAP");   
		popc_logger(DEBUG, "[PSN] Semaphore map size is: %d, %s", reqsem.size(), sem_name_reqid.c_str());					

    	// begin resources discovery locally
    	paroc_accesspoint dummy;
    	askResourcesDiscovery(req, GetAccessPoint(), GetAccessPoint(), dummy);


		// Starting a timed thread to be able to unlock the resource discovery after a certain time
		NodeThread *timer = new NodeThread(UNLOCK_TIMEOUT, GetAccessPoint(), req.getUniqueId().GetString());
		timer->create();
		if(sem_wait(current_sem) != 0){
			if(sem_wait(current_sem) != 0)
				popc_logger(ERROR, " [PSN] SEMAPHOR: The semaphor couldn't not be blocked");
		}
		timer->stop();
		
		// Delete the semaphore
		sem_unlink(semname.str().c_str());
		// Remove the pointer from the map
		reqsem.erase(sem_name_reqid);
		current_sem = NULL;
	} else {
    	// begin resources discovery locally
    	paroc_accesspoint dummy;
    	askResourcesDiscovery(req, GetAccessPoint(), GetAccessPoint(), dummy);	
		sleep(timeout);
	}
    
    // getting results for current request and construct of POPCSearchNodeInfos object
    actualReqSyn.lock();
    
    POPCSearchNodeInfos results;
    map<POPString, POPCSearchNodeInfos>::iterator i;
    
    // ! for-statement because of problem with map comparison and POPString !
    for(i=actualReq.begin(); i != actualReq.end(); i++){
        POPString id = (*i).first;
        if(strcmp(id.GetString(), req.getUniqueId().GetString()) == 0){
            results = i->second;
            break;
        }
    }
	// erase the place for this request disallowing adding more results for this
   // request in the future
   actualReq.erase(req.getUniqueId());
   if(!req.isEndRequest()){
      popc_logger(DEBUG, "[PSN] RESULTS;%d", (int)results.getNodeInfos().size());
   }
   actualReqSyn.unlock();
   return results;
   
} catch(...) {
	popc_logger(ERROR, "[PSN] Exception caught in launchDiscovery");
}


}

int POPCSearchNode::getNextSemCounter()
{
	return sem_logicalClock++;
}

// POPCSearchNode's entry point to propagate request in the grid
// asker is the node which will receive positiv result
void POPCSearchNode::askResourcesDiscovery(Request req, paroc_accesspoint node_ap, paroc_accesspoint sender, paroc_accesspoint _psm){
try{
   if(req.isEndRequest()){
      ExplorationList oldEL(req.getExplorationList());
      // Adding the node's neighbors in the exploration list
      req.addNodeToExplorationList(getPOPCSearchNodeId(), getNeighbors());
	   if(req.getMaxHops() >= 0 || req.getMaxHops() == UNLIMITED_HOPS){
         list<POPCSearchNode *>::iterator i;
         // check if the local neighbors are already asked with the originally 
         // received exploration list
         for(i = neighborsList.begin(); i != neighborsList.end(); i++){
            if(!oldEL.isIn((*i)->getPOPCSearchNodeId())){
				   POPString nid;
				   nid = (*i)->getPOPCSearchNodeId();
               paroc_accesspoint dummy;
            	(*i)->askResourcesDiscovery(req, node_ap, GetAccessPoint(), dummy);
            }
         }
      }
      JobMgr jmg(getJobMgrRef());
      jmg.ApplicationEnd(req.getPOPAppId(), false);
   } else {
	   popc_logger(DEBUG,  "[PSN] ASKRDISCOVERY;ASKER;%s;REQID;%s", node_ap.GetAccessString(), req.getUniqueId().GetString());

      // check if the request has already been asked
      
      list<POPString>::iterator k;
      for(k = knownRequests.begin(); k != knownRequests.end(); k++){
         if(strcmp(k->GetString(),req.getUniqueId().GetString()) == 0){
			   popc_logger(DEBUG,  "[PSN] ALREADY_ASKED_REQUEST;%s", req.getUniqueId().GetString());
			   POPCSearchNode nsender(sender);
			   JobMgr jsender(nsender.getJobMgrRef());
			   jsender.UnregisterNode(GetAccessPoint());
			   removeNeighbor(nsender);			
            return;
         }
      }
      // save current request's uniqueId in the history
      knownRequests.push_back(req.getUniqueId());
      
      // check the maximum length of the history
      if(knownRequests.size() > MAXREQTOSAVE){
          knownRequests.pop_front();
      }
       
      // save the received exploration list
      ExplorationList oldEL(req.getExplorationList());
      
      // Adding the node's neighbors in the exploration list
      req.addNodeToExplorationList(getPOPCSearchNodeId(), getNeighbors());

      // Check local resources
      bool isResourcesOk = checkResource(req);
	   popc_logger(DEBUG,  "[PSN] CHECK;%s", (isResourcesOk)?"OK":"FAILED");      
      if(isResourcesOk){
         // If local resources are OK, build the response and give it back to
         // 'asker' node
         Response* resp = new Response(req.getUniqueId(), POPCSearchNodeInfo(nodeInfo), req.getExplorationList(), req.getPOPAppId());
	
	      /* If it's the local node or it's the last node, send directly the answer. Otherwise, send to the next node to reroute 
         the message */
         if(!req.getWayBack().isLastNode()){
            POPString listwb = req.getWayBack().getAsString();
            popc_logger(DEBUG,  "[PSN] NEED_REROUTE;WAYBACK;%s", listwb.GetString());
            rerouteResponse(*resp, req.getWayBack());
         } else {
         	try{
            	POPCSearchNode asker(node_ap);
					popc_logger(DEBUG,  "[PSN] SEND_REP;DEST;%s", node_ap.GetAccessString());
					asker.callbackResult(*resp);  
				} catch (POPException* ex){
					popc_logger(DEBUG,  "[PSN] Can't connect to %s", node_ap.GetAccessString());				
				}
            
         }
      }
       
      // Continue the propagation if more hops are allowed. It continues if the
      // max hops is zero to avoid counting "initial node" discovery.
	   if(req.getMaxHops() >= 0 || req.getMaxHops() == UNLIMITED_HOPS){
         req.addNodeToWb(nodeInfo.getPOPCSearchNodeId());
         list<POPCSearchNode *>::iterator i;
         // check if the local neighbors are already asked with the originally 
         // received exploration list
         for(i = neighborsList.begin(); i != neighborsList.end(); i++){
            if(!oldEL.isIn((*i)->getPOPCSearchNodeId())){
               POPString nid;
     			   nid = (*i)->getPOPCSearchNodeId();
					popc_logger(DEBUG,  "[PSN] FORWARD;DEST;%s", nid.GetString());
               paroc_accesspoint dummy;
             	(*i)->askResourcesDiscovery(req, node_ap, GetAccessPoint(), dummy);
            }
         }
      }
   }
} catch(...) {
	popc_logger(ERROR, "[PSN] Exception caught in askResource");
}
}

/**
 * ViSaG : clementval
 * Reroute the response by confidence link. The way is stored in the POPWayback object
 * @param resp Response to send to the initiator
 * @param wb   Way to the initiator node
 */
void POPCSearchNode::rerouteResponse(Response resp, POPWayback wb){
try{
   //It's Last node to contact
   if(wb.isLastNode()){
      //Create the interface to contact the POPCSearchNode
      paroc_accesspoint nextNodeAP;
      POPString nextNodeStr = wb.getNextNode();
      nextNodeAP.SetAccessString(nextNodeStr.GetString());
      POPCSearchNode nextNode(nextNodeAP);
      //Give the response to the initiator
      nextNode.callbackResult(resp);
      //Print a log
      popc_logger(DEBUG,  "[PSN] REROUTE;SEND_FINAL;%s", nextNodeStr.GetString());
   } else {
      //Get the next node to contact 
      POPString nextNodeStr = wb.getNextNode();
      wb.deleteNextNode();
     
      //Create the interface to contact the POPCSearchNode
      paroc_accesspoint nextNodeAP;
      nextNodeAP.SetAccessString(nextNodeStr.GetString());
      POPCSearchNode nextNode(nextNodeAP);
      //Send the response to the next node
      nextNode.rerouteResponse(resp, wb);
      //Print a log
      popc_logger(DEBUG,  "[PSN] REROUTE;TO;%s;WAYBACK;%s", nextNodeStr.GetString(), wb.getAsString().GetString());
   }
} catch(...) {
	popc_logger(ERROR, "[PSN] Exception caught in reroute");
}
}


// POPCSearchNode's return point to give back the response to the initial node
void POPCSearchNode::callbackResult(Response resp){
try{
	//Just for test purpose, must be removed in production release
	POPCSearchNodeInfo dni = resp.getFoundNodeInfo();
   actualReqSyn.lock();
	popc_logger(DEBUG, "[PSN] RECEIVE RESPONSE (REQID;%s;SENDER;%s)", resp.getReqUniqueId().GetString() , dni.nodeId.GetString());   
   map<POPString, POPCSearchNodeInfos>::iterator i;
   // visit the currently running list
   for(i=actualReq.begin(); i != actualReq.end(); i++){
      POPString id = (*i).first;
      // if the request's uniqueId is present, add the response to the list
      // and break the for-statement.
      if(strcmp(id.GetString(), resp.getReqUniqueId().GetString()) == 0){
         i->second.addANodeInfo(resp.getFoundNodeInfo());
         break;
      }
   }
   actualReqSyn.unlock();   
      
	// Unlock the semaphore for this request   
	std::string _reqid = resp.getReqUniqueId().GetString();
   if(reqsem[_reqid] != NULL){
   	popc_logger(DEBUG, "[PSN] CALLBACK UNLOCK SEMAPHORE");   
      sem_post(reqsem[_reqid]);
   } else {
		popc_logger(DEBUG, "[PSN] SEMAPHORE IS NULL UNABLE TO UNLOCK %s", _reqid.c_str()); 
	}
  } catch(...) {
	popc_logger(ERROR, "[PSN] Exception caught in callback");
} 
}

// internal comparison between request and local resources
bool POPCSearchNode::checkResource(Request req){    
   if(psn_currentJobs >= psn_maxjobs){
      popc_logger(ERROR, "[PSN] FAILED FOR NBJOB");
      return false;
   }

    // check about the operating system
   if(req.hasOperatingSystemSet()){
       //Should be check if the current architecture is in the list of requested architecture by the request
   }
 
   // check about the minimal cpu speed
	if(req.hasMinCpuSpeedSet()){
      if(req.getMinCpuSpeed() > getCpuSpeed())
          return false;
   }

	
   // check about the exact cpu speed
   if(req.hasExpectedCpuSpeedSet()){
      if(req.getExpectedCpuSpeed() <= getCpuSpeed())
          return false;
   }


	
   // check about the minimal memory size
   if(req.hasMinMemorySizeSet()){
      if(req.getMinMemorySize() > nodeInfo.memorySize){
         popc_logger(ERROR, "[PSN] FAILED FOR MIN MEM");
         return false;
      }
   }


   // check about the exact memory size
   //TODO Should not abort the check as Expected memory size is a wish but not a abort condition. Should be used in the fitness computation but not in Check.
   if(req.hasExpectedMemorySizeSet()){
      if(req.getExpectedMemorySize() >= nodeInfo.memorySize ){
         popc_logger(ERROR, "[PSN] FAILED FOR EXP MEM");
         return false;
      }
   }
   
   //Check bandwith only if the nodeInfo networkBandwidth has been set
   if(nodeInfo.networkBandwidth > 0.5){
      // check about the minimal network bandwith
	   if(req.hasMinNetworkBandwidthSet()){
        	if(req.getMinNetworkBandwidth() > nodeInfo.networkBandwidth){
            popc_logger(ERROR, "[PSN] FAILED FOR MIN BAN");
        		return false;
         }
      }
      
      // check about the exact network bandwith
      if(req.hasExpectedNetworkBandwidthSet()){
		   if(req.getExpectedNetworkBandwidth() >= nodeInfo.networkBandwidth){
            popc_logger(ERROR, "[PSN] FAILED FOR EXP BAN");
			   return false;
         }
	   }
   }

	// check about the minimal disk space
	if(req.hasMinDiskSpaceSet()){
		if(req.getMinDiskSpace() > getDiskSpace()){
         popc_logger(ERROR, "[PSN] FAILED FOR DISK SPACE");
			return false;
      }
	}
 
    // check about the min power
	if(req.hasMinPowerSet()){
		if(req.getMinPower() > getPower()){
         popc_logger(ERROR, "[PSN] FAILED FOR MIN POW");
	   	return false;
      }
	}

	if(req.hasExpectedPowerSet()){
		if(req.getExpectedPower() > getPower()){
         popc_logger(ERROR, "[PSN]ERROR: FAILED FOR EXP POW");
	   	return false;
      }
	}
    
    // if no return until there, everything's OK!
    return true;
}

// Return a list of neighbors' nodeId
list<POPString> POPCSearchNode::getNeighbors(){
    list<POPString> neighbors;
    list<POPCSearchNode *>::iterator i;
    for(i = neighborsList.begin(); i != neighborsList.end(); i++){
        neighbors.push_back((*i)->getPOPCSearchNodeId());
    }
    return neighbors;
}

//Set the associated JobMgr access point
void POPCSearchNode::setJobMgrRef(const paroc_accesspoint &jobmgrRef){
	nodeInfo.jobmgr = jobmgrRef;
}

//return the associated JobMgr access point
paroc_accesspoint POPCSearchNode::getJobMgrRef(){
	return nodeInfo.jobmgr;
}

//Set the SSH public key
void POPCSearchNode::setPKI(POPString pk){
   nodeInfo.pki=pk;
}

//Get the SSH Public key
POPString POPCSearchNode::getPKI(){
   return nodeInfo.pki;
}

/**
 * ViSaG : clementval
 * Set the maximum job execution for this node
 * @param maxjobs Maximum number of jobs
 */
void POPCSearchNode::setMaxJobs(int maxjobs){
   psn_maxjobs=maxjobs;
}

/**
 * ViSaG : clementval
 * Get the maximum number of jobs execution on this node
 * @return Maximum number of execution on the node
 */
int POPCSearchNode::getMaxJobs(){
   return psn_maxjobs;
}

/**
 * ViSaG : clementval
 * Upadte resources to the node with a new job info
 * @param power      Power needed by the job
 * @param memorySize Memory size needed by the job
 * @param bandwidth  Bandwidth needed by the job
 */
void POPCSearchNode::addJob(float power, float memorySize, float bandwidth){
   nodeInfo.memorySize-=memorySize;
   nodeInfo.power-=power;
   nodeInfo.networkBandwidth-=bandwidth;
   psn_currentJobs++;
}

/**
 * ViSaG : clementval
 * Give back resources to the node
 * @param power      Power liberated by the job
 * @param memorySize Memory size liberated by the job
 * @param bandwidth  Bandwidth liberated by the job
 */
void POPCSearchNode::removeJob(float power, float memorySize, float bandwidth, int nbJob){
   nodeInfo.memorySize=memorySize;
   nodeInfo.power=power;
   nodeInfo.networkBandwidth=bandwidth;
   psn_currentJobs-=nbJob;
}

POPString POPCSearchNode::getNeighborsAsString(){
	POPString lst;
	std::string strlst;
	list<POPCSearchNode *>::iterator i;
   for(i = neighborsList.begin(); i != neighborsList.end(); i++){
   	strlst.append((*i)->getPOPCSearchNodeId().GetString());
   	strlst.append(";");
   }
   popc_logger(DEBUG, "[PSN] NODENEIGH:%s", strlst.c_str());   
	lst = strlst.c_str();	
	return lst;
}
