/**
 * File : popfilemanager.ph
 * Author : Valentin Clement
 * Description : Declaration of the parallel object POPFileManager (POP-C++ Global Services). This object is responsible of the 
 *               parallel file management.
 * Creation date : 2012/04/06
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval	2012/04/06  Creation of this file
 */

#ifndef POPFILEMANAGER_PH_
#define POPFILEMANAGER_PH_

#include "paroc_service_base.ph"

parclass POPFileManager : virtual public paroc_service_base {
public: 
   //POPFileManager constructor
   POPFileManager(const POPString &challenge, bool deamon) @{ od.runLocal(true);};
   
   //POPFileManager destructor   
   ~POPFileManager();
      
   // Management methods
   sync conc bool hasStrip(POPString path);
   sync conc void getMetaData();
   
   
   
   sync conc POPString readData();
   sync conc void writeData();
   

	//Define class uid
   classuid(1021);
private:
   paroc_accesspoint psn;	//direct access to the POPSearchNode
    
};
#endif /* POPFILEMANAGER_PH_ */
