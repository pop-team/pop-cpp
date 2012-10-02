/*
UPDATES : 
Authors		Date			Comment
clementval	2010/04/19	All code added for the semester project begin with this comment 	//Added by clementval
clementval	2010/04/19	All code modified during the semester project begins with //Modified by 								clementval, ends with //End of modification
clementval	2010/05/10	Creating a POPCSearchNode before creating the JobMgr, change the JobMgr creation by passing the POPCSearchNode access point
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "config.h"



//Include GlobusJobMgr, VSJOBMGR, VJOBMGR, SJOBMGR or JOBMGR
#ifdef POPC_GLOBUS
#include "jobmgr_globus.ph"
#else
#include "jobmgr.ph"
#endif


#include "popc_search_node.ph"



void Usage()
{
	printf("Usage: jobmgr_launcher [-servicepoint=<host>[:port]] [-port=<port>] <start [options]> | <stop>\n\tOptions:\n\t  [-code=<jobmgr code file>] [-conf=<jobmgr config file>] [-challenge=<string>] [-genchallenge=<out file>] [-proxy=<proxy contact>] [-test]\n");
	exit(1);
}

int main(int argc, char **argv)
{
	POPString host;
	POPString conf;
   POPString virtconf;
	POPString objcode;
	POPString challenge;
	char str[1024];


	char *tmp;
	bool stop=(paroc_utils::checkremove(&argc,&argv,"stop")!=NULL);
	if (!stop && paroc_utils::checkremove(&argc,&argv,"start")==NULL) Usage();

	if ((tmp=paroc_utils::checkremove(&argc,&argv,"-servicepoint="))==NULL)
	{
		tmp=paroc_utils::checkremove(&argc,&argv,"-port=");
		if (tmp==NULL) sprintf(str,"%s:2711",(const char *)paroc_system::GetHost());
		else sprintf(str,"%s:%s",(const char *)paroc_system::GetHost(),tmp);
	}
	else
	{
		strcpy(str,tmp);
		if (strchr(str,':')==NULL) strcat(str,":2711");
	}

	host=str;


	

	tmp=paroc_utils::checkremove(&argc,&argv,"-challenge=");
	if (tmp!=NULL) challenge=tmp;
	else if ((tmp=paroc_utils::checkremove(&argc,&argv,"-genchallenge="))!=NULL && !stop)
	{

		srand(time(NULL));
		char tmpstr[256];
		for (int i=0;i<255;i++) tmpstr[i]=(char)('A'+23.0*rand()/(RAND_MAX+1.0) );
		tmpstr[255]=0;
		challenge=tmpstr;
		int fd=creat(tmp,O_CREAT | S_IRUSR | S_IWUSR);
		if (fd<0)
		{
			perror("Challenge output file");
			return 1;
		}
		if (write(fd,tmpstr,255)!=255)
		{
			perror("Error on writing challenge string");
			return 1;
		}
		close(fd);
	}
	try
	{
		if (stop)
		{

			printf("Stoping POP-C++ %s [Standard] Global Services\n", VERSION);
			paroc_accesspoint jobmgr_ap;
			jobmgr_ap.SetAccessString(host);
			
			

		

			JobMgr mgr(jobmgr_ap);
         
         POPCSearchNode psn(mgr.GetNodeAccessPoint());
			if (!psn.Stop(challenge)){
				fprintf(stderr, "[POP-C++ Runtime] Bad challenge string. Cannot stop PSN ...\n");
			} else {
            printf("[POP-C++ Runtime] PSN stopped successfully!\n");
         }

   

			if (!mgr.Stop(challenge))
			{
				fprintf(stderr, "[POP-C++ Runtime] Bad challenge string. Cannot stop JM ...\n");
				return 1;
			}
      
			printf("[POP-C++ Runtime] JobMgr stopped successfully!\n");
			return 0;
		}


		if ((tmp=paroc_utils::checkremove(&argc,&argv,"-conf="))==NULL && (tmp=getenv("JOBMGR_CONF"))==NULL)
		{
			char *paroc_location=getenv("POPC_LOCATION");
			if (paroc_location==NULL)
			{
				fprintf(stderr,"ERROR: POPC_LOCATION environment variable is not set.\n");
				Usage();
			}

#ifdef POPC_GLOBUS
			sprintf(str,"%s/etc/jobmgr.globus.conf",paroc_location);
#else
			sprintf(str,"%s/etc/jobmgr.conf",paroc_location);
#endif
			conf=str;

         sprintf(str, "%s/etc/virtual.conf", paroc_location);
         virtconf=str;

		} else conf=tmp;

		bool daemon=(paroc_utils::checkremove(&argc,&argv,"-test")==NULL);




   printf("Starting POP-C++ %s [Standard] Global Services\n", VERSION);


		/*
		 * STANDARD VERSION
		 */
      
      // Start the POP-C++ Search Node service
      POPCSearchNode psn(challenge, daemon);
      printf("[POP-C++ Runtime] PSN Started [%s]\n", psn.GetAccessPoint().GetAccessString());   



#ifdef POPC_GLOBUS
		GlobusJobMgr info(daemon, conf,challenge, host);
#else
      try{
         //Create the base JobMgr
         paroc_accesspoint empty;
         psn.GetAccessPoint();
	   	JobMgr info(daemon, conf, challenge, host, psn.GetAccessPoint(), empty);
         printf("[POP-C++ Runtime] JM created [%s]\n", info.GetAccessPoint().GetAccessString());
      } catch(...) {
         fprintf(stderr, "Error: Need to stop PSN\n");
         if(!psn.Stop(challenge)){
            fprintf(stderr, "Bad challenge string. Cannot stop PSN ...\n");
			} else {
            printf("PSN stopped successfully!\n");
         }
      }
#endif
		if (daemon) {
			return 0;
		}
	} catch (paroc_exception *e) {
		errno=e->Code();
		paroc_system::perror("Exception occurs\n");
		delete e;
		return 1;
	}
	return 0;
}
