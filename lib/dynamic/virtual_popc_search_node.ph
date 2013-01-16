/**
 * File : virtual_popc_search_node.ph
 * Author : Clement Valentin (clementval)
 * Description : Parclass header file of the virtual search node (resources discovery)
 * Creation date : 2010/04/19
 * 
 * Modifications :
 * Author		Date 			Description
 * clementval	2010/11/11  Creation of the virtual version of the PSN
 */

#ifndef _VIRT_PSN_PH
#define _VIRT_PSN_PH

#include "popc_search_node.ph"

using namespace std;

/**
 * @author Valentin Clement
 * The POP-C++ Virtual Search Node (PSN) is in charge of the resources discovery in the GRID when the POP-C++ virtual version is 
 * used. This parallel object is a part of the POP-C++ Global Services.
 */
parclass VirtualPOPCSearchNode : POPCSearchNode {

public:
	//Node's constructore 
	VirtualPOPCSearchNode(const POPString &challenge, bool deamon) @{ od.runLocal(true); od.service(true);};
   
	// Destructor
	~VirtualPOPCSearchNode();

   //Class Unique Identifier
	classuid(1002);

protected:

   //Overwritten methods. Check resources availability
   seq sync bool checkResource(Request req);
};
#endif
