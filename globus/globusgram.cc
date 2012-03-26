#include <string.h>

#include "jobmgr_globus.ph"
#include "globusgram.ph"
#include "appservice.ph"


//This is the callback function used by globus to notify the changes of job status...
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include "globus_common.h"
#include "globus_gram_client.h"
#include "globus_gsi_credential.h"

#include "globus_gss_assist.h"


GlobusGram::GlobusGram()
{
	char *subject=NULL;
	int ret1;

	ret1=globus_module_activate(GLOBUS_GSI_CREDENTIAL_MODULE);
	if (ret1!=GLOBUS_SUCCESS)
	{
		DEBUG("globus_module_activate(GLOBUS_GSI_CREDENTIAL_MODULE) fail");
		paroc_exception::paroc_throw(POPC_APPSERVICE_FAIL);
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

	ret=globus_gsi_cred_get_subject_name(handle,&subject);
	if (ret!=GLOBUS_SUCCESS)
	{
		DEBUG("globus_gsi_cred_get_subject_name(handle,&subject) fail");
		return;
	}
	mysubject=subject;
	DEBUG("SUBJECT=%s",subject);

	//  globus_module_deactivate(GLOBUS_GSI_CREDENTIAL_MODULE);

}

GlobusGram::~GlobusGram()
{
}

bool GlobusGram::GetUserSubjectName(paroc_string &subject)
{
	subject=mysubject;
	return (mysubject!=NULL);
}

int  GlobusGram::SubmitJob(const paroc_string &gramcontact, const paroc_string &objname, int howmany, const paroc_string &platform, const paroc_accesspoint &jobmgr,
						   const paroc_accesspoint &objcallback, const paroc_string &env)
{
	if (gramcontact==NULL) return POPC_EXEC_FAIL;
	DEBUG("GRAM: %s", (const char *)gramcontact);

	paroc_string contact(gramcontact);
	char *argv[10];
	int status=0;

	if (strncasecmp(contact,"http://",7)==0 || strncasecmp(contact,"https://",8)==0)
	{
		DEBUG("WSGRAM JOB");
		paroc_string jobdesc;
		if (!GenerateWSJobDescription(objname, howmany, platform,jobmgr,objcallback,env,jobdesc))
		{
			DEBUG("Fail to generate RSL for the object %s", (const char *)objname);
			return ENOENT;
		}
		char tmpfile[256];
		int fd;
		sprintf(tmpfile,"/tmp/GRAM_%s_XXXXXX", (const char *)objname);
		if ( (fd=mkstemp(tmpfile))<0 ) return POPC_EXEC_FAIL;
		write(fd, jobdesc.GetString(), jobdesc.Length());
		close(fd);

		argv[0]="globusrun-ws";
		argv[1]="-submit";
		argv[2]="-F";
		argv[3]=contact.GetString();
		argv[4]="-b";
		argv[5]="-q";

		argv[6]="-f";
		argv[7]=tmpfile;
		argv[8]=0;
		int ret=RunCmd(argv,NULL,&status);
		unlink(tmpfile);
		if (ret!=0) return ret;
		if (status!=0)
		{
			DEBUG("globusrun-ws exits with errors");
			return POPC_EXEC_FAIL;
		}
		return 0;

	} else
	{

		paroc_string rsl;
		if (!GenerateJobDescription(objname, howmany, platform,jobmgr,objcallback,env,rsl))
		{
			DEBUG("Fail to generate RSL for the object %s", (const char *)objname);
			return ENOENT;
		}
		argv[0]="globusrun";
		argv[1]="-F";
		argv[2]="-q";
		argv[3]="-r";
		argv[4]=contact.GetString();
		argv[5]=rsl.GetString();
		argv[6]=0;
		int ret=RunCmd(argv,NULL,&status);
		if (ret!=0) return ret;
		if (status!=0)
		{
			DEBUG("globusrun exits with errors");
			return POPC_EXEC_FAIL;
		}
		return 0;
	}
}


bool GlobusGram::GenerateJobDescription(const paroc_string &objname, int howmany,  const paroc_string &platform,
										const paroc_accesspoint &jobmgr, const paroc_accesspoint &objcallback, const paroc_string &env, paroc_string &rsl)
{

	paroc_string codefile;
	char *ptr;
	AppCoreService app(appservice);
	if (!app.QueryCode(objname,platform, codefile))
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

	sprintf(args,"\"-object=%s\" ",(const char *)objname);

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

	sprintf(tok,"\"-appservice=%s\" ",appservice.GetAccessString());

	if (env!=NULL && *env!=0)
		sprintf(tmpcodefile,"&(executable=\"%s\" )(directory =/tmp )(arguments=%s)(environment=%s)(count=%d)",prog,args,(const char *)env, howmany);
	else
		sprintf(tmpcodefile,"&(executable =\"%s\" )(directory =/tmp )(arguments=%s)(count=%d)",prog,args,howmany);

	rsl=tmpcodefile;
	return true;
}





bool GlobusGram::GenerateWSJobDescription(const paroc_string &objname, int howmany,  const paroc_string &platform,
		const paroc_accesspoint &jobmgr, const paroc_accesspoint &objcallback, const paroc_string &env, paroc_string &jobdesc)
{

	paroc_string codefile;
	char *ptr;
	AppCoreService app(appservice);
	if (!app.QueryCode(objname,platform, codefile))
	{
		DEBUG("Can not find the object code for %s, platform %s",(const char *)objname,(const char *)platform);
		return false;
	}

	char sep[]=" \n\t\r";

	char tmpcodefile[10240];
	strcpy(tmpcodefile,codefile);
	char *tok=strtok_r(tmpcodefile,sep,&ptr);
	if (tok==NULL) return false;

	char xml[10240];
	char *tmp=xml;

	sprintf(tmp,"<job><executable>%s</executable>",tok);
	tmp+=strlen(tmp);

	sprintf(tmp,"<argument>-object=%s</argument>\n",(const char *)objname);
	tmp+=strlen(tmp);

	tok=strtok_r(NULL,sep,&ptr);
	while (tok!=NULL)
	{
		sprintf(tmp,"<argument>%s</argument>\n",(const char *)objname);
		tmp+=strlen(tmp);
		tok=strtok_r(NULL,sep,&ptr);
	}
	if (!jobmgr.IsEmpty())
	{
		sprintf(tmp,"<argument>-jobservice=%s</argument>\n",jobmgr.GetAccessString());
		tmp+=strlen(tmp);
	}

	if (!objcallback.IsEmpty())
	{
		sprintf(tmp,"<argument>-callback=%s</argument>\n",objcallback.GetAccessString());
		tmp+=strlen(tmp);
	}

	sprintf(tmp,"<argument>-appservice=%s</argument>\n",appservice.GetAccessString());
	tmp+=strlen(tmp);

	sprintf(tmp,"<count>%d</count></job>",howmany);

	jobdesc=xml;
	return true;
}


