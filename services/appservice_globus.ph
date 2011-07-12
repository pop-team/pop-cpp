#include "appservice.ph"
#include "globus_common.h"
#include "globus_gram_client.h"
#include "globus_gsi_credential.h"

#include "globus_gss_assist.h"

struct GlobusMonitor
{
  globus_mutex_t mutex;
  globus_cond_t cond;
  bool done;
  void *appservice;
  char *callback_contact;
};

struct GlobusJob
{
	int Id;
	char *jobcontact;
	int status;
	paroc_accesspoint jobmgr;
};

typedef paroc_array<GlobusJob> GlobusJobArray;


parclass GlobusAppCoreService: public AppCoreService
{
public:
	GlobusAppCoreService(const paroc_string &challenge, bool daemon, const paroc_string &codelocation) @{ od.url(paroc_system::GetHost()); od.executable(codelocation); };
	~GlobusAppCoreService();
	seq sync bool GetUserSubjectName([out] paroc_string &subject);

	seq sync int  SubmitJob(const paroc_string &gramcontact, const paroc_string &objname, int howmany, const paroc_string &platform, const paroc_accesspoint &jobmgr, const paroc_accesspoint &objcallback, const paroc_string &env, [out] int &jobID);

	__hidden bool EndJob(char *jobcontact, int state);
	seq sync bool EndJob(int id, int state);
	virtual void KillAll();

private:
	
	void EndJob(GlobusJob &myjob, int state);

	int Find(int id);
	int Find(char *jobcontact);
	
	bool GenerateJobDescription( const paroc_string &objname, int howmany, const paroc_string &platform, const paroc_accesspoint &jobmgr, 
				     const paroc_accesspoint &objcallback, const paroc_string &env, char *rsl, int n);
	classuid(21);
private:
	char *mysubject;
	GlobusMonitor Monitor;
	pthread_t tid;
	
	GlobusJobArray globusjobs;
	int nextJobID;
};
