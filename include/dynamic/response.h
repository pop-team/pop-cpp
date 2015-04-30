/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author -
 * @date 2010/04/19
 * @brief Response class declaration used in the resource discovery algorithm
 *
 *
 * UPDATES :
 * Authors      Date            Comment
 * clementval   2010/04/19  All code added for the semester project begins with this comment //Added by clementval, ends
 *with //End of add
 * clementval   2010/04/19  All code modified during the semester project begins with //Modified by clementval, ends
 *with //End of modification*/

#ifndef _RESPONSE_H
#define _RESPONSE_H

#include "pop_base.h"
#include "explorationList.h"
#include "pop_search_node_info.h"

/*
 *  Class representing a response of resource discovery. This class must
 *  inherit from POPBase to be passed in the network.
 */
class Response : public POPBase {
public:
    // default constructor. Needed by POPC system
    Response();

    // constructor used to set all information about the response
    Response(std::string reqUniqueId, POPCSearchNodeInfo foundNodeInfo, ExplorationList finalExplorationList,
             std::string appid);

    ~Response();

    // Inherited method to serialize the object
    virtual void Serialize(POPBuffer& buf, bool pack);

    // return the uniqueId of the request
    std::string getReqUniqueId();

    // return the response's 'nodeInfo' object
    POPCSearchNodeInfo getFoundNodeInfo();

    std::string getPOPAppId();

private:
    std::string _reqUniqueId;  // indicate request's uniqueId
    std::string _appid;  // Application services access point
    POPCSearchNodeInfo _foundNodeInfo;  // found node's 'NodeInfo'
    ExplorationList _finalExplorationList;  // exploration list to found node
};

#endif
