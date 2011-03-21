/*
UPDATES : 
Authors		Date			Comment
clementval	2010/04/19	All code added for the semester project begin with this comment 	//Added by clementval
clementval	2010/04/19	All code modified during the semester project begins with //Modified by 								clementval, ends with //End of modification
clementval	2010/05/10	Creating a POPCSearchNode befor creating the JobMgr, change the JobMgr 		creation by passing the POPCSearchNode access point
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "config.h"


/**
 * ViSaG : clementval
 * include the right files for the specified version
 */

//Include GlobusJobMgr, VSJOBMGR, VJOBMGR, SJOBMGR or JOBMGR
#ifdef POPC_GLOBUS
#include "jobmgr_globus.ph"
#elif defined POPC_SECURE_VIRTUAL
#include "virtual_secure_jobmgr.ph"
#include "popcloner.ph"
#elif defined POPC_VIRTUAL
#include "virtual_jobmgr.ph"
#include "popcloner.ph"
#elif defined POPC_SECURE
#include "secure_jobmgr.ph"
#else
#include "jobmgr.ph"
#endif


//Include VPSN, SPSN or PSN
#ifdef POPC_SECURE_VIRTUAL
#include "virtual_secure_popc_search_node.ph"
#elif defined POPC_VIRTUAL
#include "virtual_popc_search_node.ph"
#elif defined POPC_SECURE
#include "secure_popc_search_node.ph"
#else
#include "popc_search_node.ph"
#endif


//Include PSM or VPSM
#ifdef POPC_SECURE_VIRTUAL
#include "virtual_popc_security_manager.ph"
#elif POPC_VIRTUAL
#include "virtual_popc_security_manager.ph"
#elif defined POPC_SECURE
#include "popc_security_manager.ph"
#endif

/* ViSaG */

void Usage()
{
	printf("Usage: jobmgr_launcher [-servicepoint=<host>[:port]] [-port=<port>] <start [options]> | <stop>\n\tOptions:\n\t  [-code=<jobmgr code file>] [-conf=<jobmgr config file>] [-challenge=<string>] [-genchallenge=<out file>] [-proxy=<proxy contact>] [-test]\n");
	exit(1);
}

int main(int argc, char **argv)
{
	paroc_string host;
	paroc_string conf;
   paroc_string virtconf;
	paroc_string objcode;
	paroc_string challenge;
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
#ifdef POPC_SECURE_VIRTUAL
         printf("Stoping POP-C++ [Virtual Secure Version] Global Services\n");
#elif defined POPC_SECURE
         printf("Stoping POP-C++ [Secure Version] Global Services\n");
#elif defined POPC_VIRTUAL
         printf("Stoping POP-C++ [Virtual Version] Global Services\n");
#else
         printf("Stoping POP-C++ [Standard Version] Global Services\n");
#endif
			paroc_accesspoint jobmgr_ap;
			jobmgr_ap.SetAccessString(host);

		
#ifdef POPC_SECURE_VIRTUAL
			VirtSecureJobMgr mgr(jobmgr_ap);
         VirtSecurePOPCSearchNode vspsn(mgr.GetNodeAccessPoint());
			if (!vspsn.Stop(challenge)){
				fprintf(stderr, "Bad challenge string. Cannot stop VSPSN ...\n");
			} else {
            printf("VSPSN stopped successfully!\n");
         }
   
         VirtualPOPCSecurityManager vpsm(mgr.getPSMRef());
         if(!vpsm.Stop(challenge)){
            fprintf(stderr, "Bad challenge string. Cannot stop VPSM ...\n");
         } else {
            printf("VPSM stopped successfully!\n");
         }

         POPCloner pc(mgr.getPOPClonerRef());
         if (!pc.Stop(challenge)){
				fprintf(stderr, "Bad challenge string. Cannot stop POPCloner ...\n");
			} else {
            printf("POPCloner stopped successfully!\n");
         } 

#elif POPC_VIRTUAL
			VirtualJobMgr mgr(jobmgr_ap);
         VirtualPOPCSearchNode vpsn(mgr.GetNodeAccessPoint());
			if (!vpsn.Stop(challenge)){
				fprintf(stderr, "Bad challenge string. Cannot stop VPSN ...\n");
			} else {
            printf("VPSN stopped successfully!\n");
         } 

         POPCloner pc(mgr.getPOPClonerRef());
         if (!pc.Stop(challenge)){
				fprintf(stderr, "Bad challenge string. Cannot stop POPCloner ...\n");
			} else {
            printf("POPCloner stopped successfully!\n");
         } 

#elif defined POPC_SECURE
			SecureJobMgr mgr(jobmgr_ap);
         SecurePOPCSearchNode spsn(mgr.GetNodeAccessPoint());
			if (!spsn.Stop(challenge)){
				fprintf(stderr, "Bad challenge string. Cannot stop SPSN ...\n");
			} else {
            printf("SPSN stopped successfully!\n");
         }
   
         POPCSecurityManager psm(mgr.getPSMRef());
         if(!psm.Stop(challenge)){
            fprintf(stderr, "Bad challenge string. Cannot stop PSM ...\n");
         } else {
            printf("PSM stopped successfully!\n");
         }
#else
			JobMgr mgr(jobmgr_ap);
         POPCSearchNode psn(mgr.GetNodeAccessPoint());
			if (!psn.Stop(challenge)){
				fprintf(stderr, "Bad challenge string. Cannot stop PSN ...\n");
			} else {
            printf("PSN stopped successfully!\n");
         }
#endif
   

			if (!mgr.Stop(challenge))
			{
				fprintf(stderr, "Bad challenge string. Cannot stop JM ...\n");
				return 1;
			}
      
			printf("JobMgr stopped successfully!\n");
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



/**
 * ViSaG : clementval
 * Instantiation of the right services
 */
#ifdef POPC_SECURE_VIRTUAL
   printf("Starting POP-C++ [Virtual Secure Version] Global Services\n");
#elif defined POPC_SECURE
   printf("Starting POP-C++ [Secure Version] Global Services\n");
#elif defined POPC_VIRTUAL
   printf("Starting POP-C++ [Virtual Version] Global Services\n");
#else
   printf("Starting POP-C++ [Standard Version] Global Services\n");
#endif

/*
 * SECURE VIRTUAL VERSION
 */
#ifdef POPC_SECURE_VIRTUAL
      VirtSecurePOPCSearchNode psn(challenge, daemon);
      printf("VSPSN Started [%s]\n", psn.GetAccessPoint().GetAccessString());          

      //Create the VPSM
      VirtualPOPCSecurityManager psm(challenge, daemon);
      printf("VPSM Started [%s]\n", psm.GetAccessPoint().GetAccessString());

      //Give reference to other services
      psm.setPSNRef(psn.GetAccessPoint());
      psn.setPSMRef(psm.GetAccessPoint());

      //Init the SSH mode on the VPSM
      psm.initSSHMode(); 

/*
 * VIRTUAL VERSION
 */
#elif POPC_VIRTUAL
      //Create the VPSN
		VirtualPOPCSearchNode psn(challenge, daemon);
      printf("VPSN Started [%s]\n", psn.GetAccessPoint().GetAccessString());      

/*
 * SECURE VERSION
 */
#elif defined POPC_SECURE
      //Create the PSM
      POPCSecurityManager psm(challenge, daemon);
      printf("PSM created [%s]\n", psm.GetAccessPoint().GetAccessString());

      //Create the SPSN
      SecurePOPCSearchNode psn(challenge, daemon);
		printf("SPSN [%s]\n", psn.GetAccessPoint().GetAccessString());

      //Give references to other services
      psm.setPSNRef(psn.GetAccessPoint());
      psn.setPSMRef(psm.GetAccessPoint());

      //Init the ssh secure mode on the PSM
      psm.initSSHMode();

/*
 * STANDARD VERSION
 */
#else
      POPCSearchNode psn(challenge, daemon);
      printf("PSN Started [%s]\n", psn.GetAccessPoint().GetAccessString());
#endif
		
      /* ViSaG */




#ifdef POPC_GLOBUS
		GlobusJobMgr info(daemon, conf,challenge, host);
#elif defined POPC_SECURE_VIRTUAL
      //Create the POPCloner
      POPCloner cloner(challenge, daemon);
      printf("POPCloner Started [%s]\n", cloner.GetAccessPoint().GetAccessString());
      //Save the POPCloner access point in the system
      paroc_system::popcloner = cloner.GetAccessPoint();
      
      try{
         //Create the VJobMgr
         VirtSecureJobMgr info(daemon, virtconf, conf, challenge, host, psn.GetAccessPoint(), cloner.GetAccessPoint(), psm.GetAccessPoint());
         printf("VSJM created [%s]\n", info.GetAccessPoint().GetAccessString());
         psm.setJobMgrRef(info.GetAccessPoint());
      } catch (...){
         fprintf(stderr, "Error: Need to stop VSPSN, VPSM and POPCloner\n");
         //Stop the created PSN         
         if(!psn.Stop(challenge)){
            fprintf(stderr, "Bad challenge string. Cannot stop VSPSN ...\n");
         } else {
            printf("VSPSN stopped successfully!\n");
         }
         //Stop the created PSM
         if(!psm.Stop(challenge)){
            fprintf(stderr, "Bad challenge string. Cannot stop VPSM ...\n");
         } else {
            printf("VPSM stopped successfully!\n");
         }
         //Stop the created POPCloner
         if(!cloner.Stop(challenge)){
            fprintf(stderr, "Bad challenge string. Cannot stop POPCloner ...\n");
         } else {
            printf("POPCloner stopped successfully!\n");
         }
      }
#elif defined POPC_VIRTUAL
      //Create the POPCloner
      POPCloner cloner(challenge, daemon);
      printf("POPCloner Started [%s]\n", cloner.GetAccessPoint().GetAccessString());
      //Save the POPCloner access point in the system
      paroc_system::popcloner = cloner.GetAccessPoint();

      try{
         //Create the VJobMgr
         paroc_accesspoint empty;
         VirtualJobMgr info(daemon, virtconf, conf, challenge, host, psn.GetAccessPoint(), cloner.GetAccessPoint(), empty);
         printf("VJM created [%s]\n", info.GetAccessPoint().GetAccessString());
      } catch (...){
         fprintf(stderr, "Error: Need to stop VPSN and POPCloner\n");
         //Stop the created PSN         
         if(!psn.Stop(challenge)){
            fprintf(stderr, "Bad challenge string. Cannot stop VPSN ...\n");
         } else {
            printf("VPSN stopped successfully!\n");
         }
         //Stop the created POPCloner
         if(!cloner.Stop(challenge)){
            fprintf(stderr, "Bad challenge string. Cannot stop POPCloner ...\n");
         } else {
            printf("POPCloner stopped successfully!\n");
         }
      }

#elif defined POPC_SECURE
      try{
         //Create the SJobMgr
         SecureJobMgr info(daemon, conf, challenge, host, psn.GetAccessPoint(), psm.GetAccessPoint());
         printf("SJM created [%s]\n", info.GetAccessPoint().GetAccessString());
         psm.setJobMgrRef(info.GetAccessPoint());
      } catch (...){
         fprintf(stderr, "Error: Need to stop SPSN and PSM\n");
         //Stop the created PSN         
         if(!psn.Stop(challenge)){
            fprintf(stderr, "Bad challenge string. Cannot stop SPSN ...\n");
         } else {
            printf("SPSN stopped successfully!\n");
         }
         //Stop the created PSM
         if(!psm.Stop(challenge)){
            fprintf(stderr, "Bad challenge string. Cannot stop PSM ...\n");
         } else {
            printf("SPSN stopped successfully!\n");
         }
      }
#else
      try{
         //Create the base JobMgr
         paroc_accesspoint empty;
	   	JobMgr info(daemon, conf, challenge, host, psn.GetAccessPoint(), empty);
         printf("JM created [%s]\n", info.GetAccessPoint().GetAccessString());
      } catch(...){
         fprintf(stderr, "Error: Need to stop PSN\n");
         if(!psn.Stop(challenge)){
            fprintf(stderr, "Bad challenge string. Cannot stop PSN ...\n");
			} else {
            printf("PSN stopped successfully!\n");
         }
      }
      
#endif
		if (daemon)
		{
			return 0;
		}
		//Testing....
	/*	printf("Get Info:\n");
		char type[64];
		while (1)
		{
			printf("Information type:\n");
			if (scanf("%s",type)!=1) break;
			try
			{
				paroc_string typestr(type), val;
				if (info.Query(typestr,val))
				{
					printf("%s: \tType=%s\tValue=%s\n",info.GetAccessPoint().GetAccessString(), type, (const char *)val);
				}
				else
				{
					printf("%s: \tValue not found\n",info.GetAccessPoint().GetAccessString());
				}
			}
			catch (paroc_exception *e)
			{
				errno=e->Code();
				paroc_system::perror("Invoke exception occurs\n");
				delete e;
			}
		}*/
	}
	catch (paroc_exception *e)
	{
		errno=e->Code();
		paroc_system::perror("Exception occurs\n");
		delete e;
		return 1;
	}
	return 0;
}
