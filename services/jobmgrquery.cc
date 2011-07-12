#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "jobmgr.ph"

int main(int argc, char **argv)
{
	try
	{
		char master[256];
		char slaver[256];
		char str1[256],str2[256];

		if (paroc_utils::checkremove(&argc,&argv,"-help")!=NULL)
		{
			printf("Usage: jobmgrquery [-help] [jobmgr contact | jobmgr host]\n");
			return 0;
		}

		if (argc<=1)
		{
			strcpy(master,paroc_system::GetHost());
		} else strcpy(master,argv[1]);

		if (strchr(master,':')==NULL) strcat(master,":2711");


		paroc_accesspoint job;
		job.SetAccessString(master);
		JobMgr info(job);

		printf("Items: platform, host, jobs, joblist, pausejobs, power_available, ...\n");
		printf("ctrl+D to quit\n");
		printf("Enter item to query:\n");
		while (1)
		{
			if (scanf("%s",str1)!=1) break;
			paroc_string type(str1), val;
			if (info.Query(type,val)) printf("%s= %s\n",str1,(const char *)val);
			else printf("%s= NOT FOUND\n",str1);
		}
	}
	catch (paroc_exception *e)
	{
		paroc_system::perror(e);
		delete e;
	}
}
