#include <stdio.h>
#include <string.h>
#include "jobmgr.ph"
#include "paroc_array.h"

int main(int argc, char **argv)
{
	int howmany;
	if (argc<4 || sscanf(argv[3],"%d",&howmany)!=1 || howmany<=0)
	{
		printf("Usage: alloctest jobmgrcontact object howmany\n");
		return 1;
	}
	paroc_string objname=argv[2];
	paroc_accesspoint job;
	job.SetAccessString(argv[1]);
	paroc_list<paroc_accesspoint> resources;
	paroc_list<int> reserve;

	try
	{
		JobMgr jobmgr(job);
		char buf[1024];
		paroc_od *od=new paroc_od;
		printf("Enter an OD (name values)\n");
		while (fgets(buf,1023,stdin)!=NULL)
		{
			if (strncmp(buf,"done",4)==0)
			{
				paroc_array<paroc_accesspoint> jobcontacts(howmany);
				paroc_array <int> reserveIDs(howmany);
				paroc_array <float> fitness(howmany);
				int count=1;
				printf("Do resource allocation now...\n");
				int requestInfo[3];
				int iptrace[MAX_HOPS];

				for (int i=0;i<howmany;i++) fitness[i]=0;

				if (jobmgr.AllocResource(paroc_system::appservice, objname, *od, howmany, fitness, jobcontacts, reserveIDs, requestInfo, iptrace,0))
				{
					for (int i=0;i<howmany;i++)
					{
						printf("#%d:\t%s (%d)\n", i+1,jobcontacts[i].GetAccessString(),reserveIDs[i]);
						resources.AddTailNew()=jobcontacts[i];
						reserve.AddTail(reserveIDs[i]);
					}
				}
				else
				{
					printf("Alloc fail\n");
				}
				delete od;
				od=new paroc_od;
				printf("Enter next OD\n");
				continue;
			}
			int v1,v2=-1;
			char name[256];
			int t=sscanf(buf,"%s %d %d", name,&v1,&v2);
			if (t<2)
			{
				printf("Error: Bad OD value\n");
				continue;
			}
			if (strcmp(name,"power")==0)
			{
				od->power(v1,v2);
			}
			else if (strcmp(name,"memory")==0)
			{
				od->memory(v1,v2);
			}
			else if (strcmp(name,"np")==0)
			{
				howmany=v1;
			}
			else
			{
				printf("Error: Unkown OD name\n");
			}
		}
		POSITION pos=resources.GetHeadPosition();
		POSITION pos1=reserve.GetHeadPosition();
		while (pos!=NULL)
		{
			paroc_accesspoint &t=resources.GetNext(pos);
			int &r=reserve.GetNext(pos1);
			JobMgr tmp(t);
			tmp.CancelReservation(&r,1);
		}
		resources.RemoveAll();
	}
	catch (...)
	{
		printf("Exception!\n");
		return 1;

	}
}
