/*
 * File : virtual_popc_security_manager.cc
 * Author : Clement Valentin  (clementval)
 * Description :  Implementation file of the virtual security manager for POP-C++ runtime. This implementtation is used only in 
 *                the Virtual version
 * Creation date : 2010/12/06
 * 
 * Modification : 
 * Author      Date        Description
 * clementval  2010/12/06  First version of this file
 */


#include "virtual_popc_security_manager.ph"
#include "virtual_secure_jobmgr.ph"

#include <stdio.h>
#include <stdarg.h>
#include <string>

/** 
 * ViSaG : clementval
 * VirtualPOPCSecurityManager constructor
 * @param challenge  Challenge string used to stop the service
 * @param deamon     If TRUE, the parallel object run as a deamon
 */
VirtualPOPCSecurityManager::VirtualPOPCSecurityManager(const POPString &challenge, bool deamon) : 
   POPCSecurityManager(challenge, deamon){
   
}

/**
 * ViSaG : clementval
 * VirtualPOPCSecurityManager destructor
 */
VirtualPOPCSecurityManager::~VirtualPOPCSecurityManager(){}



/* ################################################### 
 * ##### POPCSecurityManager overwritten methods #####
 * ################################################### */

/**
 * ViSaG : clementval
 * Write a PKI in a VM worker. The Vm is selected with the POPAppID
 * @param popAppId   The POPAppID associated with this PKI
 * @param pki        The PKI to be written
 */
void VirtualPOPCSecurityManager::writePKI(POPString popAppId, POPString pki){
   if(popAppId.Length()<0){
      POPCSecurityManager::writePKI(popAppId, pki);
   } else {
      try{
         VirtSecureJobMgr vsjm(_localJobMgr);
         vsjm.writePKIToVM(popAppId, pki);
      } catch (...){
         popc_security_log("[VPSM] ERROR : Unable to contact VSJM to write the PKI");
      }
   }
}

/**
 * ViSaG : clementval
 * Save the PKI of the request for a POPAppID
 * @param popAppId   The POP Application ID   
 * @param pki        The public key
 */
void VirtualPOPCSecurityManager::addKeyToReqMap(POPString popAppId, POPString reqID, POPString pki){
   sprintf(log, "[VPSM] ADD_KEY_FROM_REQ: %s, %s", reqID.GetString(), popAppId.GetString());     
   popc_security_log(log);
   //Create the combinated key
   string key(popAppId.GetString());
   key.append(reqID.GetString());
   //Insert the key   
   _req_map.insert(pair<string, POPString>(key, pki));
  
}

/**
 * ViSaG : clementval
 * Get the PKI from a request for a POPAppID, ReqID. The key is erased after.
 * @param popAppId   The POP Application ID
 * @return The PKI or an empty POPString
 */
POPString VirtualPOPCSecurityManager::getKeyFromReqMap(POPString popAppId, POPString reqID){
   POPString dummy("");
   if(_req_map.empty()){
      popc_security_log("[VPSM] NO KEY IN MAP");
      return dummy;
   }
   
   //Create the key
   string key(popAppId.GetString());
   key.append(reqID.GetString());
   sprintf(log, "Get keyFromReq %s", key.c_str());
   //Look for the right mapping with the POPAppId
   map<string, POPString>::iterator it;
   for(it = _req_map.begin(); it != _req_map.end(); it++){
      string id = (*it).first;
      //Compare the current VM name with the given VM name (parameter)
      if(id.compare(key) == 0){
         POPString found = (*it).second;
         _req_map.erase(it);
         return found;
      }
   }
   popc_security_log("RETURN DUMMY");
   //If not found, return empty POPString
   return dummy;
}

/**
 * ViSaG : clementval
 * Reroute the PKI of the node running the interface to the node running the object
 * @param wayToNode
 * @param pki
 * @param popAppId
 */
void VirtualPOPCSecurityManager::rerouteRef(POPWayback wayToNode, POPString pki, POPString popAppId){
   //Set the VM public key as the key
   if(strcmp(pki.GetString(), "")==0){
      sprintf(log, "[VPSM] REROUTE_FOR_REF:START:%s", wayToNode.getAsString().GetString());
      popc_security_log(log);
      try{
         sprintf(log, "[VPSM] popAppId %s, _localjobMgr %s", popAppId.GetString(), _localJobMgr.GetAccessString());
         popc_security_log(log);
         VirtSecureJobMgr vsjm(_localJobMgr);
         pki = vsjm.getVMPKI(popAppId);
      } catch(...){
         popc_security_log("[VPSM] ERROR : Can't get VM PKI");
         if(_localJobMgr.IsEmpty())
            popc_security_log("[VPSM] ERROR : JobMgr ref empty");    
         return;  
      }
      popc_security_log(log);
   }

   //If there is no node in the way back, this node is the last node
   if(wayToNode.isEmpty()){
      writePKI(popAppId, pki);
      //sprintf(log, "[VPSM] REROUTE_FOR_REF:WRITE_PKI:%s", pki.GetString());
      sprintf(log, "[VPSM] REROUTE_FOR_REF:WRITE_PKI");
      popc_security_log(log);
   } else {
      POPString nextNode_str = wayToNode.getNextNode();     
      wayToNode.deleteNextNode();
      paroc_accesspoint nextNode_ap;
      nextNode_ap.SetAccessString(nextNode_str);

      try{
         POPCSecurityManager psm(nextNode_ap);
         psm.rerouteRef(wayToNode, pki, popAppId);
         sprintf(log, "[VPSM] REROUTE_FOR_REF:TO:%s", nextNode_str.GetString());
         popc_security_log(log);
      } catch (...){
         sprintf(log, "[VPSM] ERROR : Unable to contact PSM [%s]", nextNode_str.GetString());
         popc_node_log(log);
      }
   }
}


