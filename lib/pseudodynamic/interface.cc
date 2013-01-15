/**
 * File : interface.cc
 * Author : Tuan Anh Nguyen
 * Description : base implementation of the parallel object interface class
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval  ViSaG pro.  Add support for POP-C++ Virtual-Secure version
 * P.Kuonen    2011/3/25   Cosmetic on printed error messages
 * clementval  2011/9/13   Add the method GetAccessPointForThis() to be able to handle the THIS keyword correctly
 */

#include <stdio.h>
#include <mpi.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <errno.h>


#include "paroc_interface.h"
#include "paroc_buffer_factory_finder.h"
#include "paroc_broker.h"
#include "paroc_combox_factory.h"
#include "paroc_combox.h"
#include "paroc_system.h"
#include "paroc_utils.h"
#include "config.h"

#if defined POPC_SECURE || defined POPC_SECURE_VIRTUAL
#include "popc_security_manager.ph"
#endif

#ifndef POPC_CONNECT_TIMEOUT
#define POPC_CONNECT_TIMEOUT 10000
#endif

int RunCmd(char **argv, char *env[], int *status)
{

	char *file=NULL;

	POPString str;

	if (argv==NULL || argv[0]==NULL) return ENOENT;
	file=argv[0];
	//  if (access(file,X_OK)!=0)
	//    {
	//      return -1;
	//    }

	signal(SIGCHLD, ((status==NULL) ? SIG_IGN : SIG_DFL));

#ifndef UC_LINUX
	int pid=fork();
	if (pid==-1)
	{
		int err=errno;
		DEBUG("Fork fails to execute ...");
		return err;
	}
	else if (pid==0)
	{
		int nf=getdtablesize();
		for (int fd=3;fd<nf;fd++) close(fd);
		if (env!=NULL)
		{
			while (*env!=NULL)
			{
				putenv(strdup(*env));
				env++;
			}
		}
		if (status==NULL)
		{
			setpgid(0,0);
		}
		//Child process
		execvp(file,argv);
		DEBUG("Execution of [%s] fails\n",file);
		_exit(-1);
	}
#else
	int pid=vfork();
	if (pid==-1)
	{
		int err=errno;
		DEBUG("Fork fails to execute ...");
		return err;
	}
	else if (pid==0)
	{
		execve(file,argv,env);
		DEBUG("Execution of [%s] fail (vfork)\n",file);
		_exit(-1);
	}
#endif
	if (status!=NULL)
	{
		int id;
      id=waitpid(pid, status, 0);
	}
	return 0;
}

paroc_accesspoint paroc_interface::_paroc_nobind;
//binding time out in miliseconds
int paroc_interface::paroc_bind_timeout=10000;
int paroc_interface::batchindex=0;
int paroc_interface::batchsize=0;
paroc_accesspoint * paroc_interface::batchaccesspoint=NULL;

paroc_interface::paroc_interface() : _ssh_tunneling(false), __paroc_combox(NULL), __paroc_buf(NULL)
{
//  printf("INTERFACE: Create without anything\n"); 
  
  if(od.isSecureSet()) 
    accesspoint.SetSecure();
  //printf("INTERFACE: End of constructor\n"); 	
}

paroc_interface::paroc_interface(const paroc_accesspoint &p) : _ssh_tunneling(false), __paroc_combox(NULL), __paroc_buf(NULL)
{
//  printf("INTERFACE: Create with AP\n"); 

  // For SSH tunneling
  if(p.IsService())
    accesspoint.SetAsService();

  if(!p.IsEmpty());
    Bind(p);

  if(p.GetNoAddRef()) 
    DecRef();   
}





paroc_interface::paroc_interface(const paroc_interface &inf) : _ssh_tunneling(false), __paroc_combox(NULL), __paroc_buf(NULL)
{
  //printf("INTERFACE: Create with interface\n");
   paroc_accesspoint infAP = inf.GetAccessPoint();

   if(infAP.IsSecure())
      accesspoint.SetSecure();
   if(infAP.IsService())
      accesspoint.SetAsService();
      
	Bind(inf.GetAccessPoint());
}

paroc_interface::paroc_interface(paroc_combox *combox, paroc_buffer *buffer) : _ssh_tunneling(false), __paroc_combox(combox), __paroc_buf(buffer)
{
  //printf("INTERFACE: Create with combox & buffer\n");
	if (combox!=NULL) {
		POPString url;
		combox->GetUrl(url);
		accesspoint.SetAccessString(url);
		if (__paroc_buf==NULL) __paroc_buf=combox->GetBufferFactory()->CreateBuffer();
	}
}


/**
 * Interface destructor
 */
paroc_interface::~paroc_interface()
{
  //printf("Destroy interface %s\n", ClassName());
  Release();
}

paroc_interface & paroc_interface::operator = (const paroc_interface & obj)
{
  //printf("INTERFACE: copy constructor\n");
	Release();
	const paroc_accesspoint &res = obj.GetAccessPoint();
	Bind(res);
	return (*this);
}

void paroc_interface::SetOD(const paroc_od &myod)
{
	od = myod;
}

const paroc_od & paroc_interface::GetOD() const
{
	return od;
}


const paroc_accesspoint &  paroc_interface::GetAccessPoint() const
{
	return accesspoint;
}

/**
 * Get the accesspoint of the parallel object and set the _noaddref variable to TRUE
 */
const paroc_accesspoint &  paroc_interface::GetAccessPointForThis()
{
//  printf("INTERFACE: Get Access Point for this\n");
  accesspoint.SetNoAddRef();
	return accesspoint;
}

void paroc_interface::Serialize(paroc_buffer &buf, bool pack)
{
  //printf("Interface serialize\n");
	buf.Push("od", "paroc_od", 1);
	od.Serialize(buf,pack);
	buf.Pop();

	buf.Push("accesspoint", "paroc_accesspoint", 1);
	accesspoint.Serialize(buf, pack);
	buf.Pop();
	
	paroc_buffer *old = NULL;

	if (&buf == __paroc_buf)
	{
		old = &buf;
		__paroc_buf = __paroc_combox->GetBufferFactory()->CreateBuffer();
	}


  
	if (pack) {
    int ref = 1;
		buf.Push("refcount", "int", 1);
		buf.Pack(&ref, 1);
		buf.Pop();
	} else {
		int ref;
		buf.Push("refcount", "int", 1);
		buf.UnPack(&ref, 1);
		buf.Pop();
		if (ref > 0) {
		  // 
	//	  printf("Will bind %s\n", accesspoint.GetAccessString());
			Bind(accesspoint);
		//  printf("binded %s\n", accesspoint.GetAccessString());			
			AddRef();
			//DecRef();
		}
	}
	if (old != NULL) {
		__paroc_buf->Destroy();
		__paroc_buf = old;
	}
}

void paroc_interface::Allocate()
{
//  printf("INTERFACE: Allocate start\n");
	Release();
	POPString p;
	od.getProtocol(p);
	paroc_accesspoint jobcontact, objaccess, remotejobcontact;

	// With the actual code, batchsize is always zero
	if (batchindex<batchsize && batchindex>=1) {
		objaccess = batchaccesspoint[batchindex++];
		if (batchindex >= batchsize) {
			delete [] batchaccesspoint;
			batchindex = 0;
			batchsize = 0;
			batchaccesspoint = NULL;
		}
	} else if (!TryLocal(objaccess)) {
	  
		POPString objname(ClassName());
//    printf("INTERFACE: Will try to create a parallel object: %s\n", objname.GetString());
		//Exec using JobMgr interface...
		POPString platforms;
		od.getPlatforms(platforms);

		if (platforms.Length()<=0) {
//      printf("INTERFACE(Allocate): Will contact the appservice: %s\n", paroc_system::appservice.GetAccessString());		  
			/*CodeMgr mgr(paroc_system::appservice);
			if (mgr.GetPlatform(objname, platforms)<=0) {
				paroc_exception::paroc_throw(OBJECT_EXECUTABLE_NOTFOUND, ClassName());
			}
			od.setPlatforms(platforms);*/
		}
		//Global Resource management system --> Find a resource.

		POPString joburl;
		od.getJobURL(joburl);


		if  (joburl!=NULL)
		{
			jobcontact.SetAccessString(joburl);
		} else jobcontact=paroc_system::jobservice;

		if (jobcontact.IsEmpty())
		{
			char str[1024];
         DEBUG("INTERFACE - JOBMGR %s", (const char *)paroc_system::GetHost());
			sprintf(str,"%s:%d",(const char *)paroc_system::GetHost(),DEFAULTPORT);
			jobcontact.SetAccessString(str);
		}

	/*	try
		{
			DEBUG("JOBMGR --> connect to %s\n", jobcontact.GetAccessString());
			JobCoreService resources(jobcontact);
			int ret;
			if (batchindex==0 && batchsize>1)
			{
				if (batchaccesspoint!=NULL) delete [] batchaccesspoint;
				batchaccesspoint=new paroc_accesspoint[batchsize];
				DEBUG("Create Object : %s\n", ClassName());
            //TODO put an other array than batchaccesspoint
				ret=resources.CreateObject(paroc_system::appservice,objname,od, batchsize,  batchaccesspoint, batchsize, batchaccesspoint);
				if (ret==0) objaccess=batchaccesspoint[batchindex++];
            DEBUG("Return %d", ret);
			} else{
            
				DEBUG("Create Object : %s\n", ClassName());
            ret=resources.CreateObject(paroc_system::appservice,objname,od, 1,  &objaccess, 1, &remotejobcontact);
            DEBUG("Return %d", ret);
			}

			if (ret != 0) 
			  paroc_exception::paroc_throw(ret,ClassName());
         


      // Get the POPAppID
      AppCoreService acs(paroc_system::appservice);
      popAppId = acs.GetPOPCAppID();

		} catch (paroc_exception * e) {
			paroc_system::perror(e);
			paroc_exception::paroc_throw(POPC_JOBSERVICE_FAIL,"POP-C++ error: Cannot create object via POP-C++ Job Manager");
		} */
	}
	Bind(objaccess); 
}


void paroc_interface::Bind(const paroc_accesspoint &dest)
{
	if (dest.IsEmpty()) {
		Release();
		return;
	}

	accesspoint = dest;

	//Choose the protocol and then bind
	POPString prots = dest.GetAccessString();
	DEBUG("Access string %s : %s\n", ClassName(), dest.GetAccessString());
	POPString od_prots;
	od.getProtocol(od_prots);

	paroc_list<char *> accesslist, pref;

	Tokenize(prots,accesslist);
	ApplyCommPattern(getenv("POPC_COMM_PATTERN"),accesslist);

	Tokenize(od_prots,pref);

	if (pref.IsEmpty()) {
	  //printf("INTERFACE: Bind without preference \n");	
		//No preferred protocol in OD specified, try the first protocol in dest
		POSITION position = accesslist.GetHeadPosition();
		while (position !=NULL) {
			char *accesspoint = accesslist.GetNext(position);
			try {
//		  DEBUG("[Interface] Try to bind %s with : %s\n", ClassName(), addr);
				//printf("INTERFACE: %s Try to bind with : %s\n", ClassName(), accesspoint);
				Bind(accesspoint);
        //printf("INTERFACE: %s Bind succeed with: %s\n", ClassName(), accesspoint);				
				return;
			} catch (paroc_exception *e) {
				delete e;
				continue;
			}
		}
	} else {
		//The user specify the protocol in OD, select the preference and match with the access point...
		POSITION protocol_position = pref.GetHeadPosition();
		while (protocol_position != NULL) {
		  //printf("INTERFACE: Bind with preference\n");
			char *myprot = pref.GetNext(protocol_position);
			//Find access string that match myprot
			DEBUG("[Interface] protocol wanted for object %s : %s\n",ClassName(),  myprot);
			POSITION protocol_position = accesslist.GetHeadPosition();
			while (protocol_position != NULL) {
				char *addr = accesslist.GetNext(protocol_position);
				char pattern[1024];
				sprintf(pattern, "%s://*", myprot);
				if (paroc_utils::MatchWildcard(addr, pattern)) {
					try {
						Bind(addr);
						return;
					} catch (paroc_exception *e) {
						DEBUG("Can not bind to %s. Try next protocol...",addr);
						delete e;
						continue;
					}
				}
			}
		}
	}

	paroc_exception::paroc_throw(OBJECT_BIND_FAIL, ClassName());

}

/**
 *
 */
void paroc_interface::Bind(const char *dest)
{
  //printf("INTERFACE: Bind (%s) - %s\n", ClassName(), dest);
	Release();
	
	if (dest == NULL || *dest == 0) 
		return;


	paroc_combox_factory *comboxFactory = paroc_combox_factory::GetInstance();
	POPString p;
	comboxFactory->GetNames(p);
	if (comboxFactory == NULL) {
		paroc_exception::paroc_throw(POPC_NO_PROTOCOL, ClassName());
	}
	
		
	__paroc_combox = comboxFactory->Create("mpi");
	
	if (__paroc_combox == NULL) {
		paroc_exception::paroc_throw(POPC_NO_PROTOCOL, ClassName());
	}

	__paroc_buf = __paroc_combox->GetBufferFactory()->CreateBuffer();
	__paroc_combox->SetTimeout(paroc_bind_timeout);
	
  //printf("INTERFACE: Interface will create\n");
  bool combox_create_return = __paroc_combox->Create(NULL, 0, false);
  //printf("INTERFACE: Interface will connect\n");
  bool combox_connect_return = __paroc_combox->Connect(dest);
  
	if (combox_create_return && combox_connect_return) {
    //printf("INTERFACE: Interface connected\n");	
		int status;
		POPString info;
		POPString peerplatform;
		BindStatus(status, peerplatform, info);
		//printf("INTERFACE: Got bind status %d\n", status);
		
		switch (status) {
  		case BIND_OK:
	  		NegotiateEncoding(info, peerplatform);
       // printf("INTERFACE: Negotiate encoding done\n");	  		
		  	break;
  		case BIND_FORWARD_SESSION:
	  	case BIND_FORWARD_PERMANENT:
      {
			  paroc_accesspoint old(accesspoint);
  			paroc_accesspoint new_accesspoint;
	  		new_accesspoint.SetAccessString(info);
		  	//printf("INTERFACE: Forward current session to %s", (const char *)info);
			  Bind(new_accesspoint);
  			if (status == BIND_FORWARD_SESSION) 
  			  accesspoint = old;
	  		break;
		  }
  		default:
	  		//printf("INTERFACE: Unknown binding status");
		  	Release();
			  paroc_exception::paroc_throw(POPC_BIND_BAD_REPLY, ClassName());
		}
	} else {
	  //printf("Bind - exception create and connect the combox\n");
    int code = errno;
		Release();
		paroc_exception::paroc_throw(code, ClassName());
	}

  
	__paroc_combox->SetTimeout(-1);
  //printf("End of bind\n");
}

bool paroc_interface::TryLocal(paroc_accesspoint &objaccess)
{
  //printf("INTERFACE: TryLocal start\n");
	POPString hostname;
	POPString rarch;
	POPString codefile;
	POPString batch;

	POPString objname(ClassName());
	bool localFlag=od.IsLocal();

	od.getURL(hostname);
	od.getArch(rarch);
	od.getBatch(batch);

	if (localFlag || hostname!=NULL || batch!=NULL) {
    if (hostname==NULL) {
			hostname=paroc_system::GetHost();
		}

		od.getExecutable(codefile);
		
		//Hostname existed
		if (codefile==NULL)
		{
			//Lookup local code manager for the binary source....
			assert(!paroc_system::appservice.IsEmpty());
			/*CodeMgr mgr(paroc_system::appservice);
			if (rarch==NULL)rarch=paroc_system::platform;
			if (!mgr.QueryCode(objname,rarch,codefile))
			{
				paroc_exception::paroc_throw(OBJECT_NO_RESOURCE, ClassName());
				//else return false;
			}*/
		}

		//Local exec using sh or rsh
		char *hoststr=hostname.GetString();

		/**
		 * MPI Implementation for the K Computer
		 * MPI Process will be spawn here
		 */
		
		int status = LocalExec(hoststr, codefile, ClassName(), paroc_system::jobservice, paroc_system::appservice,&objaccess,1,od);		
		
		if (status != 0) {
			paroc_exception::paroc_throw(status, ClassName());
		}
		
		
		return (status==0);
	}
  //printf("INTERFACE: TryLocal failed\n");	
	return false;
}


void paroc_interface::Release()
{

	if (__paroc_combox!=NULL)
	{
	  paroc_connection* conn = __paroc_combox->get_connection();
	  if(conn != NULL && !accesspoint.IsService())
      DecRef();
      
		__paroc_combox->Destroy();
		__paroc_combox=NULL;
	}
	if (__paroc_buf!=NULL)
	{
		__paroc_buf->Destroy();
		__paroc_buf=NULL;
	}

/*
   if(_ssh_tunneling){
      int ret=0;
      ret = KillSSHTunnel(_ssh_user.c_str(), _ssh_dest_ip.c_str(), _ssh_dest_port, _ssh_local_port);
   }      */
}


bool paroc_interface::isBinded(){
	if (__paroc_combox == NULL || __paroc_buf == NULL) 
		return false;
	return true;
}




// ParocCall


/**
 * TODO Comment
 */
void paroc_interface::BindStatus(int &code, POPString &platform, POPString &info)
{
//  printf("INTERFACE: request bindstatus\n");
	if (__paroc_combox == NULL || __paroc_buf == NULL) 
	  return;
	  
	paroc_message_header h(0, 0, INVOKE_SYNC, "BindStatus");
	paroc_mutex_locker lock(_paroc_imutex);
	__paroc_buf->Reset();
	__paroc_buf->SetHeader(h);
	
	paroc_connection* connection = __paroc_combox->get_connection();
  popc_send_request(__paroc_buf, connection);
  popc_get_response(__paroc_buf, connection);

	__paroc_buf->Push("code", "int", 1);
	__paroc_buf->UnPack(&code, 1);
	__paroc_buf->Pop();

	__paroc_buf->Push("platform", "POPString", 1);
	__paroc_buf->UnPack(&platform, 1);
	__paroc_buf->Pop();

	__paroc_buf->Push("info", "POPString", 1);
	__paroc_buf->UnPack(&info, 1);
	__paroc_buf->Pop();
//  printf("INTERFACE: request bindstatus done\n");	
}


int paroc_interface::AddRef()
{
//  printf("Interface AddRef\n");
	if (__paroc_combox==NULL || __paroc_buf==NULL) return -1;
	paroc_message_header h(0,1, INVOKE_SYNC,"AddRef");
	paroc_mutex_locker lock(_paroc_imutex);
	__paroc_buf->Reset();
	__paroc_buf->SetHeader(h);
	paroc_connection* connection = __paroc_combox->get_connection();
  popc_send_request(__paroc_buf, connection);
  popc_get_response(__paroc_buf, connection);
	int ret;
	__paroc_buf->Push("refcount","int",1);
	__paroc_buf->UnPack(&ret,1);
	__paroc_buf->Pop();
	return ret;
}

int paroc_interface::DecRef()
{
//  printf("Interface DecRef %s\n", accesspoint.GetAccessString());
	if (__paroc_combox==NULL || __paroc_buf==NULL) return -1;
	paroc_message_header h(0, 2, INVOKE_SYNC,"DecRef");
	paroc_mutex_locker lock(_paroc_imutex);
	__paroc_buf->Reset();
	__paroc_buf->SetHeader(h);
	
	paroc_connection* connection = __paroc_combox->get_connection();
  popc_send_request(__paroc_buf, connection);
  popc_get_response(__paroc_buf, connection);
	int ret;
	__paroc_buf->Push("refcount","int",1);
	__paroc_buf->UnPack(&ret,1);
	__paroc_buf->Pop();
	return ret;
}


bool paroc_interface::Encoding(POPString encoding)
{
	if (__paroc_combox == NULL || __paroc_buf == NULL) 
	  return false;
	
	paroc_buffer_factory *fact = paroc_buffer_factory_finder::GetInstance()->FindFactory(encoding);
	if (fact == NULL) {
		DEBUG("No encoding factory for %s", (const char *)encoding);
		return false;
	}

	paroc_message_header h(0, 3, INVOKE_SYNC , "Encoding");
	paroc_mutex_locker lock(_paroc_imutex);
	__paroc_buf->Reset();
	__paroc_buf->SetHeader(h);

	__paroc_buf->Push("encoding", "POPString", 1);
	__paroc_buf->Pack(&encoding, 1);
	__paroc_buf->Pop();

	paroc_connection* connection = __paroc_combox->get_connection();
  
  popc_send_request(__paroc_buf, connection);
  popc_get_response(__paroc_buf, connection);
	
	bool ret;
	__paroc_buf->Push("result", "bool", 1);
	__paroc_buf->UnPack(&ret, 1);
	__paroc_buf->Pop();

	if (ret) {
		__paroc_buf->Destroy();
		__paroc_buf=fact->CreateBuffer();
		__paroc_combox->SetBufferFactory(fact);
	}
	
	connection->reset();
	return ret;
}

void paroc_interface::Kill()
{
	if (__paroc_combox==NULL) return;
	paroc_message_header h(0,4, 0 ,"Kill");
	paroc_mutex_locker lock(_paroc_imutex);
	__paroc_buf->Reset();
	__paroc_buf->SetHeader(h);

	paroc_Dispatch(__paroc_buf);
	__paroc_combox->RecvAck();

	Release();
}

bool paroc_interface::ObjectActive()
{
	if (__paroc_combox==NULL || __paroc_buf==NULL) return false;
	paroc_message_header h(0,5, INVOKE_SYNC ,"ObjectActive");
	paroc_mutex_locker lock(_paroc_imutex);
	__paroc_buf->Reset();
	__paroc_buf->SetHeader(h);
	paroc_Dispatch(__paroc_buf);
	paroc_Response(__paroc_buf);
	bool ret;
	__paroc_buf->Push("result","bool",1);
	__paroc_buf->UnPack(&ret,1);
	__paroc_buf->Pop();
	return ret;
}
#ifdef OD_DISCONNECT
bool paroc_interface::RecvCtrl()
{
	int  time_alive;
	int  time_control;
	int oldTimeout = __paroc_combox->GetTimeout();
	od.getCheckConnection(time_alive, time_control);
	if (__paroc_combox==NULL || __paroc_buf==NULL) {__paroc_combox->SetTimeout(oldTimeout); return false;};
	char header_name [] = "ObjectAlive\0";
	paroc_message_header h(0,6, INVOKE_SYNC ,header_name);
	paroc_mutex_locker lock(_paroc_imutex);
	while (true) {
		__paroc_combox->SetTimeout(time_control);
		paroc_connection *t = (paroc_connection *) __paroc_combox->Wait();
		if (t != NULL)
			if (!__paroc_buf->Recv(*__paroc_combox,t)) {
				__paroc_combox->SetTimeout(oldTimeout);
				paroc_exception::paroc_throw(errno);
			} else {
				__paroc_combox->SetTimeout(oldTimeout);
				return true;
			}
		__paroc_buf->Reset();
		__paroc_buf->SetHeader(h);
		if (!__paroc_buf->Send(*__paroc_combox)) {__paroc_combox->SetTimeout(oldTimeout); paroc_exception::paroc_throw(errno);}
		__paroc_combox->SetTimeout(time_alive);
		if (!__paroc_buf->RecvCtrl(*__paroc_combox)) {__paroc_combox->SetTimeout(oldTimeout); return true;}
	}
	__paroc_combox->SetTimeout(oldTimeout);
	return false;
}
#endif

void paroc_interface::NegotiateEncoding(POPString &enclist, POPString &peerplatform)
{
//  printf("INTERFACE: Negotiate encoding start\n");
	POPString preferred_encoding;
	od.getEncoding(preferred_encoding);
	paroc_list<char *> encoding_preference, encoding_available;
	Tokenize(preferred_encoding, encoding_preference);
	Tokenize(enclist, encoding_available);

	POPString current_encoding;
	__paroc_combox->GetBufferFactory()->GetBufferName(current_encoding);

	if (encoding_preference.IsEmpty()) {
    POSITION pos = encoding_available.GetHeadPosition();
		while (pos != NULL) {
			char *enc = encoding_available.GetNext(pos);
			if (paroc_utils::MatchWildcard(enc,"raw*") && !paroc_utils::isEqual(peerplatform, paroc_system::platform)) 
			  continue;
			if (paroc_utils::isncaseEqual(enc, current_encoding) || Encoding(enc)) 
			  return;
		}
	} else {
		POSITION prefpos = encoding_preference.GetHeadPosition();
		while (prefpos) {
			char *test = encoding_preference.GetNext(prefpos);
			POSITION pos = encoding_available.GetHeadPosition();
			while (pos != NULL) {
				char *enc = encoding_available.GetNext(pos);
				if (paroc_utils::MatchWildcard(enc,test)) {
					if (paroc_utils::isncaseEqual(enc, "raw") && !paroc_utils::isEqual(peerplatform,paroc_system::platform)) 
					  continue;
					if (paroc_utils::isncaseEqual(enc, current_encoding) || Encoding(enc)) 
					  return;
				}
			}
		}
	}

	paroc_exception::paroc_throw(POPC_NO_ENCODING, ClassName());
}

int paroc_interface::LocalExec(const char *hostname, const char *codefile, const char *classname, const paroc_accesspoint &jobserv, const paroc_accesspoint &appserv, paroc_accesspoint *objaccess, int howmany, const paroc_od& od)
{  
	if (codefile==NULL) 
		return ENOENT;
	signal(SIGCHLD, SIG_IGN);

	while (isspace(*codefile)) {
		codefile++;
	}	
	

	char tmpstr[10240];
	const char *argv[1024];
	char *tmp;

	bool isManual = od.getIsManual();

#ifdef OD_DISCONNECT
	bool checkConnection=od.getCheckConnection();
#endif

	POPString ruser;
	POPString rcore;
	const char *rport=NULL;
	POPString batch;
	POPString cwd;

	if (hostname != NULL && (tmp = (char*)strchr(hostname, ':')) != NULL) {
		*tmp = 0;
		rport = tmp + 1;
	}
	od.getUser(ruser);
	od.getCore(rcore);
	od.getBatch(batch);
	od.getDirectory(cwd);

	int n = 0;
	/*POPString myhost = paroc_system::GetHost();
	bool islocal = (isManual || hostname == NULL || *hostname == 0 || paroc_utils::SameContact(myhost, hostname) || paroc_utils::isEqual(hostname, "localhost") || paroc_utils::isEqual(hostname, "127.0.0.1"));
	if (batch == NULL) {
		if (!islocal) {
			char *tmp = getenv("POPC_RSH");
			argv[n++] = strdup((tmp == NULL) ? "/usr/bin/ssh" : tmp);
			//      argv[n++]=strdup("-n");
			// Add user name to host for ssh
			if (ruser != NULL && *ruser != 0) {
				char tmpstr[100];
				sprintf(tmpstr, "%s@%s", (const char*)ruser, (const char*)hostname);
				argv[n++] = strdup(tmpstr);
			} else {
				argv[n++] = strdup(hostname);
			}
		}
	}
/*	else {
		char tmpstr[100];
		tmp=getenv("POPC_LOCATION");
		if (tmp!=NULL) sprintf(tmpstr,"%s/services/popcobjrun.%s",tmp,(const char*)batch);
		else sprintf(tmpstr,"popcobjrun.%s",(const char*)batch);
		argv[n++]=strdup(tmpstr);
		if (!islocal)
		{

			BatchMgr batchman(paroc_system::appservice);
			sprintf(tmpstr,"-batch-node=%d",batchman.NextNode());
			DEBUG("%s",tmpstr);
			argv[n++]=strdup(tmpstr);
		}
	}*/

/*	tmp=getenv("POPC_LOCATION");
	if (tmp!=NULL) 
		sprintf(tmpstr,"%s/services/popcobjrun",tmp);
	else 
		strcpy(tmpstr,"popcobjrun");
	argv[n++] = strdup(tmpstr);*/


	/*strcpy(tmpstr,codefile);
	char *tok=strtok_r(tmpstr," \t\n",&tmp);
	while (tok!=NULL)
	{
		argv[n++]=strdup(tok);
		tok=strtok_r(NULL," \t\n",&tmp);
	}*/

	/*paroc_combox_socket tmpsock;
   bool isServer=true;
	if (!tmpsock.Create(0,isServer)) paroc_exception::paroc_throw_errno();
	POPString cburl;
	tmpsock.GetUrl(cburl);

	
	sprintf(tmpstr,"-callback=%s", (const char*)cburl);
	argv[n++]=strdup(tmpstr);*/
	
  //paroc_combox_factory *comboxFactory = paroc_combox_factory::GetInstance();
//  paroc_combox callback_combox = comboxFactory->Create((const char*)"mpi");  
//  paroc_combox* callback_combox =  comboxFactory->Create((const char*)"mpi");
//  if(!callback_combox->Create(NULL, 0, true))
//    paroc_exception::paroc_throw_errno();
//  POPString callback_url; 
//  callback_combox->GetUrl(callback_url);
  
//  sprintf(tmpstr, "-callback=%s", (const char*)callback_url);
//  argv[n++] = strdup(tmpstr);
	
	argv[n++]=strdup("-mpi");

	if (classname!=NULL)
	{
		sprintf(tmpstr,"-object=%s", classname);
		argv[n++]=strdup(tmpstr);
	}
	if (!appserv.IsEmpty())
	{
		sprintf(tmpstr,"-appservice=%s",appserv.GetAccessString());
		argv[n++]=strdup(tmpstr);
	}

	/*if (!jobserv.IsEmpty())
	{
		sprintf(tmpstr,"-jobservice=%s",jobserv.GetAccessString());
		argv[n++]=strdup(tmpstr);
	}*/
	// Select core
	if (rcore!=NULL&&rcore!=0) {
		sprintf(tmpstr,"-core=%s",(const char*)rcore);
		argv[n++]=strdup(tmpstr);
	}

	/*if (rport!=NULL && *rport!=0)
	{
		sprintf(tmpstr,"-socket_port=%s",rport);
		argv[n++]=strdup(tmpstr);
	}*/
	
#ifdef OD_DISCONNECT
	if (checkConnection) {
		sprintf(tmpstr,"-checkConnection");
		argv[n++]=strdup(tmpstr);
	}
#endif

	if (paroc_od::defaultLocalJob) {
		argv[n++]=strdup("-runlocal");
	}

	// Add the working directory as argument
	if (cwd!=NULL && *cwd!=0) {
		sprintf(tmpstr,"-cwd=%s",(const char*)cwd);
		argv[n++]=strdup(tmpstr);
	}

	argv[n]=NULL;

	int ret=0, err=0;


  /**
   * Run the parallel object
   */


	// Create a string with all args
	std::string executable_args;
  for (int i=0;i<n;i++) {
    executable_args.append(argv[i]);
    executable_args.append(" ");
  }
    

  
  // TODO constant instead of numbers
  // Get the next free object
  int dest; 
  int cmd = 1; 
  MPI::COMM_WORLD.Send(&cmd, 1, MPI_INT, 1, 10);
  int length = strlen(classname);
  MPI::COMM_WORLD.Send(&length, 1, MPI_INT, 1, 11);
  MPI::COMM_WORLD.Send(classname, length, MPI_CHAR, 1, 12);  
  MPI::COMM_WORLD.Recv(&dest, 1, MPI_INT, 1, 13);
  
  if(dest < 0)
    paroc_exception::paroc_throw(ALLOCATION_EXCEPTION,"POP-C++ error: Cannot create object via POP-C++ (MPI pool of object is not big enough)");
  
  /*printf("INTERFACE: allocate idle %d with %s %s\n", dest, codefile, executable_args.c_str());  
  paroc_system::current_free_process++;
  int length = strlen(codefile);
  MPI::COMM_WORLD.Send(&length, 1, MPI_INT, dest, 0);
  MPI::COMM_WORLD.Send(codefile, length, MPI_CHAR, dest, 1);
  length = executable_args.length();
  MPI::COMM_WORLD.Send(&length, 1, MPI_INT, dest, 2);
  MPI::COMM_WORLD.Send(executable_args.c_str(), length, MPI_CHAR, dest, 3);
	*/
	// Send dummy data to the created parallel object to get its rank
  
  MPI::COMM_WORLD.Send(&dest, 1, MPI_INT, dest, 15);
	int check_rank;
	MPI::COMM_WORLD.Recv(&check_rank, 1, MPI_INT, dest, 16);

	/**
	 * Create the new MPI process with the code
	 */
		
	// TODO dynamic path finding of popc_accept_broker
  /*const char* spawn_executable[2] = { };
  const char** spawn_arg_commands[2];
  const char* spawn_dummy_args[] = {(char*)0};  
  spawn_arg_commands[0] = argv;
  spawn_arg_commands[1] = spawn_dummy_args;
  int maxprocs[2] = {1, 1};
  MPI::Info spawn_infos[2] = { MPI_INFO_NULL, MPI_INFO_NULL };		
  int spawn_errcodes[2];
  		
	MPI::Intercomm brokers_intercomm;	
	brokers_intercomm = paroc_system::popc_self.Spawn_multiple(2, spawn_executable, spawn_arg_commands, maxprocs, spawn_infos, 0, spawn_errcodes);
	
	
	// Getting the broker accesspoints
	int port_name_length;
  brokers_intercomm.Recv(&port_name_length, 1, MPI_INT, 0, 0);
  char* tmp_port_name = new char[port_name_length+1];
  brokers_intercomm.Recv(tmp_port_name, port_name_length, MPI_CHAR, 0, 1);
  tmp_port_name[port_name_length] = '\0';
  std::string port_name_broker(tmp_port_name);
  delete [] tmp_port_name;
  
  // Getting the accept broker accesspoint
  brokers_intercomm.Recv(&port_name_length, 1, MPI_INT, MPI_ANY_SOURCE, 2);
  tmp_port_name = new char[port_name_length+1];      
  brokers_intercomm.Recv(tmp_port_name, port_name_length, MPI_CHAR, MPI_ANY_SOURCE, 3);
  tmp_port_name[port_name_length] = '\0';
  std::string port_name_accept_broker(tmp_port_name);
  delete [] tmp_port_name;*/
	

	//printf("INTERFACE: STEP 1 - New object spawned: %s // %s // %s\n", codefile, port_name_accept_broker.c_str(), port_name_broker.c_str());
	
	/*if(spawn_errcodes[0] != MPI_SUCCESS){
	  // LOG 
		//printf("INTERFACE: ERROR - Something went wrong with Spawn\n");
		paroc_exception::paroc_throw(err, classname);		
	}*/

	err = errno;
	
	// Put together the accesspoints of the brokers 
	/*std::string tmp_accesspoint;
	tmp_accesspoint.append("mpi://");
	tmp_accesspoint.append(port_name_accept_broker);
	tmp_accesspoint.append("__");
	tmp_accesspoint.append(port_name_broker);*/
	
	std::stringstream tmp_accesspoint;
	tmp_accesspoint << "mpi://";
	tmp_accesspoint << dest;
	
	// Saving the object accesspoint
	objaccess->SetAccessString(tmp_accesspoint.str().c_str());
	
	//printf("INTERFACE: objaccess %s\n", objaccess->GetAccessString());

	/*for (int i=0;i<n;i++) 
		if (argv[i]!=NULL) 
			free(argv[i]); */
	
	return 0;
}


void paroc_interface::Tokenize(POPString &s, paroc_list<char *> &tokens)
{
	char *t = s.GetString();
	if (t == NULL) 
	  return;
	char sep[] = " \n\t";
	char *ptrptr;
	char *tok=strtok_r(t, sep, &ptrptr);

	while (tok != NULL) {
		tokens.AddTail(tok);
		tok = strtok_r(NULL, sep, &ptrptr);
	}
}

void paroc_interface::ApplyCommPattern(const char *pattern, paroc_list<char *> &accesslist)
{
	if (pattern == NULL) 
	  return;
	  
	POPString p(pattern);
	paroc_list<char *> patternlist;
	Tokenize(p, patternlist);

	POSITION ptpos = patternlist.GetHeadPosition();
	POSITION headpos = accesslist.GetHeadPosition();
	while (ptpos!=NULL) {
		char *ptstr = patternlist.GetNext(ptpos);
		if (ptstr == NULL) continue;
		POSITION pos = headpos;
		while (pos!=NULL) {
			POSITION old = pos;
			char *t = accesslist.GetNext(pos);
			if (paroc_utils::MatchWildcard(t,ptstr)) {
				if (headpos != old) {
					accesslist.InsertBefore(headpos, t);
					accesslist.RemoveAt(old);
				} else {
					accesslist.GetNext(headpos);
					if (headpos == NULL) 
					  return;
				}
			}

		}
	}
}

/**
 * TODO Comment
 */
void paroc_interface::popc_send_request(paroc_buffer *buf, paroc_connection* conn)
{
  if (!buf->Send((*__paroc_combox), conn)) {
	  paroc_exception::paroc_throw_errno();
	}   
}

/**
 * TODO Comment
 */
void paroc_interface::popc_get_response(paroc_buffer *buf, paroc_connection* conn)
{
	if (!buf->Recv((*__paroc_combox), conn)) {
    paroc_exception::paroc_throw_errno();	
	}
	paroc_buffer::CheckAndThrow(*buf);
}

void paroc_interface::paroc_Dispatch(paroc_buffer *buf)
{
	if (!buf->Send((*__paroc_combox), __paroc_connection)) {
	  paroc_exception::paroc_throw_errno();
	}
	//printf("INTERFACE: paroc_dispatch connection %s\n", (__paroc_connection == NULL) ? "is null" : "is not null");
}

void paroc_interface::paroc_Response(paroc_buffer *buf)
{
	if (!buf->Recv((*__paroc_combox))){
    paroc_exception::paroc_throw_errno();	
	}
	//printf("INTERFACE: paroc_response will disconnect the connection\n");
	__paroc_connection->reset();
	paroc_buffer::CheckAndThrow(*buf);
}



/* ################################################################################################
 *                                 SSH TUNNELING FUNCTION
/* ################################################################################################





/**
 * ViSaG : clementval
 * Create a SSH Tunnel from the local IP to the destination IP
 * @param user       User who initiate the SSH Tunnel (not used yet) TODO
 * @param dest_ip    Destination IP of the SSH Tunnel
 * @param dest_port  Destination port of the SSH Tunnel
 * @param local_port Local port of the SSH Tunnel
 * @return PID of the SSH Tunnel on success, -1 if the SSH Tunnel can't be created
 */
int paroc_interface::CreateSSHTunnel(const char *user, const char *dest_ip, int dest_port){
   popc_interface_log("Create tunnel");
   //Save the SSH Tunnel information 
   _ssh_user.erase(_ssh_user.begin(), _ssh_user.end());
   _ssh_user.insert(0, user);
   _ssh_dest_ip.erase(_ssh_dest_ip.begin(), _ssh_dest_ip.end());
   _ssh_dest_ip.insert(0, dest_ip);
   _ssh_dest_port = dest_port;


   _ssh_tunneling = true;
   srand(time(NULL));   //Init the random generator with the current time
   int BUF_SIZE=15;
   char buf[BUF_SIZE];
   FILE *fp;
   int attempt=0;
   int error_code=0;
   int local_port;
   std::ostringstream cmd; 

   do{
      error_code=0;
      local_port = (rand() % SSH_PORT_MOD) + SSH_PORT_FIRST; 
     // DEBUG("SSH TUNNELING ON %s:%d",dest_ip, local_port);
      cmd.str("");  
      cmd.clear();
      cmd << "/usr/bin/ssh -f -N -q -o ExitOnForwardFailure=yes -L" << local_port << ":127.0.0.1:" << dest_port << " " << _ssh_dest_ip << " && echo TUNNEL_OPEN";

      
      fp = popen(cmd.str().c_str(), "r");
      if(fp==NULL) error_code=-1;   
      if(fgets(buf, BUF_SIZE, fp) == NULL) error_code=-1;
   } while(error_code!=0 && attempt++ < SSH_MAX_ATTEMPT); 
   if(error_code==0){
      _ssh_local_port = local_port;
      return local_port;
   } else {
      //paroc_exception::paroc_throw(OBJECT_EXECUTABLE_NOTFOUND, ClassName());
   }
   return error_code;
}

/**
 * ViSaG : clementval
 * Kill a SSH Tunnel
 * @param user       User who initiate the SSH Tunnel (not used yet) TODO
 * @param dest_ip    Destination IP of the SSH Tunnel
 * @param dest_port  Destination port of the SSH Tunnel
 * @param local_port Local port of the SSH Tunnel
 * @return PID if the proccess is killed, -1 if the method can't find the SSH Tunnel PID, -2 if the method can't read the PID
 */
int paroc_interface::KillSSHTunnel(const char *user, const char *dest_ip, int dest_port, int local_port){
   popc_interface_log("Kill SSH");
   _ssh_tunneling = false;
   if(dest_ip == NULL)
      return -1;

   int BUF_SIZE=100;
   char buf[BUF_SIZE];
//warning_remove   int error_code=0;

   std::ostringstream cmd;      
   cmd << "ps aux | grep \"/usr/bin/ssh -f -N -q -o ExitOnForwardFailure=yes -L" << local_port << ":127.0.0.1:" << dest_port << " " << dest_ip << "\" | grep -v grep | head -n 1 | awk -F\" \" '{print $2}'";
   FILE *fp;
   fp = popen(cmd.str().c_str(), "r");
   if(fp==NULL) return -1;
   if(fgets(buf, BUF_SIZE, fp) == NULL) return -2;
   int pid = atoi(buf);
   DEBUG("KILL SSH-T REQUESTED (user=%s, lport=%d, dport=%d, dip=%s, PID=%d)",user, local_port, dest_port, dest_ip, pid);
   if(pid!=0)
      kill(pid, SIGKILL);
   return pid;
   return 0;
}

/**
 * ViSaG : clementval
 * Check if the SSH Tunnel is alive
 * @param user       User who initiate the SSH Tunnel (not used yet) TODO
 * @param dest_ip    Destination IP of the SSH Tunnel
 * @param dest_port  Destination port of the SSH Tunnel
 * @param local_port Local port of the SSH Tunnel
 * @return TRUE if the SSH Tunnel is alive, FALSE if the SSH Tunnel is not alive
 */
bool paroc_interface::IsTunnelAlive(const char *user, const char *dest_ip, int dest_port, int local_port){
   std::ostringstream cmd;
   int BUF_SIZE=6;
   char res[BUF_SIZE];
   FILE *fp;
   cmd << "ps aux | grep \"/usr/bin/ssh -f -N -o ExitOnForwardFailure=yes -L" << local_port << ":127.0.0.1:" << dest_port << " " << dest_ip << "\" | grep -v grep | awk -F\" \" '{print $2}'";

   fp = popen(cmd.str().c_str(), "r");
   if(fp == NULL)
      return -1;

   fgets(res, BUF_SIZE, fp);
   
   int pid = atoi(res);
   if(pid != 0)
      return true;
   return false;
}


/**
 * ViSaG : clementval
 * Write log into the Security Manager log file
 * WARNING : use this method only in development
 */
int paroc_interface::popc_interface_log(const char *log)
{
	char *tmp=getenv("POPC_TEMP");
	char logfile[256];
	if (tmp!=NULL) sprintf(logfile,"%s/popc_interface_log",tmp);
	else strcpy(logfile, "/tmp/popc_interface.log");

	FILE *f=fopen(logfile,"a");
	if (f==NULL) return 1;
	time_t t=time(NULL);
	fprintf(f, "%s", ctime(&t));
	/*va_list ap;
	va_start(ap, log);
	vfprintf(f, log, ap);*/
	fprintf(f, "%s\n", log);
	//va_end(ap);
	fclose(f);
	return 0;
}

