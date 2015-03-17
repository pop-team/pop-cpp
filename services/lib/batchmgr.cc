/**
 * File : batchmgr.cc
 * Author : Laurent Winkler
 * Description : Simple manager for a batch environment
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 */

#include "batchmgr.ph"

BatchMgr::BatchMgr(const std::string &challenge): paroc_service_base(challenge), nodeCount(0) {
    //Nothing else to init
}

int BatchMgr::NextNode() {
    // Return the next node for batch object execution.
    // We start with 1, since the main runs on node 0.
    return ++nodeCount;
}
