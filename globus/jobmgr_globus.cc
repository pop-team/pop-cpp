#include "jobmgr_globus.ph"
#include "globusgram.ph"

#include "globus_gram_client.h"
#include "globus_gss_assist.h"


GlobusJobMgr::GlobusJobMgr(bool daemon, const paroc_string &conf, const paroc_string &challenge, const paroc_string &url) : JobMgr(daemon, conf,challenge, url)
{
	if (!Query("gramcontact",globus_gram))
	{
		char tmp[1024];
		sprintf(tmp,"https://%s:8443",(const char *)paroc_system::GetHost());
		globus_gram=tmp;
	}
	else
	{
		if (*globus_gram=='/')
		{
			char tmp[1024];
			sprintf(tmp,"%s::%s",(const char *)paroc_system::GetHost(),(const char *)globus_gram);
			globus_gram=tmp;
		}
	}
	DEBUG("LOCAL GLOBUS JOB CONTACT: %s",(const char *)globus_gram);
	if (!Query("grid-mapfile",gridmap)) gridmap=NULL;

	DEBUG("Globus Gram: %s",(const char*)globus_gram);
	globus_module_activate(GLOBUS_GSI_GSS_ASSIST_MODULE);
}

GlobusJobMgr::~GlobusJobMgr()
{
	DEBUG("DEACTIVATE GLOBUS MODULE GSI_ASSIST");
	globus_module_deactivate(GLOBUS_GSI_GSS_ASSIST_MODULE);
	DEBUG("GLOBUSJOBMGR..............................TERMINATED");
}

int GlobusJobMgr::ExecObj(const paroc_string  &objname, int howmany, int *reserveIDs, const paroc_accesspoint &localservice, paroc_accesspoint *objcontacts)
{
	if (howmany<=0) return EINVAL;

	paroc_string platform;
	if (!Query("platform",platform))
	{
		CancelReservation(reserveIDs, howmany);
		return  ENOENT;
	}

	paroc_string env;
	if (!Query("env",env)) env=NULL;

	mutex {
		char env_walltime[256];
		*env_walltime=0;
		for (int i=0;i<howmany;i++)
		{
			Resources *r=VerifyReservation(reserveIDs[i], true);
			if (r==NULL) return ECANCELED;
			if (r->walltime>0 && *env_walltime==0)
			{
				int hours=int(r->walltime/3600);
				int minutes=int ((r->walltime-hours*3600)/60);
				float sec=r->walltime-hours*3600-minutes*60;

				sprintf(env_walltime,"(POPC_JOB_WALLTIME %d:%d:%g)",hours,minutes,sec);
				env+=env_walltime;
			}
		}
	}


	paroc_accesspoint objglobal, callback;
	objglobal= GetAccessPoint();

	paroc_combox_socket tmpsock;
	if (!tmpsock.Create(0,true))
	{
		CancelReservation(reserveIDs,howmany);
		return errno;
	}

	paroc_string cburl;
	tmpsock.GetUrl(cburl);

	callback.SetAccessString(cburl);

	//Now  launch the job....
	int ret=0;

	try
	{
		AppCoreService appserv(localservice);
		paroc_accesspoint gramap;

		if (!appserv.QueryService("GlobusGram", gramap))
		{
			Pause(localservice, SLEEP_TIME_ON_ERROR);
			CancelReservation(reserveIDs,howmany);
			return -1;
		}

		GlobusGram globus_job(gramap);

		int job_id;
		ret=globus_job.SubmitJob(globus_gram,objname,howmany, platform, objglobal,callback,env);
		if (ret!=0)
		{
			Pause(localservice, SLEEP_TIME_ON_ERROR);
			CancelReservation(reserveIDs,howmany);
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
				CancelReservation(reserveIDs,howmany);
				Pause(localservice, SLEEP_TIME_ON_ERROR);
				return err;
			}

			int n;
			buf.Push("status","int",1);
			buf.UnPack(&n,1);
			buf.Pop();
			if (n!=0)
			{
				Pause(localservice, SLEEP_TIME_ON_ERROR);
				CancelReservation(reserveIDs, howmany);
				return n;
			}
			buf.Push("address","paroc_accesspoint",1);
			objcontacts[i].Serialize(buf , false);
			buf.Pop();

			if (!ValidateReservation(reserveIDs[i], objcontacts[i], localservice))
			{
				CancelReservation(reserveIDs,howmany);
				return ECANCELED;
			}
		}
	}
	catch (...)
	{
		CancelReservation(reserveIDs,howmany);
		return ECANCELED;
	}
	return 0;
}

bool GlobusJobMgr:: MatchUser(paroc_accesspoint &localservice)
{
	paroc_string subject;


	AppCoreService appserv(localservice);
	paroc_accesspoint gramap;

	if (!appserv.QueryService("GlobusGram", gramap))
	{
		return false;
	}

	GlobusGram user_entity(gramap);
	if (!user_entity.GetUserSubjectName(subject)) return false;

	if (gridmap!=NULL)
	{
		int len=strlen(subject);

		FILE *f=fopen(gridmap,"rt");
		if (f==NULL)
		{
			paroc_service_log("ERROR: can not open grid-mapfile: %s",(const char *)gridmap);
			return false;
		}
		char tmp[1024];
		while (fgets(tmp,1024,f)!=NULL)
		{
			if (*tmp!='"') continue;
			if (strncmp(tmp+1,subject,len)==0 && tmp[len+1]=='"')
			{
				DEBUG("MANUAL CHECKING: MAP OK: [%s] -> %s",(const char *)subject,tmp+len+2);
				fclose(f);
				return true;
			}
		}
		fclose(f);

		DEBUG("SUBJECT NAME [%s] does not exist",(const char *)subject);
		return false;
	}


	char *localuser;
	if (globus_gss_assist_gridmap(subject.GetString(),&localuser)==GLOBUS_SUCCESS)
	{
		DEBUG("MAP OK: [%s] -> %s",(const char *)subject,localuser);
		free(localuser);
		return true;
	}
	else
	{
		DEBUG("SUBJECT NAME [%s] does not exist",(const char *)subject);
	}
	return false;
}
