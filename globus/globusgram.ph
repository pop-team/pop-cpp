#include "appservice.ph"

parclass GlobusGram: public paroc_service_base
{
public:
	GlobusGram();
	~GlobusGram();

	seq sync bool GetUserSubjectName([out] paroc_string &subject);

	seq sync int  SubmitJob(const paroc_string &gramcontact, const paroc_string &objname, int howmany, const paroc_string &platform, const paroc_accesspoint &jobmgr, const paroc_accesspoint &objcallback, const paroc_string &env);

private:

	bool GenerateJobDescription( const paroc_string &objname, int howmany, const paroc_string &platform, const paroc_accesspoint &jobmgr,
								 const paroc_accesspoint &objcallback, const paroc_string &env, paroc_string &rsl);

	bool GenerateWSJobDescription( const paroc_string &objname, int howmany, const paroc_string &platform, const paroc_accesspoint &jobmgr,
								   const paroc_accesspoint &objcallback, const paroc_string &env, paroc_string &jobdesc);
	classuid(21);
private:
	paroc_string mysubject;

};
