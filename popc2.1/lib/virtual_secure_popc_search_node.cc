/**
 * File : virtual_secure_popc_search_node.cc
 * Author : Valentin Clement (clementval)
 * Description : Implementation file of the Virtual Secure POP-C++ Search Node (resources discovery)
 * Creation date : 2010/12/07
 * 
 * Modifications :
 * Authors		Date			Description
 * clementval	2010/12/07  Creation of the virtual version of the PSN
 */
#include "virtual_secure_popc_search_node.ph"
#include "virtual_secure_jobmgr.ph"
#include "virtual_popc_security_manager.ph"

using namespace std;

class NodeThread : public paroc_thread {
public:
	NodeThread(int timeout, const paroc_accesspoint &node);
	virtual void start();
	virtual void stop();
private:
	int _timeout;
	bool _running;
	bool _unlock;
	paroc_accesspoint _node;
};

//Implementation of this small class
NodeThread::NodeThread(int timeout, const paroc_accesspoint &node) : paroc_thread(true) {
	_timeout = timeout;
	_node = node;
	_running = true;
	_unlock = true;
}
//Start a timer and contact de POPCSearchNode when it's finished
void NodeThread::start(){
	POPCSearchNode n(_node);
	Timer t;
	t.Start();
	while(_running){
		usleep(100000);
		if(t.Elapsed() > _timeout){
			t.Stop();
			_running = false;
		}
	}
	if(_unlock)
		n.unlockDiscovery();
}
//Stop the timer
void NodeThread::stop(){
	_unlock = false;
	_running = false;
}

/**
 * ViSaG : clementval
 * Virtual POPCSearchNode's constructor
 * @param challenge  Challenge string used to stop the services
 * @param deamon     If TRUE, the parallel object will run in deamon mode
 */
VirtSecurePOPCSearchNode::VirtSecurePOPCSearchNode(const POPString &challenge, 
   bool deamon) : VirtualPOPCSearchNode(challenge, deamon) {
	popc_node_log("VirtualPOPCSearchNode Created ...");
}

/**
 * ViSaG : clementval
 * Destructor of VirtualPOPCSearchNode
 */
VirtSecurePOPCSearchNode::~VirtSecurePOPCSearchNode(){
	popc_node_log("VirtualPOPCSearchNode destroyed ...");
}

/**
 * ViSaG : clementval
 * Overwritten method : check resource with virtual machine. As the JobMgr stores any information about the VMs, the PSN has to 
 * contact him for the resource check
 * @param req Request to be checked
 */
bool VirtSecurePOPCSearchNode::checkResource(Request req){
   //popc_node_log("[VSPSN] Check resources");
   VirtSecureJobMgr vsjm(getJobMgrRef());
   return vsjm.checkVM(req);
}

/**
 * ViSaG : clementval
 * Setter for the local POPCSecurityNode reference
 * @param The local reference of the PSM
 */
void VirtSecurePOPCSearchNode::setPSMRef(paroc_accesspoint psm){
   _localPSM = psm;
}

/**
 * ViSaG : clementval
 * Getter for the local POPCSecurityManager reference
 * @return The local reference to the PSM
 */
paroc_accesspoint VirtSecurePOPCSearchNode::getPSMRef(){
   return _localPSM;
}


/**
 * ViSaG : clementval
 * Set the PKI to the node info
 * @param pk   The PKI
 */
void VirtSecurePOPCSearchNode::setPKI(POPString pk){
   nodeInfo.pki=pk;
}

/**
 * ViSaG : clementval
 * Get the PKI to the node info
 * @return The PKI
 */
POPString VirtSecurePOPCSearchNode::getPKI(){
   return nodeInfo.pki;
}




/*
 * OVERWRITTEN METHOD
 */

// Service's entry point for resources discovery. This method will return an
// object of type "POPCSearchNodeInfos" containing information about nodes which fit the
// request
POPCSearchNodeInfos VirtSecurePOPCSearchNode::launchDiscovery(Request req, int timeout){
	gettimeofday(&start, NULL);	//This line is just for test purpose so it can be removed in production release
   //Log
	
   if(!req.isEndRequest()){
      sprintf(log, "[VSPSN] LDISCOVERY;TIMEOUT;%d;REQID;%s", timeout, req.getUniqueId().GetString());
   	popc_node_log(log);

      //Add the main PKI in the request
      VirtualPOPCSecurityManager psm(_localPSM);
      POPString mainPKI = psm.getMainPKIFromMapping(req.getPOPAppId());
      if(strcmp(mainPKI, "") == 0){
         //popc_node_log("[VSPSN] SET_SAME_KEY");
         req.setMainPKI(req.getPKI());
      } else {
         //popc_node_log("[VSPSN] SET_KEY_FROM_MAPPING");
         req.setMainPKI(mainPKI);
      }
      //Add the mapping to the main PSM AP
      psm.addMainAPMapping(req.getPOPAppId(), _localPSM);
   } else {
      timeout = 1;
   }

    // "network" self-reference to current node for callback results
    // prepare results place for current request in the currently running
    // request's list.
    POPCSearchNodeInfos nInfos;
    actualReqSyn.lock();
    actualReq[req.getUniqueId()] = nInfos;
    actualReqSyn.unlock();
    
    // begin resources discovery locally
    askResourcesDiscovery(req, GetAccessPoint(), GetAccessPoint(), _localPSM);
  
   // wait until timeout
	if(timeout == 0){
	   sem_init(pt_locker, 0, 0);
		NodeThread *timer = new NodeThread(UNLOCK_TIMEOUT, GetAccessPoint());
		timer->create();
		sem_wait(pt_locker);
		timer->stop();
	} else {
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
   actualReqSyn.unlock();

   if(!req.isEndRequest()){
	   sprintf(log, "[VSPSN] RESULTS;%d", results.getNodeInfos().size());
   	popc_node_log(log);
   }

   return results;
}

// POPCSearchNode's entry point to propagate request in the grid
// asker is the node which will receive positiv result
void VirtSecurePOPCSearchNode::askResourcesDiscovery(Request req, paroc_accesspoint node_ap, paroc_accesspoint sender, paroc_accesspoint _psm){
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
				   sprintf(log, "[VSPSN] FORWARD;DEST;%s", nid.GetString());
				   popc_node_log(log);
            	(*i)->askResourcesDiscovery(req, node_ap, GetAccessPoint(), _psm);
            }
         }
      }
      VirtSecureJobMgr vsjm(getJobMgrRef());
      vsjm.ApplicationEnd(req.getPOPAppId(), false);
   } else {
	   sprintf(log, "[VSPSN] ASKRDISCOVERY;ASKER;%s;REQID;%s", node_ap.GetAccessString(), req.getUniqueId().GetString());
	   popc_node_log(log);

      /** 
       * ViSaG : clementval
       * Add the main PKI in the mapping for future resource discovery from this node
       * Add the main PSM AP in the mapping for routing PKI
       */

      if(req.getMainPKI().Length()<0)
         popc_node_log("[VSPSN] MAIN PKI IS EMPTY");
      if(req.getPOPAppId().Length()<0)
         popc_node_log("[VSPSN] POPAppID IS EMPTY");
      VirtualPOPCSecurityManager psm(_localPSM);
      psm.addMainPKIMapping(req.getPOPAppId(), req.getMainPKI());
      psm.addMainAPMapping(req.getPOPAppId(), _psm);
      // check if the request has already been asked
      list<POPString>::iterator k;
      for(k = knownRequests.begin(); k != knownRequests.end(); k++){
         if(strcmp(k->GetString(),req.getUniqueId().GetString()) == 0){
			   sprintf(log, "[VSPSN] ALREADY_ASKED_REQUEST;%s", req.getUniqueId().GetString());
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
	   sprintf(log, "[VSPSN] CHECK;%s", (isResourcesOk)?"OK":"FAILED");      
	   popc_node_log(log);
      if(isResourcesOk){
         // If local resources are OK, build the response and give it back to 'asker' node
         Response* resp = new Response(req.getUniqueId(), POPCSearchNodeInfo(nodeInfo), 
                                       req.getExplorationList(), req.getPOPAppId());
	
	      /* 
          * If it's the local node or it's the last node, send directly the answer. Otherwise, send to the next node to reroute 
          * the message 
          */
         if(!req.getWayBack().isLastNode()){
            POPString listwb = req.getWayBack().getAsString();
            sprintf(log, "[VSPSN] NEED_REROUTE_RESP;WAYBACK;%s", listwb.GetString());
      	   popc_node_log(log);
            rerouteResponse(*resp, req.getWayBack());
         } else {
            POPCSearchNode asker(node_ap);
            sprintf(log, "[VSPSN] SEND_DIRECT_RESP;DEST;%s", node_ap.GetAccessString());
            popc_node_log(log);
            asker.callbackResult(*resp);  
         }

         //Write PKI from the request
//         popc_node_log("[VSPSN] WRITE_KEYS_FROM_REQUEST");
         VirtualPOPCSecurityManager psm(_localPSM);
         POPString mainPki(req.getMainPKI());
         POPString initPki(req.getPKI());
         //TODO check if really needed in VS mode
         POPString emptyPOPAppID;
//         sprintf(log, "[VSPSN] init pki %s", initPki.GetString());
         popc_node_log(log);
         psm.addKeyToReqMap(req.getPOPAppId(), req.getUniqueId(),initPki);
         psm.writePKI(emptyPOPAppID, mainPki);
         if(!(sender == GetAccessPoint())){
            psm.writePKI(emptyPOPAppID, initPki);
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
               sprintf(log, "[VSPSN] FORWARD TO DEST;%s", nid.GetString());
	   			popc_node_log(log);
               (*i)->askResourcesDiscovery(req, node_ap, GetAccessPoint(), _psm);
            }
         }
      }
   }
}

// POPCSearchNode's return point to give back the response to the initial node
void VirtSecurePOPCSearchNode::callbackResult(Response resp){
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

   /**
    * ViSaG : clementval
    * Route the PKI to the Main Node
    */
   try{
      VirtualPOPCSecurityManager psm(_localPSM);
      psm.reroutePKIToMain(resp.getPOPAppId(), resp.getFoundNodeInfo().getPKI());
   } catch (...){
      popc_node_log("[VSPSN]ERROR: Can't contact PSM to reroute PKI to the main.");
   }
   if(pt_locker != NULL)
   	sem_post(pt_locker);

}


