#include <string.h>

#include "jobmgr_globus.ph"
#include "appservice_globus.ph"


//This is the callback function used by globus to notify the changes of job status...
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

void globus_job_callback_func(void *user_callback_arg, char *job_contact, int state, int errorcode)
{
  GlobusMonitor *Monitor=(GlobusMonitor *)user_callback_arg;
  IMPLEMENT_TYPE(GlobusAppCoreService) *app=(IMPLEMENT_TYPE(GlobusAppCoreService) *)Monitor->appservice;
  if (app==NULL) return;

   switch(state)
    {
    case GLOBUS_GRAM_PROTOCOL_JOB_STATE_PENDING:
       break; /* Reports state change to the user */

    case GLOBUS_GRAM_PROTOCOL_JOB_STATE_ACTIVE:
       break; /* Reports state change to the user */
      
    case GLOBUS_GRAM_PROTOCOL_JOB_STATE_FAILED:
      app->EndJob(job_contact,state);
      break; /* Reports state change to the user */
      
    case GLOBUS_GRAM_PROTOCOL_JOB_STATE_DONE:
      app->EndJob(job_contact,state);
      break; /* Reports state change to the user */
    }
}

void *GlobusJobCallbackThread(void *param)
{
  GlobusMonitor *Monitor=(GlobusMonitor *)param;
 
  if (globus_gram_client_callback_allow(globus_job_callback_func,param,&Monitor->callback_contact)!=GLOBUS_SUCCESS)
    {
      DEBUG("Can not register Globus job callback");
      Monitor->callback_contact=NULL;
    }
  //  DEBUGIF(Monitor->callback_contact!=NULL,"Globus job callback contact: %s",Monitor->callback_contact);
  
  globus_mutex_lock(&Monitor->mutex);  
  while (!Monitor->done)
    {
      /* Within the cond_wait function, it unlocks the monitor,
       * allowing the callback_func to take the lock. When it gets a
       * cond_signal, it re-locks the monitor, and returns to this
       * program.  But DO NOT unlock the monitor yourself- use the
       * globus_gram_cond_wait function, as it insures safe
       * unlocking.
       */
      globus_cond_wait(&Monitor->cond, &Monitor->mutex);
      DEBUG("CALLBACK THREAD: WAIT COND RETURN");
    } /* endwhile */
  
  globus_mutex_unlock(&Monitor->mutex);

  DEBUG("CALLBACK THREAD TERMINATED");

  return 0;  
}

GlobusAppCoreService::GlobusAppCoreService(const paroc_string &challenge, bool daemon, const paroc_string &codelocation): AppCoreService(challenge, daemon, codelocation), paroc_service_base(challenge)
{
  mysubject=NULL;
  nextJobID=0;

  int ret1;

  ret1=globus_module_activate(GLOBUS_GRAM_CLIENT_MODULE);
  if (ret1!=GLOBUS_SUCCESS)
    {
      DEBUG("globus_module_activate(GLOBUS_GRAM_CLIENT_MODULE) fail");
      paroc_exception::paroc_throw(PAROC_APPSERVICE_FAIL);
    }

  ret1=globus_module_activate(GLOBUS_GSI_CREDENTIAL_MODULE);
  if (ret1!=GLOBUS_SUCCESS)
    {
      DEBUG("globus_module_activate(GLOBUS_GSI_CREDENTIAL_MODULE) fail");
      paroc_exception::paroc_throw(PAROC_APPSERVICE_FAIL);
    }
      
  ret1=globus_module_activate(GLOBUS_COMMON_MODULE);
  if (ret1!=GLOBUS_SUCCESS)
    {
      DEBUG("globus_module_activate(GLOBUS_COMMON_MODULE) fail");
      paroc_exception::paroc_throw(PAROC_APPSERVICE_FAIL);
    }
 
  globus_gsi_cred_handle_t handle;
  globus_gsi_cred_handle_attrs_t attr;
  globus_result_t ret;

  ret=globus_gsi_cred_handle_attrs_init(&attr);
  if (ret!=GLOBUS_SUCCESS)
    {
      DEBUG("globus_gsi_cred_handle_attrs_init(&attr) fail");
      return;
    }

  ret=globus_gsi_cred_handle_init(&handle,attr);
  
  if (ret!=GLOBUS_SUCCESS)
    {
      DEBUG("globus_gsi_cred_handle_init(&handle,handle_attrs) fail");
      return;
    }
  char certfile[512];
  char *home=getenv("HOME");
  if (home==NULL)
    {
      DEBUG("Fail to find certificate");
      return;
    }
  sprintf(certfile,"%s/.globus/usercert.pem",home);

  ret=globus_gsi_cred_read_cert(handle,certfile);
  if (ret!=GLOBUS_SUCCESS)
    {
      DEBUG("globus_gsi_cred_read_cert(handler,proxyfile) fail");
      return;
    }

  ret=globus_gsi_cred_get_subject_name(handle,&mysubject);
  if (ret!=GLOBUS_SUCCESS)
    {
      DEBUG("globus_gsi_cred_get_subject_name(handle,&subject) fail");
      return;
    }
  DEBUG("SUBJECT=%s",mysubject);



  Monitor.done=false;
  Monitor.appservice=this;
  Monitor.callback_contact=NULL;
  globus_mutex_init(&Monitor.mutex,NULL);
  globus_cond_init(&Monitor.cond,NULL);

  pthread_create(&tid,NULL,GlobusJobCallbackThread, &Monitor);
  
}

GlobusAppCoreService::~GlobusAppCoreService() 
{
  //  DEBUG("TERMINATING GLOBUSAPPCORESERVICE");
  globus_mutex_lock(&Monitor.mutex);
  Monitor.done = true;
  globus_cond_broadcast(&Monitor.cond);
  globus_mutex_unlock(&Monitor.mutex);
  
  //  DEBUG("DEACTIVATE COMMON");
  globus_module_deactivate(GLOBUS_COMMON_MODULE);

  //  DEBUG("DEACTIVATE GSI_CREDENTIAL");
  globus_module_deactivate(GLOBUS_GSI_CREDENTIAL_MODULE);

  pthread_kill(tid,SIGKILL);

  //  DEBUG("Deactivate GRAM_CLIENT");
  globus_module_deactivate(GLOBUS_GRAM_CLIENT_MODULE);
  
  globus_mutex_destroy(&Monitor.mutex);
  globus_cond_destroy(&Monitor.cond);
  //  DEBUG("TERMINATED");  
}

bool GlobusAppCoreService::GetUserSubjectName(paroc_string &subject)
{
  if (mysubject==NULL) 
    {
      subject=NULL;
      return false;
    }
  subject=mysubject;
  return true;

}

int  GlobusAppCoreService::SubmitJob(const paroc_string &gramcontact, const paroc_string &objname, int howmany, const paroc_string &platform, const paroc_accesspoint &jobmgr, 
				     const paroc_accesspoint &objcallback, const paroc_string &env, int &jobID)
{
  char *tmpjobcontact=NULL;
  char rsl[10240];
  if (!GenerateJobDescription(objname, howmany, platform,jobmgr,objcallback,env,rsl,10240))
    {
      DEBUG("Fail to generate RSL for the object %s", (const char *)objname);
      return ENOENT;
      }
  DEBUG("RSL=%s to GRAM %s",rsl,(const char *)gramcontact);
  int ret=globus_gram_client_job_request(gramcontact,rsl,GLOBUS_GRAM_PROTOCOL_JOB_STATE_ALL,Monitor.callback_contact,&tmpjobcontact);
  DEBUGIF(ret!=GLOBUS_SUCCESS,"Submit job FAIL: %s",globus_gram_client_error_string(ret));

  if (ret==GLOBUS_SUCCESS)
    {
      //      DEBUG("globus_gram_client_job_request OK\n");
      //      DEBUGIF(tmpjobcontact!=NULL,"Cmd=%s, Jobcontact=[%s]\n",cmd,tmpjobcontact);
      mutex 
	{
	  int n=globusjobs.GetSize();
	  globusjobs.SetSize(n+1);
	  GlobusJob &myjob=globusjobs[n];
	  jobID=myjob.Id=nextJobID;
	  myjob.jobcontact=tmpjobcontact;
	  myjob.status=0;
	  
	  nextJobID++;
	}
      return 0;

    }
  else
    {
      
      return PAROC_EXEC_FAIL;
    }
}

bool GlobusAppCoreService::EndJob(char *jobcontact, int state)
{
  mutex 
    {
      int index=Find(jobcontact);
      if (index<0 || index>=globusjobs.GetSize()) return false;
      GlobusJob &myjob=globusjobs[index];
      EndJob(myjob,state);
      if (myjob.jobcontact!=NULL) globus_gram_client_job_contact_free(myjob.jobcontact);
      globusjobs.RemoveAt(index);
    }
  return true;
  
}


bool GlobusAppCoreService::EndJob(int id, int state)
{
  mutex 
    {
      int index=Find(id);
      if (index<0 || index>=globusjobs.GetSize()) return false;
      GlobusJob &myjob=globusjobs[index];
      EndJob(myjob,state);
      if (myjob.jobcontact!=NULL) globus_gram_client_job_contact_free(myjob.jobcontact);
      globusjobs.RemoveAt(index);
    }
  return true;
  
}

void GlobusAppCoreService::EndJob(GlobusJob &myjob, int state)
{
  if (state!=GLOBUS_GRAM_PROTOCOL_JOB_STATE_FAILED && state!= GLOBUS_GRAM_PROTOCOL_JOB_STATE_DONE)
    {
      //Need to cancel the job...
      globus_gram_client_job_cancel(myjob.jobcontact);
    }
}

int GlobusAppCoreService::Find(int id)
{
  int n=globusjobs.GetSize();
  GlobusJob *tmp=globusjobs;
  for (int i=0;i<n;i++, tmp++) if (tmp->Id==id) return i;
  return -1;
}

int GlobusAppCoreService::Find(char *jobcontact)
{
  int n=globusjobs.GetSize();
  GlobusJob *tmp=globusjobs;
  for (int i=0;i<n;i++, tmp++) if (paroc_utils::isEqual(tmp->jobcontact,jobcontact)) return i;
  return -1;
}



bool GlobusAppCoreService::GenerateJobDescription(const paroc_string &objname, int howmany,  const paroc_string &platform, const paroc_accesspoint &jobmgr, 
				     const paroc_accesspoint &objcallback, const paroc_string &env, char *rsl, int n)
{
  
  paroc_string codefile;
  char *ptr;
  if (!QueryCode(objname,platform, codefile))
    {
      DEBUG("Can not find the object code for %s, platform %s",(const char *)objname,(const char *)platform);
      return false;
    }
  
  char sep[]=" \n\t\r";

  char tmpcodefile[10240];
  strcpy(tmpcodefile,codefile);
  char *tok=strtok_r(tmpcodefile,sep,&ptr);
  if (tok==NULL) return false;

  char args[10240];
  char prog[1024];
  strcpy(prog,tok);

  sprintf(args,"%s ",(const char *)objname);

  tok=strtok_r(NULL,sep,&ptr);
  while (tok!=NULL)
    {
      strcat(args,"\"");
      strcat(args,tok);
      strcat(args,"\" ");
      tok=strtok_r(NULL,sep,&ptr);
    }

  tok=args+strlen(args);
  if (!jobmgr.IsEmpty())
    { 
      sprintf(tok,"\"-jobservice=%s\" ",jobmgr.GetAccessString());
      tok+=strlen(tok);
    }

  if (!objcallback.IsEmpty())
    { 
      sprintf(tok,"\"-callback=%s\" ",objcallback.GetAccessString());
      tok+=strlen(tok);
    }

  sprintf(tok,"\"-appservice=%s\" ",GetAccessPoint().GetAccessString());
 
  if (env!=NULL && *env!=0)
    sprintf(rsl,"&(executable=\"%s\" )(directory =/tmp )(arguments=%s)(environment=%s)(count=%d)",prog,args,(const char *)env, howmany);
  else 
    sprintf(rsl,"&(executable =\"%s\" )(directory =/tmp )(arguments=%s)(count=%d)",prog,args,howmany);

  //  DEBUG("RSL for object %s:[%s]",(const char*)objname, rsl);
  return true;
}

void GlobusAppCoreService::KillAll()
{
  printf("Kill all Globus jobs!!!!\n");
  Monitor.appservice=NULL;
  AppCoreService::KillAll();
  int n=globusjobs.GetSize();
  for (int i=0;i<n;i++)
    {
      GlobusJob &myjob=globusjobs[i];
      globus_gram_client_job_cancel(myjob.jobcontact);
    }
}
