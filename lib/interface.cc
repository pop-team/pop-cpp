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
#include "codemgr.ph"
#include "batchmgr.ph"
#include "paroc_combox_factory.h"

#include "appservice.ph"
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

//paroc_interface base class

paroc_interface::paroc_interface()
{

 // DEBUG("CREATING INTERFACE DEFAULT %s (OD:%s)", ClassName(), (od.isSecureSet())?"true":"false");
   if(od.isSecureSet()) accesspoint.SetSecure();
   _ssh_tunneling=false;
	__paroc_combox=NULL;
	__paroc_buf=NULL;
	//_popc_async_construction_thread=NULL;

}

paroc_interface::paroc_interface(const paroc_accesspoint &p)
{


   
   _ssh_tunneling=false;
   if(p.IsService())
      accesspoint.SetAsService();
	__paroc_combox=NULL;
	__paroc_buf=NULL;
	//_popc_async_construction_thread=NULL;	

   if(!p.IsEmpty());
   	Bind(p);

   if(p.GetNoAddRef()) DecRef();
   
}





paroc_interface::paroc_interface(const paroc_interface &inf)
{
   paroc_accesspoint infAP = inf.GetAccessPoint();
   _ssh_tunneling=false;
	__paroc_combox=NULL;
	__paroc_buf=NULL;
	//_popc_async_construction_thread=NULL;	

   if(infAP.IsSecure())
      accesspoint.SetSecure();
   if(infAP.IsService())
      accesspoint.SetAsService();
 
  
   
	Bind(inf.GetAccessPoint());

   
}

paroc_interface::paroc_interface(paroc_combox *combox, paroc_buffer *buffer)
{
   _ssh_tunneling=false;
	__paroc_combox=combox;
	__paroc_buf=buffer;
	//_popc_async_construction_thread=NULL;	
	if (combox!=NULL)
	{
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
   if(!accesspoint.IsService()){
     // DecRef();
   }
	Release();
}

paroc_interface & paroc_interface::operator = (const paroc_interface & obj)
{
	Release();
	const paroc_accesspoint &res=obj.GetAccessPoint();
	Bind(res);
	return (*this);
}

void paroc_interface::SetOD(const paroc_od &myod)
{
	od=myod;
}

const paroc_od & paroc_interface::GetOD() const
{
	return od;
}


// const char * paroc_interface::GetResource() const
// {
//   return resource;
// }

const paroc_accesspoint &  paroc_interface::GetAccessPoint() const
{
	return accesspoint;
}
/**
 * Get the accesspoint of the parallel object and set the _noaddref variavle to TRUE
 */
const paroc_accesspoint &  paroc_interface::GetAccessPointForThis()
{
   accesspoint.SetNoAddRef();
	return accesspoint;
}

void paroc_interface::Serialize(paroc_buffer &buf, bool pack)
{

   /**
    * ViSaG : clementval
    * Add the current node to the way back to the node running the object
    */
#if defined POPC_SECURE || defined POPC_SECURE_VIRTUAL
   if(pack && !accesspoint.IsService()){
      try{
         JobCoreService jcs(paroc_system::jobservice);
         wayToNode.insertNode(jcs.getPSMRef().GetAccessString());
      } catch (...){
         popc_interface_log("Secure version used without Global Services");
      }
   }
#endif
	buf.Push("od","paroc_od",1);
	od.Serialize(buf,pack);
	buf.Pop();

	buf.Push("accesspoint","paroc_accesspoint",1);
	accesspoint.Serialize(buf,pack);
	buf.Pop();

#if defined POPC_SECURE || defined POPC_SECURE_VIRTUAL
   /**
    * ViSaG : clementval
    * Marshall/Unmarshall the way back to the node
    */
   buf.Push("wayToNode", "POPwayback", 1);
   wayToNode.Serialize(buf, pack);
   buf.Pop();
#endif
	paroc_buffer *old=NULL;

#if defined POPC_SECURE || defined POPC_SECURE_VIRTUAL
   /**
    * ViSaG : clementval
    * Marshall/Unmarshall the POPAppID
    */
   if(pack){
      buf.Push("popAppId", "POPString", 1);
      buf.Pack(&popAppId, 1);
      buf.Pop();
   } else {
      buf.Push("popAppId", "POPString", 1);
      buf.UnPack(&popAppId, 1);
      buf.Pop();
   }
#endif

   /**
    * ViSaG : clementval
    * Send the pki to the node running the parallel object
    */
#if defined POPC_SECURE || defined POPC_SECURE_VIRTUAL
   if(!pack && !accesspoint.IsService()){
      try{
         JobCoreService jcs(paroc_system::jobservice);
         POPCSecurityManager psm(jcs.getPSMRef());
         POPString emptyPKI("");
         psm.rerouteRef(wayToNode, emptyPKI, popAppId);
      } catch(...){
         popc_interface_log("Secure version used without Global Services");
      }
   }
#endif

	if (&buf==__paroc_buf)
	{
		old=&buf;
		__paroc_buf=__paroc_combox->GetBufferFactory()->CreateBuffer();
	}


	if (pack)
	{
		int ref=AddRef();
		buf.Push("refcount","int",1);
		buf.Pack(&ref,1);
		buf.Pop();
	}
	else
	{
		int ref;
		buf.Push("refcount","int",1);
		buf.UnPack(&ref,1);
		buf.Pop();
		if (ref>0)
		{
			Bind(accesspoint);
			DecRef();
		}
	}
	if (old!=NULL)
	{
		__paroc_buf->Destroy();
		__paroc_buf=old;
	}
}

void paroc_interface::Allocate()
{
	Release();
	POPString p;
	od.getProtocol(p);
	paroc_accesspoint jobcontact, objaccess, remotejobcontact;

	// With the actual code, batchsize is always zero
	if (batchindex<batchsize && batchindex>=1)
	{
		objaccess=batchaccesspoint[batchindex++];
		if (batchindex>=batchsize)
		{
			delete [] batchaccesspoint;
			batchindex=0;
			batchsize=0;
			batchaccesspoint=NULL;
		}
	}
	else if (!TryLocal(objaccess))
	{

		POPString objname(ClassName());

		//Exec using JobMgr interface...
		POPString platforms;
		od.getPlatforms(platforms);

		if (platforms.Length()<=0)
		{
			CodeMgr mgr(paroc_system::appservice);
			if (mgr.GetPlatform(objname, platforms)<=0)
			{
				paroc_exception::paroc_throw(OBJECT_EXECUTABLE_NOTFOUND, ClassName());
			}
			od.setPlatforms(platforms);
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

		try
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
			}
			else{
            
				DEBUG("Create Object : %s\n", ClassName());
            ret=resources.CreateObject(paroc_system::appservice,objname,od, 1,  &objaccess, 1, &remotejobcontact);
            DEBUG("Return %d", ret);
			}

			if (ret!=0) paroc_exception::paroc_throw(ret,ClassName());
         


         //Get the POPAppID
         AppCoreService acs(paroc_system::appservice);
         popAppId = acs.GetPOPCAppID();

#if defined POPC_SECURE || defined POPC_SECURE_VIRTUAL

         bool isEndPointRunningJobMgr=true;
         paroc_accesspoint jcs_ap;
         char joburl[100];
         sprintf(joburl, "socket://%s:2711", paroc_utils::GetIPFromURL(objaccess.GetAccessString()));   
         DEBUG("Insert Node from %s", joburl);
         jcs_ap.SetAccessString(joburl);

         //Check if the node running the object as a POP-C++ Global Services
         try{
            JobCoreService jcs(jcs_ap);
            wayToNode.insertNode(jcs.getPSMRef().GetAccessString());
         } catch (paroc_exception * e){
            popc_interface_log("Node running the object has not POP-C++ GS");
            isEndPointRunningJobMgr=false;
         }
               

         //If Virtual, the node to add to way back is the admin node
         if(!isEndPointRunningJobMgr){
            JobCoreService virtNodeAP(remotejobcontact);
            sprintf(log, "Add jobmgr as last node to way back %s", virtNodeAP.getPSMRef().GetAccessString());
            popc_interface_log(log);
            wayToNode.insertNode(virtNodeAP.getPSMRef().GetAccessString());
         }
#endif           

		}
		catch (paroc_exception * e)
		{
			paroc_system::perror(e);
			paroc_exception::paroc_throw(POPC_JOBSERVICE_FAIL,"POP-C++ error: Cannot create object via POP-C++ Job Manager");
		}
	}
   //Add for SSH Tunneling
   if(od.isSecureSet()) objaccess.SetSecure();
   if(od.isServiceSet()) objaccess.SetAsService();

	Bind(objaccess); 
	
	//pthread_kill(_popc_async_construction_thread, 0); */
}


void paroc_interface::Bind(const paroc_accesspoint &dest)
{
	if (dest.IsEmpty())
	{
		Release();
		return;
	}

	accesspoint=dest;

	//Choose the protocol and then bind...
	POPString prots=dest.GetAccessString();
	DEBUG("Access string %s : %s\n", ClassName(), dest.GetAccessString());
	POPString od_prots;
	od.getProtocol(od_prots);

	paroc_list<char *> accesslist, pref;

	Tokenize(prots,accesslist);
	ApplyCommPattern(getenv("POPC_COMM_PATTERN"),accesslist);

	Tokenize(od_prots,pref);

	if (pref.IsEmpty())
	{
		//No preferred protocol in OD specified, try the first protocol in dest
		POSITION pos=accesslist.GetHeadPosition();
		while (pos!=NULL)
		{
			char *addr=accesslist.GetNext(pos);
			try {
				DEBUG("[Interface] Try to bind %s with : %s\n", ClassName(), addr);
				Bind(addr);
				return;
			}
			catch (paroc_exception *e)
			{
				//	      DEBUG("Can not bind to %s. Try next protocol...",addr);
				delete e;
				continue;
			}
		}
	}
	else
	{
		//The user specify the protocol in OD, select the preference and match with the access point...
		POSITION protpos=pref.GetHeadPosition();
		while (protpos!=NULL)
		{
			char *myprot=pref.GetNext(protpos);
			//Find access string that match myprot
			DEBUG("[Interface] protocol wanted for object %s : %s\n",ClassName(),  myprot);
			POSITION pos=accesslist.GetHeadPosition();
			while (pos!=NULL)
			{
				char *addr=accesslist.GetNext(pos);
				char pattern[1024];
				if(strcmp(myprot, "socket2")==0)
					sprintf(pattern,"%s://*","socket");
				else
					sprintf(pattern,"%s://*",myprot);
				if (paroc_utils::MatchWildcard(addr,pattern))
				{
					try {
						Bind(addr);
						return;
					}
					catch (paroc_exception *e)
					{
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

void paroc_interface::Bind(const char *dest)
{
	DEBUG("Bind to : %s\n", dest);
	Release();
	if (dest==NULL || *dest==0) return;

#if defined POPC_SECURE || defined POPC_SECURE_VIRTUAL
   int local_port=0;
   bool ssh_tunnel=false;
   char spoof_dest[100];

   
   DEBUG("DESTINATION_BEFORE_SSH:%s", dest);
   //Create a SSH Tunnel for the remote secure connection
   if(paroc_utils::IsRemoteDest(dest)){
      DEBUG("SSH TUNNELING ...");
      int dest_port = paroc_utils::GetPortFromURL(dest);
      std::string dest_ip(paroc_utils::GetIPFromURL(dest));
      std::string user("visag"); //paroc_utils::GetCurrentUser());
      
      local_port = CreateSSHTunnel(user.c_str(), dest_ip.c_str(), dest_port);
      //sprintf(log, "SSH TUNNELLING REQUESTED (user=%s, lport=%d, dport=%d, dip=%s)",user.c_str(), local_port, dest_port, dest_ip.c_str());
      //popc_interface_log(log);
      ssh_tunnel=true;
      accesspoint.SetSecure();
   }
#endif
	char protsep[]="://";
	char prot[256];
	char *tmp=(char*)strstr(dest,protsep);
	char defaultprot[]="socket";

	if (tmp==NULL)
	{
		//Default: use socket!
		strcpy(prot,defaultprot);
	}
	else
	{
		int sz=tmp-dest;
		strncpy(prot,dest,sz);
		prot[sz]=0;
	}

	paroc_combox_factory *fact=paroc_combox_factory::GetInstance();
	DEBUG("%s prot list:", ClassName());
	POPString p;
	fact->GetNames(p);
	if (fact==NULL) paroc_exception::paroc_throw(POPC_NO_PROTOCOL, ClassName());

	__paroc_combox=fact->Create(prot);
	if (__paroc_combox==NULL) paroc_exception::paroc_throw(POPC_NO_PROTOCOL, ClassName());

	__paroc_buf=__paroc_combox->GetBufferFactory()->CreateBuffer();

	__paroc_combox->SetTimeout(paroc_bind_timeout);

#if defined POPC_SECURE || defined POPC_SECURE_VIRTUAL
   //Fake the destination if SSH Tunneling 
   if(ssh_tunnel) sprintf(spoof_dest, "%s://%s:%d", prot, "127.0.0.1", local_port);
   else sprintf(spoof_dest, "%s", dest);
   bool isServer =false;
	if (__paroc_combox->Create(0, isServer) && __paroc_combox->Connect(spoof_dest))
	{
#else
   bool isServer =false;
	if (__paroc_combox->Create(0, isServer) && __paroc_combox->Connect(dest))
	{
#endif
		int status;
		POPString info;
		POPString peerplatform;
		BindStatus(status, peerplatform, info);
		switch (status)
		{
		case BIND_OK:
			NegotiateEncoding(info,peerplatform);
			break;

		case BIND_FORWARD_SESSION:
		case BIND_FORWARD_PERMANENT:
		{
			paroc_accesspoint old(accesspoint);
			paroc_accesspoint newap;
			newap.SetAccessString(info);
			DEBUG("Forward current session to %s", (const char *)info);
			Bind(newap);
			if (status==BIND_FORWARD_SESSION) accesspoint=old;
			break;
		}
		default:
			DEBUG("Unknown binding status");
			Release();
			paroc_exception::paroc_throw(POPC_BIND_BAD_REPLY, ClassName());
		}
	}
	else
	{
		int code=errno;
		//      DEBUG("Fail to connect from [%s] to [%s]",(const char *)paroc_system::GetHost(),dest);
		//      DEBUG("Create socket fails. Reason: %s.",strerror(code));
		Release();
		paroc_exception::paroc_throw(code, ClassName());
	}

	__paroc_combox->SetTimeout(-1);

}

bool paroc_interface::TryLocal(paroc_accesspoint &objaccess)
{
	POPString hostname;
	POPString rarch;
	POPString codefile;
	POPString batch;

	POPString objname(ClassName());
	//bool odEmpty=od.IsEmpty();
	bool localFlag=od.IsLocal();
	od.getURL(hostname);

	od.getURL(hostname);
	od.getArch(rarch);
	od.getBatch(batch);
	//if (hostname!=NULL || batch!=NULL)
	if (localFlag || hostname!=NULL || batch!=NULL)
	{
		if (hostname==NULL) hostname=paroc_system::GetHost();

		od.getExecutable(codefile);
		//Hostname existed
		if (codefile==NULL)
		{
			//Lookup local code manager for the binary source....
			assert(!paroc_system::appservice.IsEmpty());
			CodeMgr mgr(paroc_system::appservice);
			if (rarch==NULL)rarch=paroc_system::platform;
			if (!mgr.QueryCode(objname,rarch,codefile))
			{
				paroc_exception::paroc_throw(OBJECT_NO_RESOURCE, ClassName());
				//else return false;
			}
		}

		//Local exec using sh or rsh
		char *hoststr=hostname.GetString();

		int status=LocalExec(hoststr, codefile, ClassName(), paroc_system::jobservice, paroc_system::appservice,&objaccess,1,od);
		//if (status!=0 && !odEmpty) paroc_exception::paroc_throw(status, ClassName());
		
		if (status!=0) {
			paroc_exception::paroc_throw(status, ClassName());
		}
		return (status==0);
	}
	return false;
}


void paroc_interface::Release()
{
	if (__paroc_combox!=NULL)
	{
		__paroc_combox->Destroy();
		__paroc_combox=NULL;
	}
	if (__paroc_buf!=NULL)
	{
		__paroc_buf->Destroy();
		__paroc_buf=NULL;
	}

   if(_ssh_tunneling){
      int ret=0;
      ret = KillSSHTunnel(_ssh_user.c_str(), _ssh_dest_ip.c_str(), _ssh_dest_port, _ssh_local_port);
   }      
}


bool paroc_interface::isBinded(){
	if (__paroc_combox==NULL || __paroc_buf==NULL) 
		return false;
	return true;
}




//ParocCall...




void paroc_interface::BindStatus(int &code, POPString &platform, POPString &info)
{
	if (__paroc_combox==NULL || __paroc_buf==NULL) return;
	paroc_message_header h(0,0, INVOKE_SYNC ,"BindStatus");
	paroc_mutex_locker lock(_paroc_imutex);
	__paroc_buf->Reset();
	__paroc_buf->SetHeader(h);
	paroc_Dispatch(__paroc_buf);
	paroc_Response(__paroc_buf);

	__paroc_buf->Push("code","int",1);
	__paroc_buf->UnPack(&code,1);
	__paroc_buf->Pop();

	__paroc_buf->Push("platform","POPString",1);
	__paroc_buf->UnPack(&platform,1);
	__paroc_buf->Pop();

	__paroc_buf->Push("info","POPString",1);
	__paroc_buf->UnPack(&info,1);
	__paroc_buf->Pop();

}


int paroc_interface::AddRef()
{
	if (__paroc_combox==NULL || __paroc_buf==NULL) return -1;
	paroc_message_header h(0,1, INVOKE_SYNC,"AddRef");
	paroc_mutex_locker lock(_paroc_imutex);
	__paroc_buf->Reset();
	__paroc_buf->SetHeader(h);

	paroc_Dispatch(__paroc_buf);
	paroc_Response(__paroc_buf);
	int ret;
	__paroc_buf->Push("refcount","int",1);
	__paroc_buf->UnPack(&ret,1);
	__paroc_buf->Pop();
	return ret;
}

int paroc_interface::DecRef()
{
	if (__paroc_combox==NULL || __paroc_buf==NULL) return -1;
	paroc_message_header h(0,2, INVOKE_SYNC,"DecRef");
	paroc_mutex_locker lock(_paroc_imutex);
	__paroc_buf->Reset();
	__paroc_buf->SetHeader(h);

	paroc_Dispatch(__paroc_buf);
	paroc_Response(__paroc_buf);
	int ret;
	__paroc_buf->Push("refcount","int",1);
	__paroc_buf->UnPack(&ret,1);
	__paroc_buf->Pop();
	return ret;
}


bool paroc_interface::Encoding(POPString encoding)
{
	if (__paroc_combox==NULL || __paroc_buf==NULL) return false;
	paroc_buffer_factory *fact=paroc_buffer_factory_finder::GetInstance()->FindFactory(encoding);
	if (fact==NULL)
	{
		DEBUG("No encoding factory for %s", (const char *)encoding);
		return false;
	}

	paroc_message_header h(0,3, INVOKE_SYNC ,"Encoding");
	paroc_mutex_locker lock(_paroc_imutex);
	__paroc_buf->Reset();
	__paroc_buf->SetHeader(h);

	__paroc_buf->Push("encoding","POPString",1);
	__paroc_buf->Pack(&encoding,1);
	__paroc_buf->Pop();

	paroc_Dispatch(__paroc_buf);
	paroc_Response(__paroc_buf);
	bool ret;
	__paroc_buf->Push("result","bool",1);
	__paroc_buf->UnPack(&ret,1);
	__paroc_buf->Pop();

	if (ret)
	{
		__paroc_buf->Destroy();
		__paroc_buf=fact->CreateBuffer();
		__paroc_combox->SetBufferFactory(fact);
	}
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
	POPString pref;
	od.getEncoding(pref);
	paroc_list<char *> enc_pref, enc_avail;
	Tokenize(pref,enc_pref);
	Tokenize(enclist,enc_avail);

	POPString cur_enc;
	__paroc_combox->GetBufferFactory()->GetBufferName(cur_enc);

	if (enc_pref.IsEmpty())
	{
		POSITION pos=enc_avail.GetHeadPosition();
		while (pos!=NULL)
		{
			char *enc=enc_avail.GetNext(pos);
			if (paroc_utils::MatchWildcard(enc,"raw*") && !paroc_utils::isEqual(peerplatform,paroc_system::platform)) continue;
			if (paroc_utils::isncaseEqual(enc,cur_enc) || Encoding(enc)) return;
		}
	}
	else
	{
		POSITION prefpos=enc_pref.GetHeadPosition();
		while (prefpos)
		{
			char *test=enc_pref.GetNext(prefpos);
			POSITION pos=enc_avail.GetHeadPosition();
			while (pos!=NULL)
			{
				char *enc=enc_avail.GetNext(pos);
				if (paroc_utils::MatchWildcard(enc,test))
				{
					if (paroc_utils::isncaseEqual(enc,"raw") && !paroc_utils::isEqual(peerplatform,paroc_system::platform)) continue;
					if (paroc_utils::isncaseEqual(enc,cur_enc) || Encoding(enc)) return;
				}
			}
		}
	}

	paroc_exception::paroc_throw(POPC_NO_ENCODING, ClassName());
}

int paroc_interface::LocalExec(const char *hostname, const char *codefile, const char *classname, const paroc_accesspoint &jobserv, const paroc_accesspoint &appserv, paroc_accesspoint *objaccess, int howmany, const paroc_od& od)
{

   DEBUG("JOBSERVICE-INTERFACE %s", jobserv.GetAccessString());
   
	if (codefile==NULL) return ENOENT;
	signal(SIGCHLD, SIG_IGN);

	while (isspace(*codefile)) codefile++;

	char tmpstr[10240];
	char *argv[1024];
	char *tmp;

	bool isManual=od.getIsManual();
#ifdef OD_DISCONNECT
	bool checkConnection=od.getCheckConnection();
#endif
	POPString ruser;
	POPString rcore;
	const char *rport=NULL;
	POPString batch;
	POPString cwd;

	if (hostname!=NULL&&(tmp=(char*)strchr(hostname,':'))!=NULL) {
		*tmp=0;
		rport=tmp+1;
	}
	od.getUser(ruser);
	od.getCore(rcore);
	od.getBatch(batch);
	od.getDirectory(cwd);

	int n=0;
	POPString myhost=paroc_system::GetHost();
	bool islocal=(isManual||hostname==NULL || *hostname==0 || paroc_utils::SameContact(myhost,hostname) || paroc_utils::isEqual(hostname,"localhost") || paroc_utils::isEqual(hostname,"127.0.0.1"));
	if (batch==NULL)
	{
		if (!islocal)
		{
			char *tmp=getenv("POPC_RSH");
			argv[n++]=strdup((tmp==NULL)? "/usr/bin/ssh" : tmp);
			//      argv[n++]=strdup("-n");
			// Add user name to host for ssh
			if (ruser!=NULL && *ruser!=0) {
				char tmpstr[100];
				sprintf(tmpstr,"%s@%s",(const char*)ruser,(const char*)hostname);
				argv[n++]=strdup(tmpstr);
			} else {
				argv[n++]=strdup(hostname);
			}
		}
	}
	else {
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
	}
	//  if (strncmp(codefile, "http://",7)==0 || strncmp(codefile,"ftp://",6)==0)
	//    {
	tmp=getenv("POPC_LOCATION");
	if (tmp!=NULL) sprintf(tmpstr,"%s/services/popcobjrun",tmp);
	else strcpy(tmpstr,"popcobjrun");
	argv[n++]=strdup(tmpstr);
	//    }
	//   else  if ((tmp=getenv("POPC_JOB_EXEC"))!=NULL)
	//    {
	//       argv[n++]=strdup(tmp);
	//    }

	strcpy(tmpstr,codefile);
	char *tok=strtok_r(tmpstr," \t\n",&tmp);
	while (tok!=NULL)
	{
		argv[n++]=strdup(tok);
		tok=strtok_r(NULL," \t\n",&tmp);
	}

	paroc_combox_socket tmpsock;
   bool isServer=true;
	if (!tmpsock.Create(0,isServer)) paroc_exception::paroc_throw_errno();
	POPString cburl;
	tmpsock.GetUrl(cburl);

	sprintf(tmpstr,"-callback=%s", (const char*)cburl);
	argv[n++]=strdup(tmpstr);

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

	if (!jobserv.IsEmpty())
	{
		sprintf(tmpstr,"-jobservice=%s",jobserv.GetAccessString());
		argv[n++]=strdup(tmpstr);
	}
	// Select core
	if (rcore!=NULL&&rcore!=0) {
		sprintf(tmpstr,"-core=%s",(const char*)rcore);
		argv[n++]=strdup(tmpstr);
	}

	if (rport!=NULL && *rport!=0)
	{
		sprintf(tmpstr,"-socket_port=%s",rport);
		argv[n++]=strdup(tmpstr);
	}
#ifdef OD_DISCONNECT
	if (checkConnection) {
		sprintf(tmpstr,"-checkConnection");
		argv[n++]=strdup(tmpstr);
	}
#endif

	if (paroc_od::defaultLocalJob)
	{
		argv[n++]=strdup("-runlocal");
	}

	// Add the working directory as argument
	if (cwd!=NULL && *cwd!=0) {
		sprintf(tmpstr,"-cwd=%s",(const char*)cwd);
		argv[n++]=strdup(tmpstr);
	}

	argv[n]=NULL;

	int ret=0, err=0;
	if (isManual)
	{
		printf("\nTo launch this object, run this command on the target machine :\n");
		for (int i=0;i<n;i++) printf("%s ", argv[i]);
		printf("\n");
	}
	else
	{
#ifndef NDEBUG
		if (getenv("POPC_DEBUG")) {
			DEBUG("Launching a new object with command : ");
			fprintf(stderr,"--->");
			for (int i=0;i<n;i++) fprintf(stderr,"%s ", argv[i]);
			fprintf(stderr,"\n");
		}
#endif
		ret=RunCmd(argv,NULL);
		err=errno;
	}
	for (int i=0;i<n;i++) if (argv[i]!=NULL) free(argv[i]);

	if (ret==-1)
	{
		DEBUG("Can not start the object code...");
		paroc_exception::paroc_throw(err, classname);
	}

	//Now get the return paroc_accesspoint....
	tmpsock.SetTimeout(ALLOC_TIMEOUT*1000);

	for (int i=0;i<howmany;i++, objaccess++)
	{

		paroc_buffer_xdr buf1;
		paroc_buffer *buf=&buf1;

		if (!buf->Recv(tmpsock))
		{
			err=errno;
			return err;
		}
		buf->Push("status","int",1);
		buf->UnPack(&n,1);
		buf->Pop();

		if (n!=0)
		{
			return n;
		}
		buf->Push("address","paroc_accesspoint",1);
		objaccess->Serialize(*buf,false);
		buf->Pop();
	}

	return 0;
}


void paroc_interface::Tokenize(POPString &s, paroc_list<char *> &tokens)
{
	char *t=s.GetString();
	if (t==NULL) return;
	char sep[]=" \n\t";
	char *ptrptr;
	char *tok=strtok_r(t,sep,&ptrptr);

	while (tok!=NULL)
	{
		tokens.AddTail(tok);
		tok=strtok_r(NULL,sep,&ptrptr);
	}
}

void paroc_interface::ApplyCommPattern(const char *pattern, paroc_list<char *> &accesslist)
{
	if (pattern==NULL) return;
	POPString p(pattern);

	paroc_list<char *> patternlist;
	Tokenize(p,patternlist);

	POSITION ptpos=patternlist.GetHeadPosition();
	POSITION headpos=accesslist.GetHeadPosition();
	while (ptpos!=NULL)
	{
		char *ptstr=patternlist.GetNext(ptpos);
		if (ptstr==NULL) continue;
		POSITION pos=headpos;
		while (pos!=NULL)
		{
			POSITION old=pos;
			char *t=accesslist.GetNext(pos);
			if (paroc_utils::MatchWildcard(t,ptstr))
			{
				if (headpos!=old)
				{
					accesslist.InsertBefore(headpos, t);
					accesslist.RemoveAt(old);
				}
				else
				{
					accesslist.GetNext(headpos);
					if (headpos==NULL) return;
				}
			}

		}
	}
}

void paroc_interface::paroc_Dispatch(paroc_buffer *buf)
{
	if (!buf->Send(*__paroc_combox)) paroc_exception::paroc_throw_errno();
}

void paroc_interface::paroc_Response(paroc_buffer *buf)
{
	if (!buf->Recv(*__paroc_combox)) paroc_exception::paroc_throw_errno();
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

