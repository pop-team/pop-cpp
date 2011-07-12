#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
//#include <netdb.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
//#include <arpa/inet.h>
#include <assert.h>
#include "codemgr.ph"
#include <sys/times.h>
#include "timer.h"
#include <ctype.h> 
#include <pwd.h>

#include "jobmgr.ph"
#include "priolist.h"
#include "paroc_thread.h"
#include "paroc_combox_socket.h"

#define min(a,b) ((a)<(b) ? (a) : (b))

class paroc_timerthread: public paroc_thread
{
 public:
  paroc_timerthread(int parent_update, int service_timeout, IMPLEMENT_TYPE(JobMgr) *myjobmgr);
  virtual void start();
private:
  int parent_update;
  int service_timeout;
  IMPLEMENT_TYPE(JobMgr) *jobmgr;  
};

paroc_timerthread::paroc_timerthread(int myparent_update, int myservice_timeout, IMPLEMENT_TYPE(JobMgr) *myjobmgr): paroc_thread(true)
{
  parent_update=myparent_update;
  service_timeout=myservice_timeout;
  jobmgr=myjobmgr;
}

void paroc_timerthread::start()
{
  if ((parent_update<=0 && service_timeout<=0) || jobmgr==NULL) return;
  while (1)
    {
      int nextwakeup;
      bool updateaction;

      if (service_timeout<=0 ||  parent_update< service_timeout) 
	{
	  updateaction=true;
	  nextwakeup=parent_update;
	  if (service_timeout>parent_update) service_timeout-=parent_update;
	}
      else 
	{
	  updateaction=false;
	  nextwakeup=service_timeout;
	}

      while ((nextwakeup=sleep(nextwakeup))>0);
      if (updateaction) jobmgr->SelfRegister();
      else _exit(1);
    }
}

//CLASS NEIGHBOR NODE: IMPLEMENT THREAD-SAFE NEIGHBOR NODE ACCESS BASED ON KEYS
NodeInfoMap::NodeInfoMap()
{
  keycount=0;
}

void NodeInfoMap::GetContacts(paroc_list_string &contacts)
{
  contacts.RemoveAll();
  paroc_list<double> h;

  maplock.lock();;
  for (int i=0;i<HASH_SIZE;i++)
    {
      paroc_list<NodeInfoExt> &node=map[i];
      POSITION pos=node.GetHeadPosition();
      while (pos!=NULL) 
	{
	  NodeInfoExt &t=node.GetNext(pos);
	  double heuristic=t.data.heuristic;

	  POSITION hpos=h.GetHeadPosition();
	  POSITION cpos=contacts.GetHeadPosition();
	  while (hpos!=NULL)
	    {
	      POSITION old=hpos;
	      double &tmp=h.GetNext(hpos);
	      if (tmp>=heuristic)
		{
		  contacts.InsertBefore(cpos, t.key);
		  h.InsertBefore(old, heuristic);
		  break;
		} 
	      contacts.GetNext(cpos);
	    }
	  if (cpos==NULL) 
	    {
	      contacts.AddTail(t.key);
	      h.AddTail(heuristic);	      
	    }
	}
    }

  maplock.unlock();
}

bool NodeInfoMap::HasContact(const paroc_string &contact)
{
  int i=Hash(contact);
  paroc_list<NodeInfoExt> &node=map[i];
  bool ret=false;

  maplock.lock();

  POSITION pos=node.GetHeadPosition();
  while (pos!=NULL) 
    {
      NodeInfoExt &t=node.GetNext(pos);
      if (paroc_utils::SameContact(t.key, contact))
	{
	  ret=true;
	  break;
	}
    }
  maplock.unlock();
  return ret;
}

bool NodeInfoMap::GetInfo(const paroc_string &contact, NodeInfo &info)
{
  int i=Hash(contact);
  maplock.lock();
  paroc_list<NodeInfoExt> &node=map[i];
  POSITION pos=node.GetHeadPosition();
  bool ret=false;
  while (pos!=NULL) 
    {
      NodeInfoExt &t=node.GetNext(pos);
      if (paroc_utils::isEqual(t.key,contact))
	{
	  info=t.data;
	  ret=true;
	  break;
	}
    }
  maplock.unlock();
  return ret;
}

int NodeInfoMap::GetCount()
{
  maplock.lock();
  int count=0;
  for (int i=0;i<HASH_SIZE;i++) count+=map[i].GetCount();
  maplock.unlock();
  return count;
}

bool NodeInfoMap::Update(const paroc_string &contact, NodeInfo &info)
{
  int i=Hash(contact);
  maplock.lock();
  paroc_list<NodeInfoExt> &node=map[i];
  POSITION pos=node.GetHeadPosition();
  bool ret=false;
  while (pos!=NULL) 
    {
      NodeInfoExt &t=node.GetNext(pos);
      if (paroc_utils::isEqual(t.key,contact))
	{
	  info=t.data;
	  ret=true;
	  break;
	}
    }
  maplock.unlock();
  return ret;
}

bool NodeInfoMap::Remove(const paroc_string &contact)
{
  int i=Hash(contact);
  if (i<0) i=-i;
  maplock.lock();
  paroc_list<NodeInfoExt> &node=map[i];
  POSITION pos=node.GetHeadPosition();
  bool ret=false;
  while (pos!=NULL) 
    {
      POSITION oldpos=pos;
      NodeInfoExt &t=node.GetNext(pos);
      if (paroc_utils::isEqual(t.key, contact))
	{
	  node.RemoveAt(oldpos);
	  ret=true;
	  break;
	}
    }
  maplock.unlock();
  return ret;
}

bool NodeInfoMap::Add(const paroc_string &contact, NodeInfo &info)
{
  maplock.lock();

  int i=Hash(contact);
  paroc_list<NodeInfoExt> &node=map[i];

  POSITION pos=node.GetHeadPosition();
  bool ret=true;
  while (pos!=NULL) 
    {
      POSITION oldpos=pos;
      NodeInfoExt &t=node.GetNext(pos);
      if (paroc_utils::isEqual(t.key, contact))
	{
	  ret=false;
	  break;
	}
    }
  if (ret)
    {
      NodeInfoExt &t=node.AddTailNew();
      t.key=contact;
      t.data=info;
    }
  maplock.unlock();
  return ret;

}

int NodeInfoMap::Hash(const paroc_string &key)
{
  const char *s=key;
  if (s==NULL) return 0;
  int sum=0;
  while (*s!=0) 
    {
      sum+=*s;
      s++;
    }
  return sum%HASH_SIZE;
}



JobMgr::JobMgr(bool daemon, const paroc_string &challenge, const paroc_string &url): paroc_service_base(challenge)
{
  counter=1;
  requestCounter=1;

  signal(SIGCHLD,SIG_IGN);

  char str[256];
  strcpy(str,GetAccessPoint().GetAccessString());
  paroc_service_log("JobMgr access point : %s",str);
 
  char *tmp=str;
  while (*tmp!=0 && *tmp!=':') tmp++;
  *tmp=0;

  srand(times(NULL));
  int ret=paroc_system::GetIP(serviceID,1);
  if (ret!=1)
    {
      paroc_service_log("ERROR: can not find IP address");
      serviceID[0]=rand();
    }

  if (sscanf(tmp+1,"%d", serviceID+1)!=1) serviceID[1]=rand();
  paroc_service_log("MyID=%d:%d",serviceID[0], serviceID[1]);

  paroc_timerthread *timeinfo=new paroc_timerthread(86400,0, this);
  timeinfo->create();
  
  localuid=-1;
  service_timer.Start();


  myjobs=0;
  maxjobs=100;
  
  dynamicnodes=0;
  maxdynamicnodes=0;
  
  reserve_timeout=RESERVE_TIMEOUT;
  alloc_timeout=ALLOC_TIMEOUT;

  if (daemon) Start();
}

JobMgr::JobMgr(bool daemon, const paroc_string &conf, const paroc_string &challenge, const paroc_string &url): paroc_service_base(challenge)
{
  counter=1;
  requestCounter=1;

  signal(SIGCHLD,SIG_IGN);

  //Find service ID (pairs IP-port for tracing

  char str[1024];
  strcpy(str,GetAccessPoint().GetAccessString());
  paroc_service_log("JobMgr access point: %s",str);
  char *tmp=str;
  while (*tmp!=0 && *tmp!=':') tmp++;
  *tmp=0;

  srand(times(NULL));

  int ret=paroc_system::GetIP(serviceID,1);
  if (ret!=1)
    {
      paroc_service_log("ERROR: can not find IP address");
      serviceID[0]=rand();
    }

  if (sscanf(tmp+1,"%d", serviceID+1)!=1) serviceID[1]=rand();

   paroc_service_log("MyID=%d:%d",serviceID[0], serviceID[1]);
 
  DEBUGIF(ret<=0, "Can not find IP address of %s for resource discovery tracking",str);


  int service_timeout=0;
  int parent_timeout=86400; //default: one-day long in seconds

  localuid=-1;
  service_timer.Start();

  reserve_timeout=RESERVE_TIMEOUT;
  alloc_timeout=ALLOC_TIMEOUT;
  
  //Start deamon....redirect stdin/out/err to file...

//  close(0);
//  close(1);
//  close(2);
//  int fd0=open("/dev/null",O_RDONLY);
//  int fd1=open("/tmp/JobMgr.stdout",O_WRONLY | O_CREAT,S_IRWXU);
//  int fd2=open("/tmp/JobMgr.stderr",O_WRONLY | O_CREAT,S_IRWXU);
//  assert(fd0==0 && fd1==1 && fd2==2);

  
  FILE *f=fopen(conf,"rt");
  char name[64], val[256];
  if (f==NULL) 
    {
      printf("Open config file [%s] fail\n",(const char*)conf);
      throw errno;
    }
  printf("Starting Parallel Object JobMgr service \n");
  maxjobs=100;

  maxdynamicnodes=0;
  dynamicnodes=0;

  paroc_service_log("Loading information from %s",(const char *)conf);

  str[1023]=0;
  char mycontact[1024];

  strcpy(mycontact,(GetAccessPoint()).GetAccessString());
  while (!feof(f))
    {
      if (fgets(str,1023,f)==NULL) break;
      
      char *name=str;
      while (isspace(*name)) name++;
      if (*name==0 || *name=='#') continue;

      char *val=name;
      while ((!isspace(*val)) && *val!=0)
	{
	  *val=tolower(*val);
	  val++;
	}
      if (*val==0) continue;
      *val=0;
      val++;
      while (isspace(*val)) val++;
      if (*val==0) continue;
      char *tmp=val+strlen(val)-1;
      while (isspace(*tmp)) tmp--;
      tmp[1]=0;
      if (paroc_utils::isEqual(name,"node"))
	{
	  if (strchr(val,':')==NULL) 
	    {
	      strcat(val,":");
	      strcat(val,DEFAULT_PORT);
	    }
	  if (paroc_utils::SameContact(mycontact,val)) continue;
	  NodeInfo tmp;
	  paroc_string contact(val);
	  tmp.fixnode=true;
	  tmp.stoptime=-1;
	  tmp.heuristic=0;

	  neighbors.Add(contact, tmp);
	}
      else if (paroc_utils::isEqual(name,"parent"))
	{
	  if (strchr(val,':')==NULL) 
	    {
	      strcat(val,":");
	      strcat(val,DEFAULT_PORT);
	    }
	  if (paroc_utils::SameContact(mycontact,val)) continue;
	  paroc_accesspoint t;
	  t.SetAccessString(val);
	  parents.AddTail(t);
	}
      else if (paroc_utils::isEqual(name,"maxjobs"))
	{
	  if (sscanf(val,"%d",&maxjobs)!=1 || maxjobs<0) maxjobs=100;	
	}
      else if (paroc_utils::isEqual(name,"timeout"))
	{
	  if (sscanf(val,"%d",&service_timeout)==1 && service_timeout>0)
	    {
	      paroc_service_log("JobMgr Timeout: %ds",service_timeout);
	      
	    } else service_timeout=0;
	}
      else if (paroc_utils::isEqual(name,"checkpoint"))
	{
	  if (sscanf(val,"%d",&parent_timeout)==1 && parent_timeout>0)
	    {
	      paroc_service_log("Checkpoint every: %d seconds",parent_timeout);
	    } else parent_timeout=0;
	}
      else
	{
	  HostInfo &t=info.AddTailNew();
	  t.name=name;
	  t.val=val;
	}
    }

  fclose(f);

  SelfRegister();

  paroc_string tmpstr;

  if (Query("power",tmpstr))
    {
      total.flops=atof(tmpstr);
    }
  else 
    {
      //We do benchmark now to find the computing power of the machine...
      total.flops=paroc_utils::benchmark_power();
      sprintf(val,"%g",total.flops);
      HostInfo &t=info.AddHeadNew();
      t.name="power";
      t.val=val;
    }

  if (Query("ram",tmpstr))
    {
      total.mem=atoi(tmpstr);
    }
  if (Query("bandwidth",tmpstr))
    {
      total.bandwidth=atoi(tmpstr);
    }

  memcpy(&limit,&total,sizeof(Resources));

  if (Query("np",tmpstr))
  {
      int n=atoi(tmpstr);
      if (n>0)
      {
	  total.flops*=n;
      }

  }

  if (Query("degree",tmpstr))
    {
      if (sscanf(tmpstr,"%d",&maxdynamicnodes)!=1 || maxdynamicnodes<0) maxdynamicnodes=0;
    }


  if (Query("localuser",tmpstr))
    {
      passwd *t=getpwnam(tmpstr);
      if (t!=NULL) localuid=t->pw_uid;
    }

  memcpy(&available,&total,sizeof(Resources));
  DEBUG("Total resource power=%g, max per job=%g",total.flops,limit.flops);

  //Check and set environment variables....
  if (Query("env",tmpstr))
    {
      char *tok=strtok(tmpstr.GetString(),"()");
      char var[1024], val[1024], str[1024];
      while (tok!=NULL)
	{
	  if (sscanf(tok,"%s %s",var,val)!=2)
	    {
	      paroc_service_log("ERROR: can not parse the environment variable string [%s]",tok);
	    }
	  else 
	    {
	      sprintf(str,"%s=%s",var,val);
	      putenv(strdup(str));
	    }
	  tok=strtok(NULL,"()");
	}
    }


  
  if (daemon) Start();

  if (parent_timeout>0 || service_timeout>0)
    {
      paroc_timerthread *timeinfo=new paroc_timerthread(parent_timeout,service_timeout, this);
      timeinfo->create();
    }
}

JobMgr::~JobMgr()
{
  dump();
}




//Other service methods....

void JobMgr::RegisterNode(const paroc_accesspoint &url)
{
  paroc_string urlstr(url.GetAccessString());
  if (paroc_utils::SameContact(urlstr, GetAccessPoint().GetAccessString()))
    {
      DEBUG("Node %s already existed in the local database",(const char *)urlstr);
      return;
    }

  if (neighbors.HasContact(urlstr)) return;
  paroc_service_log("Register new node: %s", (const char *)urlstr);
  NodeInfo item;
  item.fixnode=true;
  item.stoptime=-1;
  item.heuristic=0;
  neighbors.Add(urlstr, item);
}

int JobMgr::Query(const paroc_string &type, paroc_string  &val)
{
  char tmp[1024];
  if (paroc_utils::isEqual(type,"platform"))
    {
      val=paroc_system::platform;
      return 1;
    }
  if (paroc_utils::isEqual(type,"host"))
    {
      val=paroc_system::GetHost();
      return 1;
    }
  if (paroc_utils::isEqual(type,"jobs"))
    {
      Update();
      mutex {
	sprintf(tmp,"%d/%d", jobs.GetCount() ,maxjobs);
	val=tmp;
      }
      return 1;
    }
  if (paroc_utils::isEqual(type,"joblist"))
    {
      Update();
      val="";
      
      mutex {
	POSITION pos=jobs.GetHeadPosition();
	while (pos!=NULL) 
	  {
	    Resources &r=jobs.GetNext(pos);
	    if (r.contact.IsEmpty() || r.appservice.IsEmpty()) continue;
	    
	    sprintf(tmp,"APP=%s/JOB=%s\n", (char *)(r.appservice.GetAccessString()),(char *)(r.contact.GetAccessString()) );
	    val+=tmp;
	  }
      }
      return 1;
    }

  if (paroc_utils::isEqual(type,"pausejobs"))
  {
    Update();
    mutex {
      sprintf(tmp,"%d", pause_apps.GetCount());
      val=tmp;
    }
    return 1;
  }

  if (paroc_utils::isEqual(type,"power_available"))
  {
    Update();
    sprintf(tmp,"%g/%g", available.flops ,total.flops);
    val=tmp;
    return 1;
  }

  POSITION pos=info.GetHeadPosition();
  while (pos!=NULL)
    {
      HostInfo &t=info.GetNext(pos);
      if (paroc_utils::isEqual(type,t.name))
	{
	  val=t.val;
	  return 1;
	}
    }
  return 0;
}  

bool JobMgr::AllocResource(const paroc_accesspoint &localservice, const paroc_string &objname, const paroc_od &od, int howmany, paroc_accesspoint* jobcontacts, int *reserveIDs)
{
  int requestInfo[3];
  memcpy(requestInfo,serviceID,2*sizeof(int));
  mutex {
    requestInfo[2]=requestCounter;
    requestCounter++;
  }
  paroc_array<float> fitness;
  fitness.SetSize(howmany);
  for (int i=0;i<howmany;i++) fitness[i]=0;

  int traceip[MAX_HOPS];

  try
    {
      if (!AllocResource(localservice,objname,od, howmany, fitness, jobcontacts,reserveIDs, requestInfo,traceip, 0)) return false;
      bool ret=true;
      for (int i=0;i<howmany && ret; i++) if (fitness[i]<=0) ret=false;
      if (!ret)
	{
	  //Cancel reservations...
	  paroc_array<int> mark;
	  mark.SetSize(howmany);
	  for (int i=0;i<howmany;i++) mark[i]=(fitness[i]>0)? 0 : 1;
	  for (int i=0;i<howmany;i++) if (!(mark[i]) && !jobcontacts[i].IsEmpty() && fitness[i]>0)
	    {
	      mark[i]=1;
	      paroc_accesspoint ac(jobcontacts[i]);
	      paroc_string acstr(ac.GetAccessString());
	      jobcontacts[i].SetAccessString(NULL);
	      fitness[i]=0;
	      JobMgr jobmgr(ac);
	      
	      jobmgr.CancelReservation(reserveIDs+i,1);
	      for (int j=i+1;j<howmany;j++) if (!(mark[j]) && fitness[j]>0 && paroc_utils::isEqual(acstr,jobcontacts[j].GetAccessString()))
		{
		  mark[j]=1;
		  jobcontacts[j].SetAccessString(NULL);
		  jobmgr.CancelReservation(reserveIDs+j,1);
		}
	    }
	}
      return ret;
    }
  catch(...)
    {
      Pause(localservice, SLEEP_TIME_ON_ERROR);
      return false;
    }
}

bool JobMgr::AllocResource(const paroc_accesspoint &localservice, const paroc_string &objname, const paroc_od &od, int howmany, float *fitness, paroc_accesspoint *jobcontacts, int *reserveIDs, int requestInfo[3], int iptrace[MAX_HOPS], int tracesize)
{

  if (howmany<1) return false;
  bool ret=false;
  if (!AddRequest(requestInfo))
    {
      paroc_service_log("Local resource has already been traversed!");
      return false;
    }


  int i,n;
  paroc_string platform;
  paroc_string codefile;

  //MATCHING LOCALLY
  paroc_service_log("Resource discovery request: obj=%s, local service: %s (trace=%d)",(const char *)objname,localservice.GetAccessString(),tracesize);
try
  {
    if (CheckPauseList(localservice))
      {
	paroc_service_log("Local resource matching is temporary paused due to previous errors!");
      }
    else if (Query("platform",platform) && MatchUser(localservice))
      {
	
	CodeMgr codemgr(localservice);
	if (codemgr.QueryCode(objname,platform,codefile))
	  {
	    if (MatchAndReserve(od,fitness,jobcontacts,reserveIDs, howmany)) ret=true;
	  }
      }
  }
 catch (...)
   {
     paroc_service_log("Exception on resource discovery");
     return false;
   }

 if (ret)
   {
     bool allok=true;
     for (int i=0;i<howmany && allok;i++) if (fitness[i]<1) allok=false;
     if (allok) return true;
   } 

 if (tracesize<0 || tracesize>=MAX_HOPS)
   {
     paroc_service_log("Stop forwarding due to trace size (value=%d)", tracesize);
     return ret;
   }
 AddTrace(iptrace, tracesize);
 
 //FORWARD TO NEIGHBORS...
 if (Forward(localservice, objname, od, howmany, fitness, jobcontacts,reserveIDs, requestInfo, iptrace, tracesize)) return true;
 return ret;
}

void JobMgr::CancelReservation(int *req, int howmany)
{
  if (howmany<=0) return;
  mutex {
    POSITION pos=jobs.GetHeadPosition();
    while (pos!=NULL)
      {
	POSITION oldpos=pos;
	Resources &t=jobs.GetNext(pos);
	for (int i=0;i<howmany;i++)
	  if (t.Id==req[i] && t.contact.IsEmpty())
	    {
	      available.flops+=t.flops;
	      available.mem+=t.mem;
	      available.bandwidth+=t.bandwidth;
	      jobs.RemoveAt(oldpos);
	    }
      }
  }
}


//This method return the reservation ID on success

int JobMgr::MatchAndReserve(const paroc_od &od, float &inoutfitness)
{
  float flops=0;
  float walltime=0;
  float mem=0;
  float bandwidth=0;
  
  float require, min;
  
  mutex 
    {
      if (jobs.GetCount()>=maxjobs) return 0;
      
      float fitness=1;
      if (!od.IsEmpty())
	{
	  od.getPower(require,min);
	  if (require>0)
	    {
	      DEBUG("Require %f, at least: %f (available: %f)", require, min, available.flops);
	      if (min<0) min=require;
	      if (min>available.flops || min>limit.flops)
		{
		  paroc_service_log("Local Match Failed (reason: power)");
		  return 0;
		}
	      if (require>available.flops || require> limit.flops)
		{
		  flops=min(available.flops,limit.flops);
		  fitness=flops/require;
		}
	      else
		{
		  fitness=min(available.flops,limit.flops)/require;
		  flops=require;
		}
	      if (fitness<inoutfitness) return 0;
	    }
	  od.getMemory(require,min);
	  if (require>0)
	    {
	      DEBUG("Require memory %f, at least: %f (available: %f)", require, min, available.mem);
	      if (min<0) min=require;
	      if (min>available.mem)
		{
		  paroc_service_log("Local Match Failed (reason: memory)");
		  return 0;
		}
	      float fitness1;
	      if (require>available.mem)
		{
		  mem=available.mem;
		  fitness1=mem/require;
		}
	      else
		{
		  mem=require;
		  fitness1=mem/available.mem;
		}
	      if (fitness1<fitness)
		{
		  if (fitness1<inoutfitness) return 0;
		  fitness=fitness1;
		}
	    }
	  
	  walltime=od.getWallTime();
	  if (walltime<0) walltime=0;
	  
	  paroc_string walltime_str;
	  if (Query("walltime",walltime_str))
	    {
	      int walltime_l[4];
	      int n=sscanf(walltime_str,"%d:%d:%d:%d",walltime_l,walltime_l+1,walltime_l+2,walltime_l+3);
	      if (n<=0)
		{
		  paroc_service_log("Bad walltime expression");
		}
	      else
		{
		  if (n!=4)
		    {
		      for (int i=n-1;i>=0;i--) walltime_l[i+4-n]=walltime_l[i];
		      for (int i=3-n; i>=0; i--) walltime_l[i]=0;
		    }
		  float maxwalltime=walltime_l[3]+60*walltime_l[2]+3600*(walltime_l[1]+24*walltime_l[0]);
		  
		  if ((walltime<=0 && maxwalltime>0) || walltime>maxwalltime) return 0;
		}
	    }
	}
      inoutfitness=fitness;
      Resources &t=jobs.AddTailNew();
      t.Id=counter;
      t.flops=flops;
      t.mem=mem;
      t.bandwidth=bandwidth;
      t.start=time(NULL);
      t.walltime=walltime;
      
      available.flops-=flops;
      available.mem-=mem;
      available.bandwidth-=bandwidth;
      counter=(counter%1000000000)+1;
      paroc_service_log("Local Match OK (fitness=%f, reserveID=%d)", fitness,t.Id);
      return t.Id;
    }
}


bool JobMgr::MatchAndReserve(const paroc_od &od, float *fitness, paroc_accesspoint *jobcontacts, int *reserveIDs, int howmany)
{
  if (howmany<=0) return false;
  Update();
  bool ret=false;

  //Sort by the fitness
  paroc_array<int> index;
  index.SetSize(howmany);
  for (int i=0;i<howmany;i++) index[i]=i;

  for (int i=0;i<howmany;i++)
    for (int j=howmany-1;j>i;j--) if (fitness[index[j]]>fitness[index[j-1]])
      {
	int t=index[j];
	index[j]=index[j-1];
	index[j-1]=t;
      }
  for (int i=howmany-1;i>=0;i--)
    {
      int pos=index[i];
      float t=fitness[pos];
      if (t>=1) return ret;
      int id=MatchAndReserve(od,fitness[pos]);
      if (id<=0) return ret;
      else ret=true;

      if (t>0 && !(jobcontacts[pos].IsEmpty()) )
	{
	  //Cancel previous reservation
	  try 
	    {
	      JobMgr res(jobcontacts[pos]);
	      res.CancelReservation(reserveIDs+pos,1);
	    }
	  catch (...)
	    {
	      paroc_service_log("Error: Fail to cancel reservation #%d on %s",reserveIDs[pos],jobcontacts[pos].GetAccessString());
	    }
	}
      reserveIDs[pos]=id;
      jobcontacts[pos]=GetAccessPoint();
    }
  return ret;
}

void JobMgr::Update()
{
  mutex
    {
      //Check if a reservation timeout/job termination....then reget the resource...
      POSITION pos=jobs.GetHeadPosition();
      while (pos!=NULL)
	{
	  POSITION old=pos;
	  Resources &t=jobs.GetNext(pos);
	  time_t now=time(NULL);
	  
	  if (t.contact.IsEmpty())
	    {
	      if (reserve_timeout>0 && now-t.start>reserve_timeout)
		{
		  available.flops+=t.flops;
		  available.mem+=t.mem;
		  available.bandwidth+=t.bandwidth;
		  jobs.RemoveAt(old);
		}         
	    }
	  else if (now-t.start>5) // Do not check twice within 5 seconds
	    {
	      if (ObjectAlive(t.contact)) t.start=now;
	      else 
		{
		  available.flops+=t.flops;
		  available.mem+=t.mem;
		  available.bandwidth+=t.bandwidth;
		  jobs.RemoveAt(old);
		}
	    }
	}
    }
}


bool JobMgr::Forward(const paroc_accesspoint &localservice, const paroc_string &objname, const paroc_od &od, int howmany, float *fitness, paroc_accesspoint *jobcontacts, int *reserveIDs, int requestInfo[3], int iptrace[MAX_HOPS], int tracesize)
{

  //The local host is not fully qualified! Find on other hosts....
  //Since this method can be invoked concurently, 
  //we need to copy the data to local memony stack and process on these data

  paroc_list_string nodes;
  neighbors.GetContacts(nodes);
  POSITION pos=nodes.GetHeadPosition();
  Timer watch;
  watch.Start();
  bool ret=false;

  while (pos!=NULL)
    {
      paroc_string &contact=nodes.GetNext(pos);
      NodeInfo info;
      if (!neighbors.GetInfo(contact,info)) continue;

      if (info.stoptime>=0)
	{
	  if (service_timer.Elapsed()-info.stoptime<PAUSE_FORWARD_TIMEOUT) continue;
	  info.stoptime=-1;
	}

      //Check if the next IP is in the trace or not. If not, add...
      try {
	watch.Reset();
	DEBUG("\tForward request to %s (trace=%d)",(const char *)contact, tracesize);

	paroc_accesspoint childaddr;
	childaddr.SetAccessString(contact);
	
	if (NodeInTrace(iptrace,tracesize,childaddr)) continue;

	//Separate the Fitness into 2 parts. Only forward the parts whose fitness<1...
	int good=0;
	int nswap=0;
	for (int j=0;j<howmany;j++)
	  if (fitness[j]<1)
	    {
	      for (int k=howmany-1-nswap;k>j;k--) if (fitness[k]>=1)
		{
		  float f=fitness[k];
		  fitness[k]=fitness[j];
		  fitness[j]=f;
		  
		  int r=reserveIDs[k];
		  reserveIDs[k]=reserveIDs[j];
		  reserveIDs[j]=r;
		  
		  paroc_accesspoint ac(jobcontacts[k]);
		  jobcontacts[k]=jobcontacts[j];
		  jobcontacts[j]=ac;
		  nswap++;
		  break;
		}
	      if (fitness[j]<1) break;
	      good++;
	      
	    } else good++;

	int count=howmany-good;
	if (count<=0) break;
	JobMgr child(childaddr);
	paroc_array<float> oldfitness;
	oldfitness.InsertAt(-1,fitness+good,count);
	if (child.AllocResource(localservice,objname,od, count , fitness+good,jobcontacts+good, reserveIDs+good, requestInfo, iptrace, tracesize))
	  {
	    ret=true;
	    double seconds=watch.Elapsed();
	    float sumfitness=0;
	    float *tmp=fitness+good;
	    for (int j=0;j<count;j++) if (tmp[j]!=oldfitness[j]) sumfitness+=tmp[j];
	    
	    if (sumfitness>0)
	      {
		info.heuristic=(info.heuristic+seconds/sumfitness)/1.9;
	      } else info.heuristic+=seconds;
	    
	    if (info.heuristic>MAX_HEURISTICS) info.heuristic=MAX_HEURISTICS;
	  }
	else 
	  {
	    info.heuristic+=watch.Elapsed();
	    if (info.heuristic>MAX_HEURISTICS) info.heuristic=MAX_HEURISTICS;
	  }

      }
      catch (...)
	{
	  paroc_service_log("Exception on %s", (const char *)contact);
	  info.heuristic=2*MAX_HEURISTICS;
	  info.stoptime=service_timer.Elapsed();
	}
      neighbors.Update(contact,info);
    }

  paroc_array<int> index;
  index.SetSize(howmany);
  for (int i=0;i<howmany;i++) index[i]=(fitness[i]<=0)? 1: -1;
  int total=0;
  paroc_string local=GetAccessPoint().GetAccessString();
  for (int i=0;i<howmany;i++) if (index[i]==-1)
    {
      index[i]=1;
      paroc_string t(jobcontacts[i].GetAccessString());
      if (t==NULL || paroc_utils::isEqual(t,local)) continue;
      NodeInfo info;
      info.fixnode=false;
      info.stoptime=-1;
      info.heuristic=0;
      if (neighbors.Add(t,info)) total++;
      
      for (int j=i+1;j<howmany;j++) 
	if ( index[j]==-1 && paroc_utils::isEqual(jobcontacts[i].GetAccessString(), jobcontacts[j].GetAccessString()) ) 
	  {
	    index[j]=1;
	  }
    }

  //Now remove dynamic nodes to keep balance....
  //TO DO....
  return ret;
}


void JobMgr::SelfRegister()
{
  static double lasttime=-500;
  
  if ((service_timer.Elapsed()-lasttime)<300) return;
  lasttime=service_timer.Elapsed()+36000;

  DEBUG("Updating my contact to parrent nodes...");
  POSITION pos=parents.GetHeadPosition();
  while (pos!=NULL)
    {
      paroc_accesspoint &tmp=parents.GetNext(pos);
      try 
	{
	  JobMgr remote(tmp);
	  DEBUG("Registering %s to %s",GetAccessPoint().GetAccessString(), tmp.GetAccessString());
	  remote.RegisterNode(GetAccessPoint());              
	}
      catch (...)
	{
	  DEBUG("Exception: can not register the local job service [%s] to %s",GetAccessPoint().GetAccessString(), tmp.GetAccessString());
	}
    }
  lasttime=service_timer.Elapsed();
}

void JobMgr::Start()
{
  paroc_service_base::Start();

  close(0);
  close(1);
  close(2);
  open("/dev/null",O_RDONLY);

  char *tmp=getenv("PAROC_TEMP");
  int pid=getpid();
  char filename[256];
#ifndef NDEBUG
  if (tmp!=NULL) sprintf(filename,"%s/jobmgr_stdout_%d",tmp,pid);
  else sprintf(filename,"/tmp/jobmgr_stdout_%d",pid);

  open(filename,O_WRONLY | O_CREAT,S_IRWXU | S_IRGRP);

  if (tmp!=NULL) sprintf(filename,"%s/jobmgr_stderr_%d",tmp,pid);
  else  sprintf(filename,"/tmp/jobmgr_stderr_%d", pid);

  open(filename,O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP);

  paroc_service_log("GO TO DAEMON MODE");
#else
  open("/dev/null",O_WRONLY);
  open("/dev/null",O_WRONLY);
#endif 

  if (tmp!=NULL) sprintf(filename,"%s/jobmgr.pid",tmp);
  else strcpy(filename,"/tmp/jobmgr.pid");

  FILE *f=fopen(filename,"w+");
  if (f!=NULL)
    {
      fprintf(f,"%d",pid);
      fclose(f);
    }
}

int JobMgr::Exec(char **arguments, char *env[], int &pid)
{
  
  char *file=NULL;
  char *argv[1024];
  char *tmp;
  char sep[]=" \n\r\t";
  paroc_string str;
  int n=0;

  if (Query("jobmgr",str) && str!=NULL)
    {
      char *tok=strtok_r(str.GetString(),sep,&tmp);
      while (tok!=NULL)
	{
	  argv[n++]=tok;
	  tok=strtok_r(NULL,sep,&tmp);
	}
    } 
  
  while (*arguments!=NULL && n<1023)
    {
      argv[n++]=*arguments;
      arguments++;
    }
  argv[n]=NULL;
  if (n==0) return ENOENT;
  file=argv[0];

  pid=fork();
  if (pid==-1)
    {
      paroc_service_log("Execute command fail. Pause on error...");
      paroc_accesspoint empty;
      Pause(empty,SLEEP_TIME_ON_ERROR);
      return errno;
    }
  else if (pid==0)
    {
      int nf=getdtablesize();
      for (int fd=3;fd<nf;fd++) close(fd);
      if (localuid>=0)
	{
	  int ret=setuid(localuid);
	  if (ret!=0) perror("ERROR: can not setuid\n");
	}

      if (env!=NULL)
	{
	  while (*env!=NULL)
	    {
	      putenv(strdup(*env)); 
	      env++;
	    }
	}
	
      //Child process
      execvp(file,argv);
      char str[256];
      paroc_service_log("Execution of [%s] fail\n",file);      
      _exit(-1);    
    }
  return 0;  
}

int JobMgr::ExecObj(const paroc_string  &objname, int howmany, int *reserveIDs, const paroc_accesspoint &localservice, paroc_accesspoint *objcontacts)
{

  if (howmany<=0) return EINVAL;

  char *env[32];
  char **curenv=env;
  char env_np[256];
  char env_walltime[256];
  *env_walltime=0;

  sprintf(env_np,"PAROC_NP=%d",howmany);
  *curenv=env_np;
  curenv++;

  mutex {
    for (int i=0;i<howmany;i++)
      {
	Resources *r=VerifyReservation(reserveIDs[i], true);
	if (r==NULL) 
	  {
	    CancelReservation(reserveIDs,howmany);
	    return ECANCELED;
	  }

	if (r->walltime>0 && *env_walltime==0)
	  {
	    int hours=int(r->walltime/3600);
	    int minutes=int ((r->walltime-hours*3600)/60);
	    float sec=r->walltime-hours*3600-minutes*60;
	    sprintf(env_walltime,"PAROC_JOB_WALLTIME=%d:%d:%g",hours,minutes,sec);
	    *curenv=env_walltime;
	    curenv++;
	  }
      }
  }   
  *curenv=NULL;

  paroc_string mycodefile;
  try
    {
      CodeMgr code(localservice);
      if (!code.QueryCode(objname,paroc_system::platform,mycodefile) || mycodefile==NULL)
	{
	  CancelReservation(reserveIDs,howmany);
	  return ENOENT;
	}
    }
  catch(...)
    {
      CancelReservation(reserveIDs, howmany);
      return ENOENT;
    }
  
  char *argv[1024];
  int n=0;
  char *code=mycodefile.GetString();
  char *tmp;
  char *tok=strtok_r(mycodefile.GetString()," \t\n",&tmp);
  while (tok!=NULL)
    {
      argv[n++]=tok;
      tok=strtok_r(NULL," \t\n",&tmp);
    }
  paroc_string obj_arg(objname);

  if (obj_arg!=NULL)
    {
      argv[n++]=obj_arg.GetString();
    }

  //Setup Global job service
  paroc_string jobservice_arg("-jobservice=");
  jobservice_arg+=GetAccessPoint().GetAccessString();
  argv[n++]=jobservice_arg.GetString();
  
  //Setup application specific services...
  paroc_string localservice_arg("-appservice=");
  if (!localservice.IsEmpty())
    {
      localservice_arg+=localservice.GetAccessString();
      argv[n++]=localservice_arg.GetString();
    }
  
  paroc_combox_socket tmpsock;
  if (!tmpsock.Create(0,true))
    {
      CancelReservation(reserveIDs,howmany);
      return errno;
    }

  paroc_string cburl;
  tmpsock.GetUrl(cburl);
  char tmpstr[1024];
  sprintf(tmpstr,"-callback=%s",(const char *)cburl);
  argv[n++]=tmpstr;
  argv[n]=NULL;

  int pid;
  int ret=Exec(argv,env, pid);

  if (ret!=0)
    {
      Pause(localservice, SLEEP_TIME_ON_ERROR);
      CancelReservation(reserveIDs, howmany);        
      return ret;
    }

  //Receive the object accesspoint from object broker....
  tmpsock.SetTimeout(alloc_timeout*1000);

  for (int i=0;i<howmany;i++)
    {
      paroc_buffer_xdr buf1;
      paroc_buffer &buf=buf1;
      
      if (!buf.Recv(tmpsock))
	{
	  int err=errno;
	  if (pid>0) kill(pid, SIGKILL);
	  Pause(localservice, SLEEP_TIME_ON_ERROR);
	  CancelReservation(reserveIDs, howmany);        
	  return err;
	}
      
      int n;
      buf.Push("status","int",1);
      buf.UnPack(&n,1);
      buf.Pop();
      
      if (n!=0)
	{
	  if (pid>0) kill(pid, SIGKILL);
	  Pause(localservice, SLEEP_TIME_ON_ERROR);
	  CancelReservation(reserveIDs, howmany);        
	  return n;
	}
      buf.Push("address","paroc_accesspoint",1);
      objcontacts[i].Serialize(buf , false);
      buf.Pop();
      
      if (!ValidateReservation(reserveIDs[i], objcontacts[i], localservice))
	{
	  if (pid>0) kill(pid,SIGKILL);
	  CancelReservation(reserveIDs, howmany);        
	  return ECANCELED;
	}
    }     
  return 0;
}

bool JobMgr::MatchUser(const paroc_accesspoint &localservice)
{
  return true;
}

void JobMgr::dump()
{
#ifndef NDEBUG
  FILE *f;
  char str[256];
  char str1[256];
  sprintf(str,"%s/JobMgr_%s",DUMP_PATH,GetAccessPoint().GetAccessString());
  char *tmp=str;
  for (char *tmp=str; *tmp!=0;tmp++) if (*tmp==':') *tmp='_';
  f=fopen(tmp,"w+t");
  if (f==NULL) return;
  
  paroc_list_string keys;
  neighbors.GetContacts(keys);
  fprintf(f,"Neighbour nodes (%d)\n", keys.GetCount());
  POSITION pos=keys.GetHeadPosition();
  int i=0;
  while (pos!=NULL)
    {
      i++;
      paroc_string &t=keys.GetNext(pos);
      NodeInfo info;
      if (!neighbors.GetInfo(t,info)) continue;
      fprintf(f,"%d: %s\t%g\t%d\n",i,(const char *)t, info.heuristic,int(info.fixnode));
    }
  fclose(f);
#endif

}

void JobMgr::Pause(const paroc_accesspoint &app, int duration)
{
  paroc_service_log("Pause %d seconds", duration);
  mutex {
  PauseInfo &t=pause_apps.AddTailNew();
  t.until_time=service_timer.Elapsed()+duration;
  t.app=app;
  }
}

bool JobMgr::CheckPauseList(const paroc_accesspoint &app)
{
  double now=service_timer.Elapsed();
  mutex {
    POSITION pos=pause_apps.GetHeadPosition();
    while (pos!=NULL)
      {
	POSITION old=pos;
	PauseInfo &t=pause_apps.GetNext(pos);
	if (now> t.until_time) pause_apps.RemoveAt(old);
	else if (t.app.IsEmpty() || t.app==app)
	  {
	    DEBUG("CheckPauseList return true");
	    return true;
	  }
      }
  }
  return false;

}


bool JobMgr::AddRequest(int reqId[3])
{
  double oldest=service_timer.Elapsed();
  if (reserve_timeout>0) oldest-=2*reserve_timeout;
  else oldest-=300;

  mutex {
    POSITION pos=tracelist.GetHeadPosition();
    while (pos!=NULL)
      {
	POSITION oldpos=pos;
	RequestTrace &t=tracelist.GetNext(pos);
	if (memcmp(t.requestID,reqId, 3*sizeof(int))==0) return false;
	if (t.timestamp<oldest) tracelist.RemoveAt(oldpos);
      }
    RequestTrace &t=tracelist.AddTailNew();
    memcpy(t.requestID,reqId,3*sizeof(int));
    t.timestamp=service_timer.Elapsed();
    if (tracelist.GetCount()>100) paroc_service_log("Warning: job trace list is too big (%d items)\n",tracelist.GetCount());
    return true;
  }
}

bool JobMgr::AddTrace(int trace[MAX_HOPS], int &tracesize)
{
  if (tracesize<0 || tracesize>=MAX_HOPS) return false;
  if (paroc_system::GetIP(trace+tracesize,1)==1)
    {
      tracesize++;
      return true;
    }
  return false;
}


bool JobMgr::NodeInTrace(int trace[MAX_HOPS], int tracesize, paroc_accesspoint &contact)
{
  if (tracesize<0 || tracesize>=MAX_HOPS || contact.IsEmpty()) return false;
  char host[1024];
  strcpy(host,contact.GetAccessString());

  char *hostname=host;

  char *t=strstr(host, "socket://");
  if (t!=NULL) hostname=t+9;
  else
    {
      t=strstr(host, "http://");
      if (t!=NULL) hostname=t+7;
    }
  
  t=strchr(hostname,':');

  if (t!=NULL) *t=0;
  int ip;
  if (paroc_system::GetIP(hostname,&ip,1)!=1) return false;

  for (int i=0;i<tracesize;i++, trace++) if (*trace==ip) return true;
  return false;
}


bool JobMgr::ObjectAlive(paroc_accesspoint &t)
{
  try {
    paroc_interface test(t);
    return true;
  }
  catch (...)
    {
      return false;
    }
}

Resources* JobMgr::VerifyReservation(int reserveId, bool updatetime)
{
  mutex {
    POSITION pos=jobs.GetHeadPosition();
    while (pos!=NULL)
      {
	Resources &tmp=jobs.GetNext(pos);
	if (tmp.Id==reserveId)
	  {
	    if (updatetime) tmp.start=time(NULL);
	    return &tmp;
	  }
      }
  }
  return NULL;  
}

bool JobMgr::ValidateReservation(int id, const paroc_accesspoint &objcontact, const paroc_accesspoint &appserv)
{
  mutex {
    POSITION pos=jobs.GetHeadPosition();
    while (pos!=NULL)
      {
	POSITION old=pos;
	Resources &tmp=jobs.GetNext(pos);
	if (tmp.Id==id)
	  {
	    tmp.contact=objcontact;
	    tmp.appservice=appserv;
	    tmp.start=time(NULL);
	    return true;
	  }
      }
  }
  return false;
}


bool JobMgr::ReleaseJob(int id)
{
  if (id<=0) return false;
  mutex {
    POSITION pos=jobs.GetHeadPosition();
    while (pos!=NULL)
      {
	POSITION oldpos=pos;
	Resources &t=jobs.GetNext(pos);
	if (t.Id==id && !t.contact.IsEmpty())
	  {
	    available.flops+=t.flops;
	    available.mem+=t.mem;
	    available.bandwidth+=t.bandwidth;
	    jobs.RemoveAt(oldpos);
	    return true;
	  }
      }
  }
  return false;
}

