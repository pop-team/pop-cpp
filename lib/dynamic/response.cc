/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of the response object. response is used for the resource discovery.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_ResourceDiscoveryResponse instead of Response
 */

#include "pop_response.h"
#include <iostream>
#include <unistd.h>

// default constructor. Not directly used
Response::Response() {
}

// Constructor with all response's information
Response::Response(std::string reqUniqueId, POPCSearchNodeInfo foundNodeInfo, ExplorationList finalExplorationList,
                   std::string appid) {
    // save the params
    _reqUniqueId = reqUniqueId;
    _foundNodeInfo = foundNodeInfo;
    _finalExplorationList = finalExplorationList;
    _appid = appid;
}

// Destructor
Response::~Response() {
}

// method used to pass the object in the grid.
void Response::Serialize(POPBuffer& buf, bool pack) {
    if (pack) {  // marshalling
        // marshall request's uniqueId
        buf.Pack(&_reqUniqueId, 1);
        buf.Pack(&_appid, 1);
        // marshall the found node's 'NodeInfo'
        _foundNodeInfo.Serialize(buf, true);

        // marshall the exploration list
        _finalExplorationList.Serialize(buf, true);

    } else {  // unmarshalling
        buf.UnPack(&_reqUniqueId, 1);
        buf.UnPack(&_appid, 1);

        // unmarshall the found node's 'NodeInfo'
        _foundNodeInfo.Serialize(buf, false);

        // unmarshall the exploration list
        _finalExplorationList.Serialize(buf, false);
    }
}

// Get the request's uniqueId
std::string Response::getReqUniqueId() {
    return _reqUniqueId;
}

// Get the found node's 'NodeInfo'
POPCSearchNodeInfo Response::getFoundNodeInfo() {
    return _foundNodeInfo;
}

// Get the application services access point
std::string Response::getPOPAppId() {
    return _appid;
}
