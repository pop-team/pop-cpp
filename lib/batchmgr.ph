/**
 * File : batchmgr.cc
 * Author : Laurent Winkler
 * Description : Declaration of the simple manager for a batch environment
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 */

#ifndef BATCHMANAGER_H
#define BATCHMANAGER_H

#include "paroc_service_base.ph"

/**
 * @class BatchMgr
 * @brief Parclass : Simple manager for a batch environment, used by POP-C++ runtime.
 * @author Laurent Winkler
 * @ingroup runtime
 * BatchMgr's purpose is to provide an object counter for the node attribution in a batch environment.
 * (see also popcjob.* and popcobjrun.* scripts)
 */
parclass BatchMgr: virtual public paroc_service_base
{
public:
	classuid(6);
	/** @brief Constructor
	 * @param challenge challenge string which will be required on stopping the service
	 */
	BatchMgr([in] const POPString &challenge) @{ od.runLocal(true); od.service(true);};
	~BatchMgr();

	/** @brief Increase the node counter and returns the value
	 * @return current node
	 */
	sync seq int NextNode();

private :
	int nodeCount;
};

#endif

