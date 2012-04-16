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

parclass POPFileManager : virtual public paroc_service_base {
public:
   classuid(50);   

   //POPCloner constructor
   POPFileManager(const POPString &challenge, bool deamon, POPString host) @{ od.runLocal(true); od.service(true); od.url(host); };
   
   //POPCloner destrcutor   
   ~POPFileManager();
   
   //Create a new strip on this node
   bool createStrip();
   
   sync conc void findResourcesForStrip(int nb);
   
	//Write to strip
	async conc void writeToStrip(POPString stripName, POPString data);
   
   //Save the accesspoint of the POPSearchNode
   sync seq void setPSNAccessPoint(paroc_accesspoint ap);
   
private:
	paroc_accesspoint psn_ap;
};

int popfile_log(const char *format,...);  //log function for error