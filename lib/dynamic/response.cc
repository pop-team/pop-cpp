/**
 * File : response.cc
 * Author : Valentin Clement (clementval)
 * Description : Implementation of the response object. response is used for the resource discovery
 * Creation date : 2010/04/19
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval	2010/04/19	All code added for the semester project begins with this comment //Added by clementval, ends with //End of add
 * clementval	2010/04/19	All code modified during the semester project begins with //Modified by clementval, ends with //End of modification
 */

#include "response.h"
#include <iostream>
#include <unistd.h>

// default constructor. Not directly used
Response::Response(){}

// Constructor with all response's information
Response::Response(POPString reqUniqueId,
                   POPCSearchNodeInfo foundNodeInfo,
                   ExplorationList finalExplorationList,
                   POPString appid){
   // save the params
   _reqUniqueId = reqUniqueId;
   _foundNodeInfo=foundNodeInfo;
   _finalExplorationList = finalExplorationList;
   _appid = appid;
}

// Destructor
Response::~Response(){
}

// method used to pass the object in the grid.
void Response::Serialize(POPBuffer &buf, bool pack){
   if(pack){ // marshalling
      // marshall request's uniqueId
      buf.Pack(&_reqUniqueId, 1);
      buf.Pack(&_appid, 1);
      // marshall the found node's 'NodeInfo'
      _foundNodeInfo.Serialize(buf, true);
        
      // marshall the exploration list
      _finalExplorationList.Serialize(buf, true);

   }else{ // unmarshalling
      buf.UnPack(&_reqUniqueId ,1);
      buf.UnPack(&_appid, 1);

      // unmarshall the found node's 'NodeInfo'
      _foundNodeInfo.Serialize(buf, false);
        
      // unmarshall the exploration list
      _finalExplorationList.Serialize(buf, false);



   }
}

// Get the request's uniqueId
POPString Response::getReqUniqueId(){
    return _reqUniqueId;
}


// Get the found node's 'NodeInfo'
POPCSearchNodeInfo Response::getFoundNodeInfo(){
    return _foundNodeInfo;
}

// Get the application services access point
POPString Response::getPOPAppId(){
   return _appid;
}


