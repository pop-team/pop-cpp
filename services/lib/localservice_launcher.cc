#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "paroc_accesspoint.h"


#ifdef POPC_GLOBUS
#include "appservice_globus.ph"
#else
#include "appservice.ph"
#endif

void Usage()
{
	printf("Usage: localservice_launcher  [-servicepoint=<host>[:port]]  <start [options]> |  <stop>\n\tOptions:\n\t  [-challenge=<string>] [-code=<appservice codefile>] [-conf=<config file>] [-proxy=<POP-C++ proxy>] [-test] [-out=<file> (default:stdout)]\n");
	exit(-1);
}

int main(int argc, char **argv)
{
	int port;
	char objcode[256], host[256];
	paroc_string challenge;

	char *tmp;
	bool stop=(paroc_utils::checkremove(&argc,&argv,"stop")!=NULL);

	if (!stop && paroc_utils::checkremove(&argc,&argv,"start")==NULL) Usage();

	tmp=paroc_utils::checkremove(&argc,&argv,"-challenge=");
	if (tmp!=NULL) challenge=tmp;

	if ((tmp=paroc_utils::checkremove(&argc,&argv,"-servicepoint="))==NULL)
	{
		if (stop)
		{
			fprintf(stderr,"Local service point to stop is missing\n");
			Usage();
		}
		else sprintf(host,"%s:2711",(const char *)paroc_system::GetHost());
	} else strcpy(host,tmp);

	try {
		if (stop)
		{
			paroc_accesspoint pt;
			pt.SetAccessString(host);
			fprintf(stderr,"Connecting to %s...\n" ,host);
			AppCoreService mgr(pt);
			if (mgr.Stop(challenge))
				fprintf(stderr,"...Stopped\n");
			else
				fprintf(stderr,"...fail to stop. Please check the challenge string!\n");
			return 0;
		}

		if ((tmp=paroc_utils::checkremove(&argc,&argv,"-code="))==NULL)
		{
			if ((tmp=getenv("POPC_LOCATION"))==NULL)
			{
				fprintf(stderr,"Error: local service code file is not specified\n");
				Usage();
			}
#ifdef POPC_GLOBUS
			sprintf(objcode,"%s/services/appservice.globus",tmp);
#else
			sprintf(objcode,"%s/services/appservice",tmp);
#endif

		} else strcpy(objcode,tmp);

		if ((tmp=paroc_utils::checkremove(&argc,&argv,"-proxy="))!=NULL)
		{
			strcat(objcode," -proxy=");
			strcat(objcode,tmp);
		}

		char *outfile=paroc_utils::checkremove(&argc,&argv,"-out=");
		FILE *f=(outfile!=NULL)? fopen(outfile,"w+t") : NULL;
		if (f==NULL && outfile!=NULL)
		{
			perror("Open file to store the service access point failed");
			return 1;
		}

#ifdef POPC_GLOBUS
		GlobusAppCoreService info(challenge, true, objcode);
#else
		AppCoreService info(challenge, true, objcode);
#endif

		char *conf=paroc_utils::checkremove(&argc,&argv,"-conf=");
		if (conf!=NULL) paroc_utils::InitCodeService(conf,&info);

		//print out the contact string....
		if (f==NULL)  printf("%s\n",info.GetAccessPoint().GetAccessString());
		else
		{
			fprintf(f,"%s",info.GetAccessPoint().GetAccessString());
			fclose(f);
		}

	}
	catch (int e)
	{
		errno=e;
		perror("Exception occured\n");
		return 1;
	}
	catch (paroc_exception *e)
	{
		errno=e->Code();
		perror("Paroc exception occured\n");
		delete e;
		return 1;
	}
	return 0;
}
