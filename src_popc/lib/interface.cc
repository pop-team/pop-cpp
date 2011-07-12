#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "paroc_interface.h"
#include "paroc_buffer_factory_finder.h"
#include "paroc_broker.h"
#include "jobmgr.ph"
#include "codemgr.ph"
#include "paroc_combox_factory.h"
#include "paroc_combox_socket.h"

#ifndef PAROC_CONNECT_TIMEOUT
#define PAROC_CONNECT_TIMEOUT 10000
#endif

int RunCmd(char **argv, char *env[])
{

  char *file=NULL;

  char *tmp;
  char sep[]=" \n\r\t";
  paroc_string str;
  int n;

  if (argv==NULL || argv[0]==NULL) return ENOENT;
  file=argv[0];
//  if (access(file,X_OK)!=0)
//    {
//      return -1;
//    }

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
      setpgid(0,0);
      //Child process
      execvp(file,argv);
      DEBUG("Execution of [%s] fail\n",file);
      _exit(-1);
    }
  return 0;
}



paroc_accesspoint paroc_interface::_paroc_nobind;

//binding time out in miliseconds 
int paroc_interface::paroc_bind_timeout=10000; 

//paroc_interface base class
 
paroc_interface::paroc_interface()
{
  __paroc_combox=NULL;
 __paroc_buf=NULL;
}

paroc_interface::paroc_interface(const paroc_accesspoint &p)
{
  __paroc_combox=NULL;
  __paroc_buf=NULL;

  Bind(p);
}

paroc_interface::paroc_interface(const paroc_interface &inf)
{
  __paroc_combox=NULL;
  __paroc_buf=NULL;
  Bind(inf.GetAccessPoint());
}

paroc_interface::~paroc_interface()
{
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

void paroc_interface::Serialize(paroc_buffer &buf, bool pack)
{
  buf.Push("od","paroc_od",1);
  od.Serialize(buf,pack);
  buf.Pop();

  buf.Push("accesspoint","paroc_accesspoint",1);
  accesspoint.Serialize(buf,pack);
  buf.Pop();
  
  paroc_buffer *old=NULL;

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

  paroc_string hostname;
  paroc_string codefile;
  paroc_accesspoint jobcontact, objaccess;

  char *tmpstr;

  codefile=NULL;
  int ntries=PAROC_ALLOC_RETRY;
  while (1)
  {
    ntries--;
    int reqid=LocateResource(hostname,codefile,jobcontact);
    if (reqid<0)
      {
	DEBUG("Allocation of parallel object fail\n");
	paroc_exception::paroc_throw(ALLOCATION_EXCEPTION, ClassName());
      }
    
    if (hostname!=NULL)
      {
	//Local exec using sh or rsh 
 	char *hoststr=hostname.GetString();
	char *rport=NULL;
	
	if ((tmpstr=strchr(hoststr,':'))!=NULL)
	  {
	    *tmpstr=0;  
	    rport=tmpstr+1;
	  }
	int status=LocalExec(hoststr, codefile, ClassName(),rport, paroc_system::jobservice, paroc_system::appservice,&objaccess,1);
	if (status!=0) paroc_exception::paroc_throw(status, ClassName());
	break;
      } 
    else
      {
	//Exec using JobMgr interface...
	paroc_string objname(ClassName());
	JobMgr t(jobcontact);
	int status=t.ExecObj(objname,1, &reqid, paroc_system::appservice,&objaccess);
	if (status==0 && !objaccess.IsEmpty()) break;
	t.CancelReservation(&reqid,1);
	
	if (ntries<=0) paroc_exception::paroc_throw(status, ClassName()); 
	else 
	  {
	    DEBUG("Execution of object %s on %s fails. Retry on other resources",ClassName(),jobcontact.GetAccessString());
	  }
      }
  }
  Bind(objaccess);
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
  paroc_string prots=dest.GetAccessString();
  paroc_string od_prots;
  od.getProtocol(od_prots);

  paroc_list<char *> accesslist, pref;

  Tokenize(prots,accesslist);
  ApplyCommPattern(getenv("PAROC_COMM_PATTERN"),accesslist);

  Tokenize(od_prots,pref);

  if (pref.IsEmpty())
    {
      //No preferred protocol in OD specified, try the first protocol in dest
      POSITION pos=accesslist.GetHeadPosition();
      while (pos!=NULL)
	{
	  char *addr=accesslist.GetNext(pos);
	  try {
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

	  POSITION pos=accesslist.GetHeadPosition();
	  while (pos!=NULL)
	    {
	      char *addr=accesslist.GetNext(pos);
	      char pattern[1024];
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
  Release();
  if (dest==NULL || *dest==0) return;

  char protsep[]="://";
  char prot[256];
  char *tmp=strstr(dest,protsep);
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

  if (fact==NULL) paroc_exception::paroc_throw(PAROC_NO_PROTOCOL, ClassName());

  __paroc_combox=fact->Create(prot);
  __paroc_buf=__paroc_combox->GetBufferFactory()->CreateBuffer();

  __paroc_combox->SetTimeout(paroc_bind_timeout);

  if (__paroc_combox->Create(0, false) && __paroc_combox->Connect(dest))     
    {
      
      int status;
      paroc_string info;
      paroc_string peerplatform;
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
	  paroc_exception::paroc_throw(PAROC_BIND_BAD_REPLY, ClassName());
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

int paroc_interface::LocateResource(paroc_string &hostname, paroc_string &codefile, paroc_accesspoint &jobcontact)
{
  char targetcode[256];
  char str[256];

  int req;


  paroc_string objname(ClassName());
  bool odEmpty=od.IsEmpty();

  if (odEmpty) hostname=paroc_system::GetHost();
  else od.getURL(hostname);

  codefile=NULL;

  if (hostname==NULL)
    {
      //Global Resource management system --> Find a resource.
      paroc_accesspoint p;

      char *t;
      paroc_string joburl;
      od.getJobURL(joburl);

      if  (joburl!=NULL)
	{
	  p.SetAccessString(joburl);
	} else p=paroc_system::jobservice;
      
      if (p.IsEmpty())
	{
	  sprintf(str,"%s:%d",(const char *)paroc_system::GetHost(),DEFAULTPORT);
	  p.SetAccessString(str);
	}
      JobMgr resources(p);
      int req;
      if (resources.AllocResource(paroc_system::appservice,objname,od, 1, &jobcontact,&req))
	{
	  return req;
	}
    } 
  else
    {
      od.getExecutable(codefile);
      //Hostname existed
      if (codefile!=NULL) return 0;
      //Lookup local code manager for the binary source....
      CodeMgr mgr(paroc_system::appservice);
      if (mgr.QueryCode(objname,paroc_system::platform,codefile))
	{
	  return 0;
	}
    }
  paroc_exception::paroc_throw(OBJECT_NO_RESOURCE, ClassName());
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
}


//ParocCall...

void paroc_interface::BindStatus(int &code, paroc_string &platform, paroc_string &info)
{
  if (__paroc_combox==NULL || __paroc_buf==NULL) return;
  paroc_message_header h(0,0, INVOKE_SYNC ,"BindStatus");
  paroc_mutex_locker lock(_paroc_imutex);
  __paroc_buf->Reset();
 __paroc_buf->SetHeader(h);
  if (!__paroc_buf->Send(*__paroc_combox)) paroc_exception::paroc_throw(errno);
  if (!__paroc_buf->Recv(*__paroc_combox)) paroc_exception::paroc_throw(errno);

  __paroc_buf->Push("code","int",1);
  __paroc_buf->UnPack(&code,1);
  __paroc_buf->Pop();

  __paroc_buf->Push("platform","paroc_string",1);
  __paroc_buf->UnPack(&platform,1);
  __paroc_buf->Pop();

  __paroc_buf->Push("info","paroc_string",1);
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

  if (!__paroc_buf->Send(*__paroc_combox)) paroc_exception::paroc_throw(errno);
  if (!__paroc_buf->Recv(*__paroc_combox)) paroc_exception::paroc_throw(errno);
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

  if (!__paroc_buf->Send(*__paroc_combox)) paroc_exception::paroc_throw(errno);
  if (!__paroc_buf->Recv(*__paroc_combox)) paroc_exception::paroc_throw(errno);
  int ret;
  __paroc_buf->Push("refcount","int",1);
  __paroc_buf->UnPack(&ret,1);
  __paroc_buf->Pop();
  return ret;
}


bool paroc_interface::Encoding(paroc_string encoding)
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

  __paroc_buf->Push("encoding","paroc_string",1);
  __paroc_buf->Pack(&encoding,1);
  __paroc_buf->Pop();

  if (!__paroc_buf->Send(*__paroc_combox)) paroc_exception::paroc_throw(errno);
  if (!__paroc_buf->Recv(*__paroc_combox)) paroc_exception::paroc_throw(errno);
  bool ret;
  __paroc_buf->Push("result","bool",1);
  __paroc_buf->UnPack(&ret,1);
  __paroc_buf->Pop();

  if (ret)
    {
      __paroc_buf->Destroy();
      __paroc_buf=fact->CreateBuffer();
      __paroc_combox->SetBufferFactory(fact);
      //      DEBUG("Encoding for %s@%s: %s",ClassName(),accesspoint.GetAccessString(),(const char *)encoding);
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

  if (!__paroc_buf->Send(*__paroc_combox)) paroc_exception::paroc_throw(errno);
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
  if (!__paroc_buf->Send(*__paroc_combox)) paroc_exception::paroc_throw(errno);
  if (!__paroc_buf->Recv(*__paroc_combox)) paroc_exception::paroc_throw(errno);
  bool ret;
  __paroc_buf->Push("result","bool",1);
 __paroc_buf->UnPack(&ret,1);
 __paroc_buf->Pop();
  return ret;
}



void paroc_interface::NegotiateEncoding(paroc_string &enclist, paroc_string &peerplatform)
{
  paroc_string pref;
  od.getEncoding(pref);
  paroc_list<char *> enc_pref, enc_avail;
  Tokenize(pref,enc_pref);
  Tokenize(enclist,enc_avail);
  
  paroc_string cur_enc;
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
  
  paroc_exception::paroc_throw(PAROC_NO_ENCODING, ClassName());
}

int paroc_interface::LocalExec(const char *hostname, const char *codefile, const char *classname, const char *rport, const paroc_accesspoint &jobserv, const paroc_accesspoint &appserv, paroc_accesspoint *objaccess, int howmany)
{

  while (isspace(*codefile)) codefile++;

  char tmpstr[10240];
  char *argv[1024];
  char *tmp;

  int n=0;
  paroc_string myhost=paroc_system::GetHost();
  bool islocal=(hostname==NULL || *hostname==0 || paroc_utils::SameContact(myhost,hostname) || paroc_utils::isEqual(hostname,"localhost") || paroc_utils::isEqual(hostname,"127.0.0.1"));
  if (!islocal)
    {
      char *tmp=getenv("PAROC_RSH");
      argv[n++]=strdup((tmp==NULL)? "/usr/bin/rsh" : tmp);
      //      argv[n++]=strdup("-n");
      argv[n++]=strdup(hostname);
    }

  //  if (strncmp(codefile, "http://",7)==0 || strncmp(codefile,"ftp://",6)==0)
  //    {
  tmp=getenv("PAROC_LOCATION");
  if (tmp!=NULL) sprintf(tmpstr,"%s/services/webrun",tmp);
  else strcpy(tmpstr,"webrun");
  argv[n++]=strdup(tmpstr);
  //    }
  //   else  if ((tmp=getenv("PAROC_JOB_EXEC"))!=NULL)
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
  if (!tmpsock.Create(0,true)) paroc_exception::paroc_throw_errno();
  paroc_string cburl;
  tmpsock.GetUrl(cburl);

  sprintf(tmpstr,"-callback=%s", (const char*)cburl);
  argv[n++]=strdup(tmpstr);

  argv[n++]=strdup(classname);

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

  if (rport!=NULL && *rport!=0)
    {
      sprintf(tmpstr,"-socket_port=%s",rport);
      argv[n++]=strdup(tmpstr);
    }
  argv[n]=NULL;

  int ret=RunCmd(argv,NULL);
  int err=errno;
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


void paroc_interface::Tokenize(paroc_string &s, paroc_list<char *> &tokens)
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
  paroc_string p(pattern);

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

