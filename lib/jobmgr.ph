/**
 * File : jobmgr.ph
 * Author : Tuan Anh Nguyen
 * Description : Declaration of the parallel object JobMgr (POP-C++ Global Services)
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval	2010/04/19	All code added for the semester project begins with this comment //Added by clementval, ends with 
 *                         //End of add
 * clementval	2010/04/19	All code modified during the semester project begins with //Modified by clementval, ends with 
 *                         //End of modification
 * clementval	2010/04/29	Full functionnal version with the new POPSearchNode in charge of the resource discovery. 
 *                         Biggest change are in the method AllocResource.
 * 								Add new method UnregisterNode, Reserve, GetNodeAccessPoint
 * clementval	2010/05/02	Better distribution of parallel object on discovered ressources
 * Wyssen      2010/08/04  Added the prototypes for the virtual version of POP-C++. All modified code is marked with
 *                         Begining -> ### Added by Wyssen ###
 *                         Ending   -> ### End ###
 */

#ifndef JOBMGR_PH
#define JOBMGR_PH



#include <time.h>
#include <sys/time.h>
#include "paroc_service_base.ph"
#include <timer.h>
#include <paroc_accesspoint.h>
#include <paroc_list.h>
#include "popc_logger.h"


/**
 * ViSaG : clementval 
 */
#include "POPString.h"

//Added by clementval
#include <list>
#include "request.h"
#include "response.h"
#include "explorationList.h"
#include "popc_search_node_info.h"
#include "popc_search_node.ph"

#define TIMEOUT 0;					// Waiting time of the resources discovery algorithm
#define MAXHOP 1000;					// Maximum depth for a discovery request
#define SELFREGISTER_TIMEOUT 84600	//Time before between two self-registration (default one day)
//End

/* ### Added by Wyssen ### */
//#include "ESXWrapper.h"
//#include "WrapperFactory.h"
/* ### End ### */



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
   /**
    * ViSaG : clementval
    * Add the popAppId into the Resources struct
    * Add the reqID into the Resources struct
    */
   POPString popAppId;
   POPString reqID;

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
	POPString  name;
	POPString val;
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
typedef paroc_list<POPString> paroc_list_string;



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
	bool HasContact(const POPString &contact);

	bool GetInfo(const POPString &contact, NodeInfo &info);
	int GetCount();

	bool Update(const POPString &contact, NodeInfo &info);
	bool Remove(const POPString &key);
	bool Add(const POPString &contact, NodeInfo &info);
private:
	int Hash(const POPString &key);

	struct NodeInfoExt
	{
		POPString key;
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
parclass JobMgr : public JobCoreService
{
public:
   /* ViSaG : clementval : Add reference to the PSM */
	JobMgr(bool daemon, [in] const POPString &conf, [in] const POPString &challenge, const POPString &url, 
      const paroc_accesspoint &nodeAccess, const paroc_accesspoint &localPSM) @{ od.url(url); od.runLocal(true); od.service(true);};
   /* End */

	~JobMgr();  //Method ID 11
	
	async seq  virtual void CancelReservation([in, size=howmany] int *req, int howmany); //17
	async seq  void dump();
	async seq void SelfRegister();
	
   //Method to get and set the POPCSecurityManager reference
   async seq void setPSMRef(paroc_accesspoint secmgr);
   
	// Returns information about the job manager : power, jobs, ...
	sync seq virtual int Query([in] const POPString &type, [out] POPString &val); 


	/**
	 * Concurrent method
	 */


	//Global service...
	sync seq virtual int CreateObject(paroc_accesspoint &localservice, const POPString &objname, const paroc_od &od, int howmany, [in, out,size=howmany] paroc_accesspoint *jobcontacts,  int howmany2, [in, out, size=howmany2] paroc_accesspoint *remotejobcontacts); 
	sync conc virtual bool  AllocResource(const paroc_accesspoint &localservice, const POPString &objname, const paroc_od &od, int howmany, [in,out, size=howmany] float *fitness, [in,out, size=howmany] paroc_accesspoint *jobcontacts, [in,out, size=howmany] int *reserveIDs, [in] int requestInfo[3], [in] int trace[MAX_HOPS], [in] int tracesize); 

	async conc void RegisterNode([in] const paroc_accesspoint &url);  

	// Reserve the resource. Add the POPAppID for the reservation
	sync conc virtual int Reserve(const paroc_od &od, float &inoutfitness, POPString popAppId, POPString reqID);
	sync conc virtual int ExecObj(const POPString &objname, const paroc_od &od, int howmany, [in, size=howmany] int *reserveIDs, const paroc_accesspoint &localservice,  [out, size=howmany] paroc_accesspoint *objcontacts);


	
	//Allow the unregistration of a specific node
	async conc void UnregisterNode([in] const paroc_accesspoint &url);
	
   //Method called when an application is finished
   async conc virtual void ApplicationEnd(POPString popAppId, bool initiator);	


	//Return the access point for the local POPCSearchNode parclass
	sync conc paroc_accesspoint GetNodeAccessPoint();
   
   sync conc virtual paroc_accesspoint getPSMRef();
	


	virtual void Start();


   
   

	classuid(15);
protected:
	virtual void Update();
	virtual int Exec(char **arguments, char **env, int &pid, POPString popAppId, POPString reqID);
	virtual int MatchAndReserve(const paroc_od &od, float & fitness);
	virtual bool MatchAndReserve(const paroc_od &od, float *fitness, paroc_accesspoint *jobcontacts, int *reserveIDs, int howmany);
	virtual bool Forward(const paroc_accesspoint &localservice, const POPString &objname, const paroc_od &od, int howmany, float *fitness,       paroc_accesspoint *jobcontacts, int *reserveIDs, int requestInfo[3], int iptrace[MAX_HOPS], int tracesize);

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

	//Added by clementval

	//Access Point of the local POPCSearchNode
	//paroc_accesspoint localNode;
	//End of add

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

   /* ViSaG : clementval */

   paroc_accesspoint _localPSN;  //reference to the local POPCSearchNode
   paroc_accesspoint _localPSM;  //reference to the local POPCSecurityManager
   
private: 
	POPSynchronizer reserveLock;   

};

#endif /* JOBMGR_PH */