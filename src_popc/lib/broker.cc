#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include <signal.h>
#include "paroc_broker.h"
#include "paroc_interface.h"
#include "paroc_event.h"
#include "paroc_buffer_factory_finder.h"

#include "objectmonitor.ph"
#include "paroc_thread.h"
#include "appservice.ph"

#define TIMEOUT 1800

#define MINMETHODID 2

void paroc_request::operator =(const paroc_request &r)
{
  from=r.from;
  memcpy(methodId,r.methodId,3*sizeof(unsigned));
  data=r.data;
}

class paroc_receivethread: public paroc_thread 
{
public:
  paroc_receivethread(paroc_broker *br, paroc_combox *com);
  ~paroc_receivethread();
  virtual void start();
protected:
  paroc_broker *broker;
  paroc_combox *comm;
};

paroc_receivethread::paroc_receivethread(paroc_broker *br, paroc_combox *combox): paroc_thread(true)
{
  broker=br;
  comm=combox;
}

paroc_receivethread::~paroc_receivethread()
{
}

void paroc_receivethread::start()
{
  broker->ReceiveThread(comm);
}

//===paroc_object: base class for all parallel object-server side


//===paroc_broker: the base class for server object broker


paroc_accesspoint paroc_broker::accesspoint;
paroc_string paroc_broker::classname;


paroc_broker::paroc_broker()
{  
  obj=NULL;
  state=PAROC_STATE_RUNNING;

  instanceCount=0;
  mutexCount=0;
}

paroc_broker::~paroc_broker()
{
  if (obj!=NULL) 
    {
      delete obj;
    }
}


bool paroc_broker::Setup(paroc_array<paroc_combox *> & comboxArray)
{  

  int comboxCount = comboxArray.GetSize();
  int i=0;
  
  for(i=0;i<comboxCount;i++){
    int port;
    //if(*comboxArray[i]==NULL || (port=((paroc_combox*)comboxArray[i])->GetPort())<=0) return false;

  }
  comboxArrayPtr = &comboxArray;
  return true;
}

int paroc_broker::Run()
{

  //Create threads for each protocols for receiving requests....
   
  paroc_array<paroc_receivethread *> ptArray;
  int comboxCount = comboxArrayPtr->GetSize();
  ptArray.SetSize(comboxCount);
  int i;

  state=PAROC_STATE_RUNNING;

  for(i=0; i<comboxCount; i++){
    ptArray[i] =new paroc_receivethread(this,(*comboxArrayPtr)[i]);
    int ret=ptArray[i]->create();
    if (ret!=0) return errno;
  }

  bool enablealarm=true;
  alarm(TIMEOUT);
  
  while (state==PAROC_STATE_RUNNING)
    {
      try {
	paroc_request req;
	
	if (!GetRequest(req)) break;
	//	DEBUG("Serve request: class %s, MethodID=(%d,%d,%d)",classname,req.methodId[0],req.methodId[1],req.methodId[2]);
	ServeRequest(req);
	if (req.methodId[2] & INVOKE_CONSTRUCTOR) 
	  {
	    alarm(0);
	    if (obj==NULL) break;
	  }
      }
      
      catch (...)
	{
	  if (!paroc_system::appservice.IsEmpty())
	    {
	      char tmp[1024];
	      sprintf(tmp,"Unhandled exception on %s@%s\n",(const char *)paroc_broker::classname,paroc_broker::accesspoint.GetAccessString());
	      AppCoreService app(paroc_system::appservice);
	      app.Log(tmp);
	      app.UnManageObject(paroc_broker::accesspoint);
	      app.KillAll();
	      exit(1);
	    }
	  //	  rprintf("Broker exception (ignored)\n");
	}
    }

  if (obj!=NULL && state==PAROC_STATE_RUNNING)
    {
      paroc_mutex_locker test(execCond);

      //Wait for all invocations terminated....
      while (instanceCount>0 || !request_fifo.IsEmpty())
	{
	  execCond.wait();
	}
    }

  state=PAROC_STATE_EXIT;
  for(i=0; i<comboxCount; i++)
    {
      if (WakeupReceiveThread((*comboxArrayPtr)[i])) delete ptArray[i]; else ptArray[i]->cancel(); 
      (*comboxArrayPtr)[i]->Destroy();
    }

  return 0;
}


bool paroc_broker::Init(int *argc, char ***argv, paroc_array<paroc_combox *> & comboxArray)
{ 
  char *addr=paroc_utils::checkremove(argc,argv,"-callback="); 

  paroc_combox *callback=NULL;
  if (addr!=NULL)
  {
    char *tmp=strstr(addr,"://");
    paroc_combox_factory *fact=paroc_combox_factory::GetInstance();

    if (tmp==NULL) callback=fact->Create("socket"); 
    else 
      {
	*tmp=0;
	callback=fact->Create(addr);
	*tmp=':';
      }

    if (!callback->Create(0, false) || !callback->Connect(addr))
      {
	callback->Destroy();
	rprintf("Error: fail to connect to callback\n");
	return false;
      }
  }

  paroc_combox_factory  *ff=paroc_combox_factory::GetInstance();
  int comboxCount = ff->GetCount();
  comboxArray.SetSize(comboxCount);
  paroc_string protocolName;  
  paroc_string url;
  int status=0;

  int count=0;
  for (int i=0;i<comboxCount;i++)
    {
      comboxArray[count]=ff->Create(i);
      if (comboxArray[count]==NULL)
	{
	  DEBUG("Fail to create combox #%d",i);
	}
      else count++;
    }
  if (comboxCount!=count) 
    {
      comboxCount=count;
      comboxArray.SetSize(comboxCount);
    }
  if (comboxCount==0) status=1;
  for(int i=0; i<comboxCount; i++)
    {
      paroc_combox * pc = comboxArray[i];
      pc->GetProtocol(protocolName);
      char argument[1024];
      sprintf(argument, "-%s_port=", (const char *)protocolName);    
      
      char *portstr=paroc_utils::checkremove(argc,argv,argument);
      if (portstr!=NULL)
	{
	  int port;
	  if (sscanf(portstr,"%d",&port)!=1) return false;
	  if(!pc->Create(port, true))
	    {
	      paroc_system::perror("Broker");
	      return false;
	    }	  
	}
      else 
    	{
	  if(!pc->Create(0, true))
	    {
	      paroc_system::perror("Broker");
	      return false;
	    }
	}
      paroc_string ap;
      pc->GetUrl(ap);
      url+=ap;
      if(i<comboxCount-1) url+=PROTO_DELIMIT_CHAR;
    }
  accesspoint.SetAccessString(url.GetString());
  
  
  if (callback!=NULL)
    {
      char url[1024];
      int len;
      paroc_buffer *buf=callback->GetBufferFactory()->CreateBuffer();
      paroc_message_header h("Callback");
      buf->SetHeader(h);
      
      buf->Push("status","int",1);
      buf->Pack(&status,1);
      buf->Pop();
      
      buf->Push("address","paroc_accesspoint",1);
      paroc_broker::accesspoint.Serialize(*buf,true);
      buf->Pop();
      
      bool ret=buf->Send(*callback);
      buf->Destroy();
      callback->Destroy();
      if (!ret)
	{
	  rprintf("Error: fail to send accesspoint  via callback\n");
	  return false;
	}
    }
  return true;
}

bool paroc_broker::SendCallback(paroc_accesspoint & ap){
  return true;
}


bool paroc_broker::WakeupReceiveThread(paroc_combox  *mycombox)
{
   paroc_combox_factory *fact=paroc_combox_factory::GetInstance();
   paroc_string url, prot;

   bool ok=false;
   mycombox->GetProtocol(prot);
   mycombox->GetUrl(url);

   paroc_combox *tmp=fact->Create(prot);
   
   if (tmp!=NULL) 
     {
       tmp->SetTimeout(100000);
       if (tmp->Create(0,false) && tmp->Connect(url))
	 {
	   paroc_buffer *buf=tmp->GetBufferFactory()->CreateBuffer();
	   paroc_message_header h(0,0,0,"Wakeup");
	   buf->SetHeader(h);
	   ok=buf->Send(*tmp);
	   buf->Destroy();
	 }
       else
	 {
	   DEBUG("Fail to wakeup receive thread");
	 }
       tmp->Destroy();
     }
   return ok;
}
