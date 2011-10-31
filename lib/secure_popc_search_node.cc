/**
 * File : virtual_secure_popc_search_node.cc
 * Author : Clement Valentin (clementval)
 * Description : Implementation file of the Secure POP-C++ Search Node (resources discovery)
 * Creation date : 2010/12/07
 * 
 * Modifications :
 * Authors		Date			Description
 * clementval	2010/12/07  Creation of the virtual version of the PSN
 */
#include "secure_popc_search_node.ph"
#include "secure_jobmgr.ph"
#include "popc_security_manager.ph"
#include "nodethread.h"

using namespace std;

/**
 * ViSaG : clementval
 * Secure POPCSearchNode's constructor
 * @param challenge  Challenge string used to stop the services
 * @param deamon     If TRUE, the parallel object will run in deamon mode
 */
SecurePOPCSearchNode::SecurePOPCSearchNode(const POPString &challenge, 
   bool deamon) : POPCSearchNode(challenge, deamon) {
	popc_node_log("SecurePOPCSearchNode Created ...");
}

/**
 * ViSaG : clementval
 * Destructor of SecurePOPCSearchNode
 */
SecurePOPCSearchNode::~SecurePOPCSearchNode(){
	popc_node_log("SecurePOPCSearchNode destroyed ...");
}

/**
 * ViSaG : clementval
 * Setter for the local POPCSecurityNode reference
 * @param The local reference of the PSM
 */
void SecurePOPCSearchNode::setPSMRef(paroc_accesspoint psm){
   _localPSM = psm;
}

/**
 * ViSaG : clementval
 * Getter for the local POPCSecurityManager reference
 * @return The local reference to the PSM
 */
paroc_accesspoint SecurePOPCSearchNode::getPSMRef(){
   return _localPSM;
}


/**
 * ViSaG : clementval
 * Set the PKI to the node info
 * @param pk   The PKI
 */
void SecurePOPCSearchNode::setPKI(POPString pk){
   nodeInfo.pki=pk;
}

/**
 * ViSaG : clementval
 * Get the PKI to the node info
 * @return The PKI
 */
POPString SecurePOPCSearchNode::getPKI(){
   return nodeInfo.pki;
}




/*
 * OVERWRITTEN METHOD
 */

// Service's entry point for resources discovery. This method will return an
// object of type "POPCSearchNodeInfos" containing information about nodes which fit the
// request
POPCSearchNodeInfos SecurePOPCSearchNode::launchDiscovery(Request req, int timeout){
	gettimeofday(&start, NULL);	//This line is just for test purpose so it can be removed in production release
   //Log
	sprintf(log, "[SPSN] LDISCOVERY;TIMEOUT;%d", timeout);
	popc_node_log(log);

   //Add the main PKI in the request
   POPCSecurityManager psm(_localPSM);
   POPString mainPKI = psm.getMainPKIFromMapping(req.getPOPAppId());
   if(strcmp(mainPKI, "") == 0){
      popc_node_log("SET_SAME_KEY");
      req.setMainPKI(req.getPKI());
   } else {
      popc_node_log("SET_KEY_FROM_MAPPING");
      req.setMainPKI(mainPKI);
   }
   //Add the mapping to the main PSM AP
   psm.addMainAPMapping(req.getPOPAppId(), _localPSM);

   if(req.isEndRequest())
      timeout = 1;
	
	// create a new unique request id with the name of the node and its
	// logical clock. This uniqueId is added to the request
	char uId[MAXREQUNIQUEIDLENGTH];
	sprintf(uId,"%s__%d", getPOPCSearchNodeId().GetString(), logicalClock);
   POPString uniqueId(uId);
	req.setUniqueId(uniqueId);
	logicalClock++;
    
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
		popc_node_log("Unlocker timer started ...");
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
	sprintf(log, "RESULTS;%d", results.getNodeInfos().size());
	popc_node_log(log);
   return results;
}

// POPCSearchNode's entry point to propagate request in the grid
// asker is the node which will receive positiv result
void SecurePOPCSearchNode::askResourcesDiscovery(Request req, paroc_accesspoint node_ap, paroc_accesspoint sender, paroc_accesspoint _psm){
   popc_node_log("[SPSN] Ask resource discovery");
   if(req.isEndRequest()){
      popc_node_log("[SPSN] Recieve application end request");
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
				   sprintf(log, "FORWARD;DEST;%s", nid.GetString());
				   popc_node_log(log);
            	(*i)->askResourcesDiscovery(req, node_ap, GetAccessPoint(), _psm);
            }
         }
      }
      JobMgr jmg(getJobMgrRef());
      jmg.ApplicationEnd(req.getPOPAppId(), false);
   } else {
	   sprintf(log, "[SPSN] ASKRDISCOVERY;ASKER;%s;REQID;%s", node_ap.GetAccessString(), req.getUniqueId().GetString());
	   popc_node_log(log);

      /** 
       * ViSaG : clementval
       * Add the main PKI in the mapping for future resource discovery from this node
       * Add the main PSM AP in the mapping for routing PKI
       */
      POPCSecurityManager psm(_localPSM);
      psm.addMainPKIMapping(req.getPOPAppId(), req.getMainPKI());
      psm.addMainAPMapping(req.getPOPAppId(), _psm);

      // check if the request has already been asked
      list<POPString>::iterator k;
      for(k = knownRequests.begin(); k != knownRequests.end(); k++){
         if(strcmp(k->GetString(),req.getUniqueId().GetString()) == 0){
			   sprintf(log, "ALREADY_ASKED_REQUEST;%s", req.getUniqueId().GetString());
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
	   sprintf(log, "CHECK;%s", (isResourcesOk)?"OK":"FAILED");      
	   popc_node_log(log);
      if(isResourcesOk){
         // If local resources are OK, build the response and give it back to
         // 'asker' node
         Response* resp = new Response(req.getUniqueId(), POPCSearchNodeInfo(nodeInfo), req.getExplorationList(), req.getPOPAppId());
	
	      /* If it's the local node or it's the last node, send directly the answer. Otherwise, send to the next node to reroute 
         the message */
         if(!req.getWayBack().isLastNode()){
            POPString listwb = req.getWayBack().getAsString();
            sprintf(log, "NEED_REROUTE;WAYBACK;%s", listwb.GetString());
      	   popc_node_log(log);
            rerouteResponse(*resp, req.getWayBack());
         } else {
            sprintf(log, "SEND_REP;DEST;%s", node_ap.GetAccessString());
            popc_node_log(log);
            POPCSearchNode asker(node_ap);
            asker.callbackResult(*resp);  
         }

         //Add main PKI
         popc_node_log("ADD_KEYS_FROM_REQUEST");
         POPCSecurityManager psm(_localPSM);
         POPString mainPki(req.getMainPKI());
         POPString initPki(req.getPKI());
         psm.writePKI(req.getPOPAppId(), mainPki);
         if(!(sender == GetAccessPoint())){
            psm.writePKI(req.getPOPAppId(), initPki);
         }
      }
       
         // Continue the propagation if more hops are allowed. It continues if the
         // max hops is zero to avoid counting "initial node" discovery.
	      if(req.getMaxHops() >= 0 || req.getMaxHops() == UNLIMITED_HOPS){
            list<POPCSearchNode *>::iterator i;
            // check if the local neighbors are already asked with the originally 
            // received exploration list
            req.addNodeToWb(getPOPCSearchNodeId());
            for(i = neighborsList.begin(); i != neighborsList.end(); i++){
               if(!oldEL.isIn((*i)->getPOPCSearchNodeId())){
	   			   POPString nid;
	   			   nid = (*i)->getPOPCSearchNodeId();
	   			   sprintf(log, "FORWARD;DEST;%s", nid.GetString());
	   			   popc_node_log(log);
               	(*i)->askResourcesDiscovery(req, node_ap, GetAccessPoint(), _psm);
               }
            }
         }
   }
}

// POPCSearchNode's return point to give back the response to the initial node
void SecurePOPCSearchNode::callbackResult(Response resp){
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
	sprintf(log, "RESP;REQID;%s;SENDER;%s;TIME;START;%ld;END;%ld;DIFF;%ld", resp.getReqUniqueId().GetString(), 
      dni.nodeId.GetString(), msec_start, msec_end, diff);
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
	sem_post(pt_locker);


   /**
    * ViSaG : clementval
    * Route the PKI to the Main Node
    */
   POPCSecurityManager psm(_localPSM);
   psm.reroutePKIToMain(resp.getPOPAppId(), resp.getFoundNodeInfo().getPKI());
}


