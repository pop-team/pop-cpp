/**
 * File : popcloner.ph
 * Author : Valentin Clement
 * Description : Declaration of the parallel object POPCloner (POP-C++ Global Services). This object is responsible of the 
 *               VM cloning.
 * Creation date : 2010/11/12
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval	2010/11/12  Creation of this file
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
   bool createStrip(POPString abslotuePath);
   
   //Find resource to create strips
   sync conc bool findResourcesForStrip(int nb, [in, out, size=nb] paroc_accesspoint* candidate);
   
	//Write to strip
	async conc void writeToStrip(POPString stripName, POPString data);
   
   //Save the accesspoint of the POPSearchNode
   sync seq void setPSNAccessPoint(paroc_accesspoint ap);
   
   //Get neighbors to create strips on them 
   sync seq void getNeighborsFromPSN();
   
private:
	paroc_accesspoint psn_ap;
	std::list<paroc_accesspoint> pfm_neighbors;
	
};

int popfile_log(const char *format,...);  //log function for error