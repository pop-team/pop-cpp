/**
 * File : codemgr.ph
 * Author : Tuan Anh Nguyen
 * Description : Declaration of the code manager service
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 */


#ifndef CODEMGR_PH
#define CODEMGR_PH

#include <vector>
#include "service_base.ph"

#define CODE_MAX_STRING_SIZE 1024


struct codedata {
    codedata() {};
    std::string platform;
    std::string codefile;
};

struct codedb {
    codedb() {};
    std::string objname;
    std::vector<codedata> platform;
};

typedef std::vector<codedb> CodeDBArray;

/**
 * @class CodeMgr
 * @brief Parclass : Manage object executables for different platforms, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 * CodeMgr is an application-scope service which provides information about location of a parallel object executable for a specific platform.
 * This service is used by the resource discovery service to acquire information of supported platform of the parallel object.
 * @sa pop_service_base
 */
parclass CodeMgr:
virtual public pop_service_base {
public:
    /** @brief Constructor
     * @param challenge challenge string which will be required on stopping the service
    */
    CodeMgr(const std::string &challenge) @{od.runLocal(true); od.service(true);};
    ~CodeMgr();


    /** @brief  Register code to the CodeMgr service (seq, async)
     * @param objname name of the object
     * @param platform executable platform
     * @param codefile URL or absolute path to the executable
    */
    seq sync void RegisterCode(const std::string &objname, const std::string &platform, const std::string &codefile);


    /** @brief  Query location of object code for a specific platform (seq,sync)
     * @param objname name of the object
     * @param platform executable platform
     * @param codefile stores URL to the executable on success
     * @return Return true if the executable is available
    */
    seq sync int QueryCode(const std::string &objname, const std::string &platform, [out] std::string &codefile);


    /** @brief  Get list of supported platforms for a specific object (seq,sync)
     * @param objname name of the object
     * @param platform stores list of platform separated by a space
     * @return Return number of supported platform stored in platform
    */
    seq sync int GetPlatform(const std::string &objname, [out]  std::string &platform);

    classuid(2);

protected:
    CodeDBArray info;
};


#endif
