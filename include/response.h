/* 
UPDATES : 
Authors		Date			Comment
clementval	2010/04/19	All code added for the semester project begins with this comment //Added by clementval, ends with //End of add
clementval	2010/04/19	All code modified during the semester project begins with //Modified by clementval, ends with //End of modification*/

#ifndef _RESPONSE_H
#define _RESPONSE_H
#include "../include/paroc_string.h"
#include "../include/paroc_base.h"
#include "explorationList.h"
#include "popc_search_node_info.h"

/*
 *  Class representing a response of resource discovery. This class must
 *  inherit from POPBase to be passed in the network.
 */
class Response : public POPBase{
   public :
      // default constructor. Needed by POPC system
      Response();
        
      // constructor used to set all information about the response
      Response(paroc_string reqUniqueId, POPCSearchNodeInfo foundNodeInfo, ExplorationList finalExplorationList, paroc_string appid);
        
      // destructor
      ~Response();
        
      // Inherited method to serialize the object
      virtual void    Serialize(POPBuffer &buf, bool pack);
        
      // return the uniqueId of the request
      paroc_string    getReqUniqueId();
      
      // return the response's 'nodeInfo' object
      POPCSearchNodeInfo        getFoundNodeInfo();

      paroc_string getPOPAppId();

   private :
      paroc_string _reqUniqueId;             //indicate request's uniqueId
      paroc_string _appid;                   //Application services access point
      POPCSearchNodeInfo _foundNodeInfo;     //found node's 'NodeInfo'
      ExplorationList _finalExplorationList; //exploration list to found node
         
};

#endif
