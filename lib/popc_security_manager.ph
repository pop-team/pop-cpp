/**
 * File : popc_security_manager.ph
 * Author : Valentin Clement (clementval)
 * Description : Parclass header file of the security manager for POP-C++ runtime
 * Creation date : 2010/10/19
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval  2010/10/19  First version of this file
 * clementval  2010/10/21  All the code added for the ViSaG project is commented with the following signature (ViSaG : clementval)
 * clementval  2010/10/27  Implement the PKI rerouting for the reference passing
 */


#ifndef _POPC_SECURITY_MANAGER_PH
#define _POPC_SECURITY_MANAGER_PH


//Includes section
#include "paroc_service_base.ph"
#include "paroc_accesspoint.h"
#include "popwayback.h"
#include <map>



/**
 * ViSaG : clementval
 * POPCSecurityManager class declaration. This parallel class is executed as a POP-C++ Global Service. Its main function is to 
 * manage all the security issues for the SSH tunneling implementation in POP-C++.
 * @author clementval
 */
parclass POPCSecurityManager : virtual public paroc_service_base {
public:
   //Define class UID. POP-C++ need
   classuid(15);

   //Security Manager constructor
	POPCSecurityManager(const POPString &challenge, bool deamon) @{ od.runLocal(true); od.service(true); };

   //Security Manager destructor
   ~POPCSecurityManager();


   //Setter for the local JobMgr reference
   sync seq void setJobMgrRef(paroc_accesspoint jobmgr);
   
   //Getter for the local JobMgr reference
   sync conc paroc_accesspoint getJobMgrRef();   
   
   //Setter for the local PSN reference
   sync seq void setPSNRef(paroc_accesspoint psn);

   //Getter for the local PSN reference
   sync conc paroc_accesspoint getPSNRef();

   //Write the public key in the authorized_keys file if this key is not already in
   sync seq virtual void writePKI(POPString popAppId, POPString pki);

   //Return the public key of the local node
   sync conc POPString getLocalPKI();

   //init the SSH mode
   sync mutex void initSSHMode();

   //return the main PKI of the node running the main of this POP-C++ application
   sync seq POPString getMainPKIFromMapping(POPString popappid);

   //Get the access point of the Main node from a specific POPAppId
   sync seq paroc_accesspoint getMainAPFromMapping(POPString popappid);

   //Add a mapping between a POPAppId and a main PKI
   async seq void addMainPKIMapping(POPString popappid, POPString mainPKI);

   //Add a mapping between a POPAppId and an access point to the main of a POP-C++ application
   async seq void addMainAPMapping(POPString popappid, paroc_accesspoint ap);

   //Reroute a node PKI too the main node
   async conc void reroutePKIToMain(POPString popappid, POPString pki);

   //Reroute a running node PKI to the node having the reference to it
   sync conc virtual void rerouteRef(POPWayback wayToNode, POPString pki, POPString popAppId);





protected:
   int popc_security_log(const char *log);	//write log in file
   char log[600];	                           //buffer for log

   paroc_accesspoint _localJobMgr;  //reference to the local JobMgr
   paroc_accesspoint _localPSN;     //reference to the local POPCSearchNode
   POPString _localPublicKey;       //contains the local SSH public key


   //Mapping between the POPAppId and the Access Point of the initiator of the resource discovery
   std::map<POPString, paroc_accesspoint> _initiatorMapping;   

   //Mapping between the POPAppId and the main node public key
   std::map<POPString, POPString> _mainPKIMapping;


   //List of all current PKI in the authorized_keys file
   std::list<POPString> _localPublicKeysList;
   
   




   
  
};

#endif
