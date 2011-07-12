#ifndef JOBMGR_PH
#define JOBMGR_PH
#include <time.h>


#include "paroc_service_base.ph"

#include <timer.h>
#include <paroc_accesspoint.h>
#include <paroc_list.h>


#define PAUSE_FORWARD_TIMEOUT 300

#define MAX_CONTACT_LENGTH 64

#define DEFAULT_PORT "2711"
#define DUMP_PATH "/tmp"

#define MAX_HEURISTICS 200

#define SLEEP_TIME_ON_ERROR 120

#define MAX_HOPS 20

#define HASH_SIZE 101

#define NODE_STATIC -1
#define NODE_LEARNT 0
#define NODE_REGISTERED 2

struct Resources
{
	int Id;
	float flops;
	float mem;
	float bandwidth;
	float walltime;

	time_t start;
	paroc_accesspoint contact;
	paroc_accesspoint appservice;
};


struct NodeInfo
{
	double heuristic;
	int id;
	double stoptime;
	bool fixnode;
	int nodetype;
};

struct PauseInfo
{
	double until_time;
	paroc_accesspoint app;
};

struct HostInfo
{
	paroc_string  name;
	paroc_string val;
	HostInfo & operator = (const HostInfo &t)
	{
		name=t.name;
		val=t.val;
		return *this;
	};
};

struct RequestTrace
{
	int requestID[3];
	double timestamp;
};


typedef paroc_list<HostInfo> HostInfoDB;
typedef paroc_list<NodeInfo> NodeInfoList;
typedef paroc_list<paroc_string> paroc_list_string;



typedef paroc_list<Resources> ResourceList;
typedef paroc_list<PauseInfo> PauseList;

typedef paroc_list<RequestTrace> TraceList;


/**
 * @class NodeInfoMap
 * @brief (to be written), used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 */
class NodeInfoMap
{
public:
	NodeInfoMap();
//Manipulate neighbor nodes (thread safe)
	void GetContacts(paroc_list_string &contacts);
	bool HasContact(const paroc_string &contact);

	bool GetInfo(const paroc_string &contact, NodeInfo &info);
	int GetCount();

	bool Update(const paroc_string &contact, NodeInfo &info);
	bool Remove(const paroc_string &key);
	bool Add(const paroc_string &contact, NodeInfo &info);
private:
	int Hash(const paroc_string &key);

	struct NodeInfoExt
	{
		paroc_string key;
		NodeInfo data;
	};
	paroc_list<NodeInfoExt> map[HASH_SIZE];
	int keycount;
	paroc_mutex maplock;
};

/**
 * @class JobMgr
 * @brief Parclass : Manages the execution of jobs, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 * @ingroup runtime
 */
parclass JobMgr:public JobCoreService
{
public:
	JobMgr(bool daemon, [in] const paroc_string &challenge, const paroc_string &url) @{ od.url(url); od.runLocal(true);};
	JobMgr(bool daemon, [in] const paroc_string &conf, [in] const paroc_string &challenge, const paroc_string &url) @{ od.url(url); od.runLocal(true);} ;

	~JobMgr();

	conc async void RegisterNode([in] const paroc_accesspoint &url);

	/**
	 * @brief Returns information about the job manager : power, jobs, ...
	 * @param type input
	 * @param val output
	 */
	sync seq virtual int Query([in] const paroc_string &type, [out] paroc_string &val);

//Global service...
	sync conc virtual int CreateObject(const paroc_accesspoint &localservice, const paroc_string &objname, const paroc_od &od, int howmany, [out,size=howmany] paroc_accesspoint *jobcontacts);



	sync conc virtual bool  AllocResource(const paroc_accesspoint &localservice, const paroc_string &objname, const paroc_od &od, int howmany, [in,out, size=howmany] float *fitness, [in,out, size=howmany] paroc_accesspoint *jobcontacts, [in,out, size=howmany] int *reserveIDs, [in] int requestInfo[3], [in] int trace[MAX_HOPS], [in] int tracesize);

	seq async void CancelReservation([in, size=howmany] int *req, int howmany);

	conc sync virtual int ExecObj(const paroc_string &objname, const paroc_od &od, int howmany, [in, size=howmany] int *reserveIDs, const paroc_accesspoint &localservice,  [out, size=howmany] paroc_accesspoint *objcontacts);

	seq async void dump();

	virtual void Start();

	async void SelfRegister();

	classuid(15);
protected:
	virtual void Update();
	virtual int Exec(char **arguments, char **env, int &pid);
	virtual int MatchAndReserve(const paroc_od &od, float & fitness);
	virtual bool MatchAndReserve(const paroc_od &od, float *fitness, paroc_accesspoint *jobcontacts, int *reserveIDs, int howmany);
	virtual bool Forward(const paroc_accesspoint &localservice, const paroc_string &objname, const paroc_od &od, int howmany, float *fitness, paroc_accesspoint *jobcontacts, int *reserveIDs, int requestInfo[3], int iptrace[MAX_HOPS], int tracesize);

	virtual bool MatchUser(const paroc_accesspoint &localservice);

	virtual void Pause(const paroc_accesspoint &app, int duration);
	virtual bool CheckPauseList(const paroc_accesspoint &app);

	bool AddRequest(int reqId[3]);

	bool AddTrace(int trace[MAX_HOPS], int &tracesize);
	bool NodeInTrace(int trace[MAX_HOPS], int tracesize, paroc_accesspoint &contact);


	bool ObjectAlive(paroc_accesspoint &t);
	Resources* VerifyReservation(int reserveId, bool updatetime);
	bool ValidateReservation(int id, const paroc_accesspoint &objcontact, const paroc_accesspoint &appserv);
	bool ReleaseJob(int id);

	HostInfoDB info;

	NodeInfoMap neighbors;


	TraceList tracelist;
	int requestCounter;


	int dynamicnodes; //number of current nodes that are dynamically updated
	int maxdynamicnodes; //max number of dynamic updated nodes

	ResourceList jobs;

	int maxjobs;
	Resources available;
	Resources limit;
	Resources total;


	int myjobs;
	int counter;

	int serviceID[2]; //pair (IP,port) at most

	int myPID;

	int reserve_timeout;
	int alloc_timeout;

	int localuid;

	Timer service_timer;
	paroc_accesspoint_list parents;

	PauseList pause_apps;

	bool modelearn;
};

int paroc_service_log(const char *format,...);

#endif //JOBMGR_PH

