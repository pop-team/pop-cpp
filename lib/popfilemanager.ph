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

parclass POPFileManager : virtual public paroc_service_base {
public:
   
   //POPCloner constructor
   POPFileManager(const POPString &challenge, bool deamon) @{ od.runLocal(true);};
   
   //POPCloner destrcutor   
   ~POPFileManager();
   
   classuid(1021);
};