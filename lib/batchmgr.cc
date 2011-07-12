/*
AUTHORS: Laurent Winkler

DESCRIPTION: Simple manager for a batch environment
 */
#include "batchmgr.ph"

BatchMgr::BatchMgr(const paroc_string &challenge): paroc_service_base(challenge)
{
	nodeCount=0;
}
BatchMgr::~BatchMgr()
{
}

int BatchMgr::NextNode()
{
	// Return the next node for batch object execution.
	// We start with 1, since the main runs on node 0.
	nodeCount++;
	return nodeCount;
}

//@pack(BatchMgr);