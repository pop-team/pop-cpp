/**
 * File : popcloner.ph
 * Author : Valentin Clement
 * Description : Declaration of the parallel object POPCloner (POP-C++ Global Services). This object is responsible of the 
 *               VM cloning.
 * Creation date : 2010/11/12
 * 
 * Change Log: 
 * Author		Date			Description
 * clementval	03.25.2012	Creation of this file
 */

#include "paroc_service_base.ph"
#include "paroc_accesspoint.h"
//#include "popfilestrip.h"

#include <list>

parclass POPFileManager : virtual public paroc_service_base {
public:
   classuid(50);   

   //POPCloner constructor
   POPFileManager(const POPString &challenge, bool deamon, POPString host) @{ od.runLocal(true); od.service(true); od.url(host); };
   
   //POPCloner destrcutor   
   ~POPFileManager();
   
   //Create a new strip on this node
   sync seq bool createStrip(POPString abslotuePath);
   
   //Find resource to create strips
   sync conc int findResourcesForStrip(int nb, [in, out, size=nb] paroc_accesspoint* candidate, [in, out, size=nb] POPString* stripNames, POPString stripPrefix);
   
	//Write to strip
	async conc void writeToStrip(POPString stripName, POPString data);
	
	
	async conc void asyncCall1();
	
	async conc void asyncCall2(POPString data);
	
   
   //Save the accesspoint of the POPSearchNode
   sync seq void setPSNAccessPoint(paroc_accesspoint ap);
   
   //Get neighbors to create strips on them 
   sync seq void getNeighborsFromPSN();
   
private:
	paroc_accesspoint psn_ap;
	std::list<paroc_accesspoint> pfm_neighbors;
	
};

int popfile_log(const char *format,...);  //log function for error