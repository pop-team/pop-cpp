#ifndef JOBMGR_GLOBUS_PH
#define JOBMGR_GLOBUS_PH

#include "jobmgr.ph"

#include "globus_gram_client.h"
#include "globus_gss_assist.h"

parclass GlobusJobMgr: public JobMgr
{
public:
	GlobusJobMgr(bool daemon, const paroc_string &conf, const paroc_string &challenge, const paroc_string &url) @{ od.url(url); od.runLocal(true);};
	~GlobusJobMgr();

	virtual int ExecObj(const paroc_string  &objname, int howmany, int *reserveIDs, const paroc_accesspoint &localservice, paroc_accesspoint *objcontacts);


	classuid(30);
protected:
	virtual bool MatchUser(paroc_accesspoint &localservice);
private:

	paroc_string globus_gram;
	paroc_string gridmap;
};


#endif
