/*
 * The POP-C++ Security Manager (PSM) is in charge of the security of the connections in POP-C++. In its current version, 
 * this security manager is in charge of all the SSH keys management. This parallel object is a part of the POP-C++ Global 
 * Services. The Virtual POP-C++ Security Manager is use only on the Admin Virtual Machine.
 * 
 * File : virtual_popc_security_manager.ph
 * Author : Clement Valentin (clementval)
 * Description : Parclass header file of the security manager for POP-C++ runtime
 * Creation date : 2010/12/06
 * 
 * Modification : 
 * Date        Author      Description
 * 2010/12/06  clementval  First version of this file
 */

#include "popc_security_manager.ph"

#include <map>
#include <string>


using namespace std;

parclass VirtualPOPCSecurityManager : POPCSecurityManager {
public:
   //Define class UID. POP-C++ need
   classuid(16);

   //Virtual Security Manager constructor
	VirtualPOPCSecurityManager(const POPString &challenge, bool deamon) @{ od.runLocal(true); od.service(true); od.service(true);};

   //Virtual Security Manager destructor
   ~VirtualPOPCSecurityManager();

   //Write the PKI on the specific VM
   sync seq virtual void writePKI(POPString popAppId, POPString pki);

   //Save the pki included in the request to be retrive when the VM is prepared
   sync seq void addKeyToReqMap(POPString popAppId, POPString reqID, POPString pki);

   //Retrieve the saved pki from req to be write in the prepared VM
   sync conc POPString getKeyFromReqMap(POPString popAppId, POPString reqID);

   //Reroute a running node PKI to the node having the reference to it
   sync conc void rerouteRef(POPWayback wayToNode, POPString pki, POPString popAppId);

private: 
   //Map containing the saved pki from request   
   map<string, POPString> _req_map;
};
