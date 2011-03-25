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
 */

#include "popc_search_node.ph"
#include "nodethread.h"

//POPCSearchNode's constructor with challenge string (necessary to stop the object) and deamon boolean value to put the object in a deamon mode
POPCSearchNode::POPCSearchNode(const paroc_string &challenge, bool deamon) : paroc_service_base(challenge) {
	popc_node_log("PSN Created ...");
	logicalClock=0;
   psn_currentJobs=0;

#ifdef __APPLE__
   pt_locker == NULL;
#else
	sem_t locker;
	pt_locker = &locker;
#endif
	if(deamon) Start();
}

//POPCSearchNode's destructor
POPCSearchNode::~POPCSearchNode(){
	popc_node_log("[PSN] POPCSearchNode destroyed ...");
}


// Set the ID of the POPCSearchNode
void POPCSearchNode::setPOPCSearchNodeId(paroc_string nodeId){
	nodeInfo.nodeId = nodeId;
	sprintf(log, "[PSN] POPCSearchNode id : %s", nodeInfo.nodeId.GetString());
	popc_node_log(log);
}

// Get the ID of this POPCSearchNode
paroc_string POPCSearchNode::getPOPCSearchNodeId(){
    return nodeInfo.nodeId;
}

// Set the operating system
void POPCSearchNode::setOperatingSystem(paroc_string operatingSystem){
    nodeInfo.operatingSystem = operatingSystem;
}

// Get the operating system
paroc_string POPCSearchNode::getOperatingSystem(){
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
void POPCSearchNode::setProtocol(paroc_string prot){
    nodeInfo.protocol = prot;
}

//Get the protocol
paroc_string POPCSearchNode::getProtocol(){
    return nodeInfo.protocol;
}

//Set the encoding
void POPCSearchNode::setEncoding(paroc_string enc){
    nodeInfo.encoding = enc;
}

//Get the encoding
paroc_string POPCSearchNode::getEncoding(){
    return nodeInfo.encoding;
}



// Add a POPCSearchNode as a neighbor of this POPCSearchNode
void POPCSearchNode::addNeighbor(POPCSearchNode &node){
	sprintf(log, "[PSN] NODE_ADD;%s", node.GetAccessPoint().GetAccessString());
	popc_node_log(log);
	neighborsList.push_back(new POPCSearchNode(node));
}

// Remove a POPCSearchNode as a neighbor of this POPCSearchNode
void POPCSearchNode::removeNeighbor(POPCSearchNode &node){
	sprintf(log, "[PSN] NODE_REMOVE;%s", node.GetAccessPoint().GetAccessString());
	popc_node_log(log);
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
void POPCSearchNode::unlockDiscovery(){
	sem_post(pt_locker);
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
	gettimeofday(&start, NULL);	//This line is just for test purpose so it can be removed in production release
   //Log



   if(req.isEndRequest()){
      timeout = 1;
   } else {
   	sprintf(log, "[PSN] LDISCOVERY;TIMEOUT;%d", timeout);
   	popc_node_log(log);
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
    
    // begin resources discovery locally
    paroc_accesspoint dummy;
    askResourcesDiscovery(req, GetAccessPoint(), GetAccessPoint(), dummy);
    
   // wait until timeout
	if(timeout == 0){
#ifdef __APPLE__
		if(pt_locker == NULL)
         pt_locker = sem_open("popc_sem_resdisc", O_CREAT, 0, 0);
      if(pt_locker == SEM_FAILED)
         popc_node_log("[PSN]ERROR: SEMFAILED TO OPEN");
#else
		sem_init(pt_locker, 0, 0);
#endif
		NodeThread *timer = new NodeThread(UNLOCK_TIMEOUT, GetAccessPoint());
		timer->create();
		sem_wait(pt_locker);
		timer->stop();
#ifdef __APPLE__
		sem_unlink("popc_sem_resdisc");
#endif
	} else {
		sleep(timeout);
	}
    
    // getting results for current request and construct of POPCSearchNodeInfos object
    actualReqSyn.lock();
    
    POPCSearchNodeInfos results;
    map<paroc_string, POPCSearchNodeInfos>::iterator i;
    
    // ! for-statement because of problem with map comparison and paroc_string !
    for(i=actualReq.begin(); i != actualReq.end(); i++){
        paroc_string id = (*i).first;
        if(strcmp(id.GetString(), req.getUniqueId().GetString()) == 0){
            results = i->second;
            break;
        }
    }
	// erase the place for this request disallowing adding more results for this
   // request in the future
   actualReq.erase(req.getUniqueId());
   actualReqSyn.unlock();

   if(!req.isEndRequest()){
      sprintf(log, "[PSN] RESULTS;%d", results.getNodeInfos().size());
   	popc_node_log(log);
   }
   return results;
}

// POPCSearchNode's entry point to propagate request in the grid
// asker is the node which will receive positiv result
void POPCSearchNode::askResourcesDiscovery(Request req, paroc_accesspoint node_ap, paroc_accesspoint sender, paroc_accesspoint _psm){
   if(req.isEndRequest()){
      //popc_node_log("Recieve application end request");
      ExplorationList oldEL(req.getExplorationList());
      // Adding the node's neighbors in the exploration list
      req.addNodeToExplorationList(getPOPCSearchNodeId(), getNeighbors());
	   if(req.getMaxHops() >= 0 || req.getMaxHops() == UNLIMITED_HOPS){
         list<POPCSearchNode *>::iterator i;
         // check if the local neighbors are already asked with the originally 
         // received exploration list
         for(i = neighborsList.begin(); i != neighborsList.end(); i++){
            if(!oldEL.isIn((*i)->getPOPCSearchNodeId())){
				   paroc_string nid;
				   nid = (*i)->getPOPCSearchNodeId();
				   //sprintf(log, "FORWARD;DEST;%s", nid.GetString());
				   popc_node_log(log);
               paroc_accesspoint dummy;
            	(*i)->askResourcesDiscovery(req, node_ap, GetAccessPoint(), dummy);
            }
         }
      }
      JobMgr jmg(getJobMgrRef());
      jmg.ApplicationEnd(req.getPOPAppId(), false);
   } else {
	   sprintf(log, "[PSN] ASKRDISCOVERY;ASKER;%s;REQID;%s", node_ap.GetAccessString(), req.getUniqueId().GetString());
	   popc_node_log(log);

      // check if the request has already been asked
      list<paroc_string>::iterator k;
      for(k = knownRequests.begin(); k != knownRequests.end(); k++){
         if(strcmp(k->GetString(),req.getUniqueId().GetString()) == 0){
			   sprintf(log, "[PSN] ALREADY_ASKED_REQUEST;%s", req.getUniqueId().GetString());
			   popc_node_log(log);
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
	   sprintf(log, "[PSN] CHECK;%s", (isResourcesOk)?"OK":"FAILED");      
	   popc_node_log(log);
      if(isResourcesOk){
         // If local resources are OK, build the response and give it back to
         // 'asker' node
         Response* resp = new Response(req.getUniqueId(), POPCSearchNodeInfo(nodeInfo), req.getExplorationList(), req.getPOPAppId());
	
	      /* If it's the local node or it's the last node, send directly the answer. Otherwise, send to the next node to reroute 
         the message */
         if(!req.getWayBack().isLastNode()){
            paroc_string listwb = req.getWayBack().getAsString();
            sprintf(log, "[PSN] NEED_REROUTE;WAYBACK;%s", listwb.GetString());
      	   popc_node_log(log);
            rerouteResponse(*resp, req.getWayBack());
         } else {
            POPCSearchNode asker(node_ap);
            sprintf(log, "[PSN] SEND_REP;DEST;%s", node_ap.GetAccessString());
            popc_node_log(log);
            asker.callbackResult(*resp);  
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
               paroc_string nid;
     			   nid = (*i)->getPOPCSearchNodeId();
               sprintf(log, "[PSN] FORWARD;DEST;%s", nid.GetString());
               popc_node_log(log);
               paroc_accesspoint dummy;
             	(*i)->askResourcesDiscovery(req, node_ap, GetAccessPoint(), dummy);
            }
         }
      }
   }
}

/**
 * ViSaG : clementval
 * Reroute the response by confidence link. The way is stored in the POPWayback object
 * @param resp Response to send to the initiator
 * @param wb   Way to the initiator node
 */
void POPCSearchNode::rerouteResponse(Response resp, POPWayback wb){
   //It's Last node to contact
   if(wb.isLastNode()){
      //Create the interface to contact the POPCSearchNode
      paroc_accesspoint nextNodeAP;
      paroc_string nextNodeStr = wb.getNextNode();
      nextNodeAP.SetAccessString(nextNodeStr.GetString());
      POPCSearchNode nextNode(nextNodeAP);
      //Give the response to the initiator
      nextNode.callbackResult(resp);
      //Print a log
      sprintf(log, "[PSN] REROUTE;SEND_FINAL;%s", nextNodeStr.GetString());
      popc_node_log(log);
   } else {
      //Get the next node to contact 
      paroc_string nextNodeStr = wb.getNextNode();
      wb.deleteNextNode();
     
      //Create the interface to contact the POPCSearchNode
      paroc_accesspoint nextNodeAP;
      nextNodeAP.SetAccessString(nextNodeStr.GetString());
      POPCSearchNode nextNode(nextNodeAP);
      //Send the response to the next node
      nextNode.rerouteResponse(resp, wb);
      //Print a log
      sprintf(log, "[PSN] REROUTE;TO;%s;WAYBACK;%s", nextNodeStr.GetString(), wb.getAsString().GetString());
      popc_node_log(log);
   }
}


// POPCSearchNode's return point to give back the response to the initial node
void POPCSearchNode::callbackResult(Response resp){
	//Just for test purpose, must be removed in production release
	gettimeofday(&end, NULL);
	long msec_start;
	msec_start = (start.tv_sec)*1000000;
	msec_start += (start.tv_usec);
	long msec_end;
	msec_end = (end.tv_sec)*1000000;
	msec_end += (end.tv_usec);
	long diff = msec_end-msec_start;
	POPCSearchNodeInfo dni = resp.getFoundNodeInfo();
	sprintf(log, "[VSPSN] RECEIVE RESPONSE (REQID;%s;SENDER;%s)", resp.getReqUniqueId().GetString() , dni.nodeId.GetString());
	popc_node_log(log);
	//End for test
   actualReqSyn.lock();
   map<paroc_string, POPCSearchNodeInfos>::iterator i;

   // visit the currently running list
   for(i=actualReq.begin(); i != actualReq.end(); i++){
      paroc_string id = (*i).first;
      // if the request's uniqueId is present, add the response to the list
      // and break the for-statement.
      if(strcmp(id.GetString(), resp.getReqUniqueId().GetString()) == 0){
         i->second.addANodeInfo(resp.getFoundNodeInfo());
         break;
      }
   }
   actualReqSyn.unlock();
   if(pt_locker != NULL)
   	sem_post(pt_locker);
}

// internal comparison between request and local resources
bool POPCSearchNode::checkResource(Request req){    
   if(psn_currentJobs >= psn_maxjobs){
      popc_node_log("[PSN]ERROR: FAILED FOR NBJOB");
      return false;
   }

    // check about the operating system
   if(req.hasOperatingSystemSet()){
       //Should be check if the current architecture is in the list of requested architecture by the request
   }
 
   // check about the minimal cpu speed
	if(req.hasMinCpuSpeedSet()){
      /*sprintf(log, "MINCPUSPEED %d, %d", req.getMinCpuSpeed(), getCpuSpeed());      
		popc_node_log(log);*/
      if(req.getMinCpuSpeed() > getCpuSpeed())
          return false;
   }

	
   // check about the exact cpu speed
   if(req.hasExpectedCpuSpeedSet()){
      /*sprintf(log, "EXPCPUSPEED %d, %d", req.getExpectedCpuSpeed(), getCpuSpeed());      
		popc_node_log(log);*/
      if(req.getExpectedCpuSpeed() <= getCpuSpeed())
          return false;
   }


	
   // check about the minimal memory size
   if(req.hasMinMemorySizeSet()){
     /* sprintf(log, "MINMEM %f, %f", req.getMinMemorySize(), nodeInfo.memorySize);      
      popc_node_log(log);*/
      if(req.getMinMemorySize() > nodeInfo.memorySize){
         popc_node_log("[PSN]ERROR: FAILED FOR MIN MEM");
         return false;
      }
   }


   // check about the exact memory size
   //TODO Should not abort the check as Expected memory size is a wish but not a abort condition. Should be used in the fitness computation but not in Check.
   if(req.hasExpectedMemorySizeSet()){
      /*sprintf(log,"EXPMEM %f, %f", req.getExpectedMemorySize(), nodeInfo.memorySize);       
		popc_node_log(log);*/
      if(req.getExpectedMemorySize() >= nodeInfo.memorySize ){
         popc_node_log("[PSN]ERROR: FAILED FOR EXP MEM");
         return false;
      }
   }
   
   //Check bandwith only if the nodeInfo networkBandwidth has been set
   if(nodeInfo.networkBandwidth > 0.5){
      // check about the minimal network bandwith
	   if(req.hasMinNetworkBandwidthSet()){
         /*sprintf(log,"MINBAN %f, %f", req.getMinNetworkBandwidth(), nodeInfo.networkBandwidth);      
		   popc_node_log(log);*/
        	if(req.getMinNetworkBandwidth() > nodeInfo.networkBandwidth){
            popc_node_log("[PSN]ERROR: FAILED FOR MIN BAN");
        		return false;
         }
      }
      
      // check about the exact network bandwith
      if(req.hasExpectedNetworkBandwidthSet()){
         /*sprintf(log, "EXPBAN %f, %f", req.getExpectedNetworkBandwidth(), nodeInfo.networkBandwidth);      
		   popc_node_log(log);*/
		   if(req.getExpectedNetworkBandwidth() >= nodeInfo.networkBandwidth){
            popc_node_log("[PSN]ERROR: FAILED FOR EXP BAN");
			   return false;
         }
	   }
   }

	// check about the minimal disk space
	if(req.hasMinDiskSpaceSet()){
//      sprintf(log, "MINDIS %d, %d", req.getMinDiskSpace(), getDiskSpace());      
		popc_node_log(log);
		if(req.getMinDiskSpace() > getDiskSpace()){
         popc_node_log("[PSN]ERROR: FAILED FOR DISK SPACE");
			return false;
      }
	}
 
    // check about the min power
	if(req.hasMinPowerSet()){
      /*sprintf(log, "MINPOW %f, %f", req.getMinPower(), getPower());      
		popc_node_log(log);*/
		if(req.getMinPower() > getPower()){
         popc_node_log("[PSN]ERROR: FAILED FOR MIN POW");
	   	return false;
      }
	}

	if(req.hasExpectedPowerSet()){
      /*sprintf(log, "EXPPOW %f, %f", req.getExpectedPower(), getPower());      
		popc_node_log(log);*/
		if(req.getExpectedPower() > getPower()){
         popc_node_log("[PSN]ERROR: FAILED FOR EXP POW");
	   	return false;
      }
	}
    
    // if no return until there, everything's OK!
    return true;
}

// Return a list of neighbors' nodeId
list<paroc_string> POPCSearchNode::getNeighbors(){
    list<paroc_string> neighbors;
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
void POPCSearchNode::setPKI(paroc_string pk){
   nodeInfo.pki=pk;
}

//Get the SSH Public key
paroc_string POPCSearchNode::getPKI(){
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
  /* sprintf(log,"AFTER_REMOVE:MEM:%f:POW:%f:BAN:%f", nodeInfo.memorySize, nodeInfo.power, nodeInfo.networkBandwidth);
   popc_node_log(log);*/
   psn_currentJobs-=nbJob;
}

//Method to write log in a file
int POPCSearchNode::popc_node_log(const char *log)
{
	char *tmp=getenv("POPC_TEMP");
	char logfile[256];
	if (tmp!=NULL) sprintf(logfile,"%s/popc_node_log",tmp);
	else strcpy(logfile, "/tmp/pop_node.log");

	FILE *f=fopen(logfile,"a");
	if (f==NULL) return 1;
	time_t t=time(NULL);
	fprintf(f, "%s", ctime(&t));
	/*va_list ap;
	va_start(ap, log);
	vfprintf(f, log, ap);*/
	fprintf(f,"%s",log);
	fprintf(f,"\n");
	//va_end(ap);
	fclose(f);
	return 0;
}
