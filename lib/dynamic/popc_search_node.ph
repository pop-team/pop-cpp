/**
 * File : popc_search_node.ph
 * Author : Valentin Clement (clementval)
 * Description : Parclass header file of the search node (resources discovery)
 * Creation date : 19/04/2010
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval	2010/04/19	All code added for the semester project begins with this comment //Added by clementval, ends with 
 *                         //End of add
 * clementval	2010/04/19	All code modified during the semester project begins with //Modified by clementval, ends with 
 *                         //End of modification
 * clementval	2010/04/09	Add method and variable to hold the reference of the associated JobMgr.
 * clementval 	2010/05/10	Remove useless constructor and add a constrcutor with challenge string and deamon boolean value. Add an 
 *                         inherotance of the class paroc_service base to transform this parclass in a POPC service.
 * clementval  2010/10/21  All the code added for the ViSaG project is commented with the following signature (ViSaG : clementval)
 * clementval  2010/10/20  Add setter and getter for the PSM reference. Add variable _localPSM
 */


#ifndef _NODE_PH
#define _NODE_PH


#include <time.h>
#include <sys/time.h>

#include <list>
#include <map>
#include <string.h>
#include "request.h"
#include "response.h"
#include "popc_search_node_info.h"
#include <semaphore.h>
#include <fcntl.h>

#include "paroc_service_base.ph"
#include "jobmgr.ph"
#include "timer.h"
#include "paroc_thread.h"
#include "popc_logger.h"


#include <iostream>
#include <unistd.h>
#include <stdarg.h>

#define MAXREQTOSAVE 10		// Maximum number of request to save in the history
#define UNLOCK_TIMEOUT 20	//Timeout to unlock the discovery process is no responses are coming

using namespace std;

/*
 *  Class representing POPCSearchNode to discover resource on the grid, inherite from paroc_service_base
 */
parclass POPCSearchNode : virtual public paroc_service_base {

public :
	//Node's constructore 
	POPCSearchNode(const POPString &challenge, bool deamon) @{ od.runLocal(true); od.service(true);};
   
	// Destructor
	~POPCSearchNode();
	seq sync void setJobMgrRef(const paroc_accesspoint &jobmgrRef);
	conc sync paroc_accesspoint getJobMgrRef();
	seq  sync void setPOPCSearchNodeId(POPString nodeId);
   conc sync POPString getPOPCSearchNodeId();
   seq  sync void setOperatingSystem(POPString operatingSys);
   conc sync POPString getOperatingSystem();
	seq  sync void setPower(float p);
	conc sync float getPower();
   seq  sync void setCpuSpeed(int cpuSpeed);
   conc sync int getCpuSpeed();
   seq  sync void setMemorySize(float memorySize);
   conc sync int getMemorySize();
   seq  sync void setNetworkBandwidth(float networkBandwidth);
   conc sync float getNetworkBandwidth();
   seq  sync void setDiskSpace(int diskSpace);
   conc sync int getDiskSpace();
	seq  sync void setProtocol(POPString prot);
	conc sync POPString getProtocol();
	seq  sync void setEncoding(POPString enc);
	conc sync POPString getEncoding();
   seq sync void setMaxJobs(int maxjobs);
   conc sync int getMaxJobs();

   sync seq POPString getUID();

	// Method allowing adding Neighbor to the node
	seq sync void addNeighbor(POPCSearchNode &node);

	// Method allowing removing Neighbor to the node
   seq sync void removeNeighbor(POPCSearchNode &node);

	// Method to remove all neighbors (allowing clean destruction of node)
	seq sync void deleteNeighbors();

	// Node's entry point to propagate request
	seq async virtual void askResourcesDiscovery(Request req, paroc_accesspoint jobmgr_ac, paroc_accesspoint sender, paroc_accesspoint psm);
	
	seq sync POPString getNeighborsAsString();
        
	// Service's entry point to ressource discovery
	conc sync virtual POPCSearchNodeInfos launchDiscovery([in, out] Request req, int timeout);        

	// Node's return point to give back the response to the initial node
	conc async virtual void callbackResult(Response resp);

   //Unlock the resource discovery when waiting time is set to 0
	conc async void unlockDiscovery(POPString reqid);

   // Reroute the response by the confidence link
   conc async void rerouteResponse(Response resp, const POPWayback wayback);


        


   sync seq void addJob(float power, float memorySize, float bandwidth);
   sync seq void removeJob(float power, float memorySize, float bandwidth, int nbJob);

   //TODO put in Secure PSN when created
   seq sync virtual void setPKI(POPString pk);
   conc sync virtual POPString getPKI();

	classuid(1001);
protected:	
	map<std::string, sem_t*> reqsem;			// Map of semaphores used for null waiting time
	
	int logicalClock;  							// own request's counter
	int sem_logicalClock;						// Logical clock used to name semaphore on Darwin architecture
	POPCSearchNodeInfo nodeInfo;     		// node's information
	list<POPCSearchNode *> neighborsList; 	// node's neighbors list
  	list<POPString> knownRequests; 			// already-asked requests
   map<POPString, POPCSearchNodeInfos> actualReq;     // own actual requests
   POPSynchronizer actualReqSyn;  			// sync. for actual req.
   
   // internal method returning a list of neighbors
   conc sync list<POPString> getNeighbors();
   int psn_currentJobs;
   int psn_maxjobs;
	struct timeval start, end;	//for test purpose

   seq sync virtual bool checkResource(Request req);
private: 
	int getNextSemCounter();
};



#endif
