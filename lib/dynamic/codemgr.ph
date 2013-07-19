/**
 * File : codemgr.ph
 * Author : Tuan Anh Nguyen
 * Description : Declaration of the code manager service
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 */


#ifndef CODEMGR_PH
#define CODEMGR_PH

#include "paroc_array.h"
#include "paroc_service_base.ph"

typedef char string256[256];
struct codedata
{
	codedata() {};
	string256 platform;
	string256 codefile;
};

struct codedb
{
	codedb() {};
	string256 objname;
	paroc_array<codedata> platform;
};

typedef paroc_array<codedb> CodeDBArray;

/**
 * @class CodeMgr
 * @brief Parclass : Manage object executables for different platforms, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 * CodeMgr is an application-scope service which provides information about location of a parallel object executable for a specific platform.
 * This service is used by the resource discovery service to acquire information of supported platform of the parallel object.
 * @sa paroc_service_base
 */
parclass CodeMgr: virtual public paroc_service_base
{
public:
	/** @brief Constructor
	 * @param challenge challenge string which will be required on stopping the service
	*/
	CodeMgr(const POPString &challenge) @{od.runLocal(true); od.service(true);};
	~CodeMgr();


	/** @brief  Register code to the CodeMgr service (seq, async)
	 * @param objname name of the object
	 * @param platform executable platform
	 * @param codefile URL or absolute path to the executable
	*/
	seq sync void RegisterCode(const POPString &objname, const POPString &platform, const POPString &codefile);


	/** @brief  Query location of object code for a specific platform (seq,sync)
	 * @param objname name of the object
	 * @param platform executable platform
	 * @param codefile stores URL to the executable on success
	 * @return Return true if the executable is available
	*/
	seq sync int QueryCode(const POPString &objname, const POPString &platform, [out] POPString &codefile);


	/** @brief  Get list of supported platforms for a specific object (seq,sync)
	 * @param objname name of the object
	 * @param platform stores list of platform separated by a space
	 * @return Return number of supported platform stored in platform
	*/
	seq sync int GetPlatform(const POPString &objname, [out]  POPString &platform);

	classuid(2);

protected:
	CodeDBArray info;
};


#endif
