/**
 * File : secure_popc_search_node.ph
 * Author : Clement Valentin (clementval)
 * Description : Parclass header file of the secure search node (resources discovery)
 * Creation date : 2010/04/19
 * 
 * Modifications :
 * Author		Date 			Description
 * clementval	2010/11/11  Creation of the virtual version of the PSN
 */

#ifndef _SECURE_PSN_PH
#define _SECURE_PSN_PH

#include "popc_search_node.ph"

/**
 * @author Valentin Clement
 * The POP-C++ Secure Search Node (PSN) is in charge of the resources discovery in the GRID when the POP-C++ virtual version is 
 * used. This parallel object is a part of the POP-C++ Global Services.
 */
parclass SecurePOPCSearchNode : public POPCSearchNode {

public:
	//Node's constructore 
	SecurePOPCSearchNode(const POPString &challenge, bool deamon) @{ od.runLocal(true); od.service(true);};
   
	// Destructor
	~SecurePOPCSearchNode();
   
   //Getter and Setter for the Security Manager reference
   sync seq void setPSMRef(paroc_accesspoint psm);
   sync conc paroc_accesspoint getPSMRef();

   //Getter and Setter for the PKI
   seq sync void setPKI(POPString pk);
   conc sync POPString getPKI();


   /*
    * Overwritten method
    */

   // Service's entry point to ressource discovery
	conc sync virtual POPCSearchNodeInfos launchDiscovery(Request req, int timeout);        

	// Node's entry point to propagate request
	seq async virtual void askResourcesDiscovery(Request req, paroc_accesspoint jobmgr_ac, paroc_accesspoint sender, paroc_accesspoint psm);
        
	// Node's return point to give back the response to the initial node
	conc async virtual void callbackResult(Response resp);
   
   //Class Unique Identifier
	classuid(1010);

protected:
   //Reference to the local Security Manager
   paroc_accesspoint _localPSM;  

};
#endif


   
