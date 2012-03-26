/**
 * File : virtual_popc_search_node.cc
 * Author : Clement Valentin (clementval)
 * Description : Implementation file of the virtual_search node (resources discovery)
 * Creation date : 2010/11/11
 * 
 * Modifications :
 * Authors		Date			Description
 * clementval	2010/11/11  Creation of the virtual version of the PSN
 */
#include "virtual_popc_search_node.ph"
#include "virtual_jobmgr.ph"

/**
 * ViSaG : clementval
 * Virtual POPCSearchNode's constructor
 * @param challenge  Challenge string used to stop the services
 * @param deamon     If TRUE, the parallel object will run in deamon mode
 */
VirtualPOPCSearchNode::VirtualPOPCSearchNode(const POPString &challenge, bool deamon) : POPCSearchNode(challenge, deamon) {
	popc_node_log("VirtualPOPCSearchNode Created ...");
}

/**
 * ViSaG : clementval
 * Destructor of VirtualPOPCSearchNode
 */
VirtualPOPCSearchNode::~VirtualPOPCSearchNode(){
	popc_node_log("VirtualPOPCSearchNode destroyed ...");
}

/**
 * ViSaG : clementval
 * Overwritten method : check resource with virtual machine. As the JobMgr stores any information about the VMs, the PSN has to 
 * contact him for the resource check
 * @param req Request to be checked
 */
bool VirtualPOPCSearchNode::checkResource(Request req){
   VirtualJobMgr vjm(getJobMgrRef());
   return vjm.checkVM(req);
}


