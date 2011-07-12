#ifndef REMOTELOG_H
#define REMOTELOG_H

#include "paroc_service_base.ph"

/**
 * @class RemoteLog
 * @brief Parclass : allow remote object to "printf" to local console, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 * RemoteLog is an application-scope service which allows remote objects to send back message to the user's console.
 */
parclass RemoteLog: virtual public paroc_service_base
{
public:

	/** @brief Constructor
	 * @param challenge challenge string which will be required on stopping the service
	*/
	RemoteLog([in] const paroc_string &challenge) @{ od.runLocal(true);};
	~RemoteLog();

	/** @brief Write a message to the user's console
	 * @param info the user message (null terminated string)
	*/
	async seq void Log([in] const paroc_string &info);

	classuid(3);
};

#endif

