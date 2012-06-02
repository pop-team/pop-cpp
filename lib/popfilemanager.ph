/**
 * File : popfilemanager.ph
 * Author : Valentin Clement (clementval)
 * Description : Declaration of the parallel object POPFileManager. This object is in charge of POPFile management. 
 * Creation date : 03.25.2012
 * 
 * Change Log: 
 * Author		Date			Description
 * clementval	03.25.2012	Creation of this file
 */
 
#ifndef POPFILEMANAGER_H_INCLUDE
#define POPFILEMANAGER_H_INCLUDE

#include "paroc_service_base.ph"
#include "paroc_accesspoint.h"
#include <list>

parclass POPFileManager : virtual public paroc_service_base {
public:
   classuid(50);   

   //POPFileManager constructor
   POPFileManager(const POPString &challenge, bool deamon, POPString host) @{ od.runLocal(true); od.service(true); od.url(host); };
   
   //POPFileManager destrcutor   
   ~POPFileManager();
   
   //Create a new strip on this node
   sync seq bool createStrip(POPString abslotuePath);
   
   //Find resource to create strips
   sync conc int findResourcesForStrip(int nb, [in, out, size=nb] paroc_accesspoint* candidate, [in, out, size=nb] POPString* stripNames, POPString stripPrefix, bool local);
   
	//Write to strip
	async conc void writeToStrip(POPString stripName, POPString data);
	
	//Write to a remote strip
	async conc void writeToRemoteStrip(POPString stringName, POPString data, paroc_accesspoint ap);

	// Read a block of data from the strip
	sync conc POPString readFromStrip(POPString stripName, long start, long offset);
   
   //Save the accesspoint of the POPSearchNode
   sync seq void setPSNAccessPoint(paroc_accesspoint ap);
   
   //Get neighbors to create strips on them 
   sync seq void getNeighborsFromPSN();
   
private:
	paroc_accesspoint psn_ap;	// Saved access point to the local PSN for resource discovery
	std::list<paroc_accesspoint> pfm_neighbors;	// list of direct neigbors
	
};

int popfile_log(const char *format,...);  //log function for error

#endif /* POPFILEMANAGER_H_INCLUDE_ */ 