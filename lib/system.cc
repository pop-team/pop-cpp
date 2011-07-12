/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: system stuffs and declarations used by the runtime
 */

#include <stdio.h>

#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

#include "paroc_system.h"
#include <appservice.ph>
#include <paroc_buffer_factory_finder.h>
#include <paroc_utils.h>

paroc_accesspoint paroc_system::appservice;
paroc_accesspoint paroc_system::jobservice;
paroc_string paroc_system::platform;
const char *paroc_system::paroc_errstr[17]=
	{"Out of resource",
	 "Fail to bind to the remote object broker",
	 "Mismatch remote method id",
	 "Can not access code service",
	 "Object allocation failed",
	 "No parallel object executable",
	 "Bad paroc package format",
	 "POP-C++ local application service failed",
	 "POP-C++ job manager service failed",
	 "Execution of object code failed",
	 "Bad binding reply",
	 "No support protocol",
	 "No support data encoding",
	 "standard exception",
	 "Acknowledgement not received",
	 "Network configuration error",
	 "Unknown POP-C++ exception"
	};


AppCoreService *paroc_system::mgr=NULL;
paroc_string paroc_system::challenge;

paroc_system::paroc_system()
{
	paroc_combox_factory::GetInstance();
	paroc_buffer_factory_finder::GetInstance();
	char *tmp=getenv("POPC_PLATFORM");
	if (tmp!=NULL)
	{
		platform=tmp;
	}
	else
	{
		char str[128];

#ifndef POPC_ARCH
		char arch[64], sysname[64];
		sysinfo(SI_SYSNAME,sysname,64);
		sysinfo(SI_ARCHITECTURE,arch,64);
		sprintf(str,"%s-%s",sysname,arch);
#else
		strcpy(str,POPC_ARCH);
#endif
		platform=str;
	}
}


paroc_system::~paroc_system()
{
	if (mgr!=NULL)
	{
		Finalize(false);
		delete mgr;
	}
	mgr=NULL;

	paroc_combox_factory *pf=paroc_combox_factory::GetInstance();
	paroc_buffer_factory_finder *bf=paroc_buffer_factory_finder::GetInstance();
	pf->Destroy();
	delete bf;
}


void paroc_system::perror(const char *msg)
{
	//DEBUG("paroc_system::perror : %d",errno);
	if (errno>USER_DEFINE_ERROR && errno<=USER_DEFINE_LASTERROR)
	{
		if (msg==NULL) msg="Error";
		fprintf(stderr,"%s: %s (errno %d)\n",msg,paroc_errstr[errno-USER_DEFINE_ERROR-1],errno);
	}
	else if (errno>USER_DEFINE_LASTERROR) fprintf(stderr,"%s: Unknown error (errno %d)\n",msg, errno);
	else ::perror(msg);
}

void paroc_system::perror(const paroc_exception *e)
{
	errno=e->Code();
	paroc_system::perror((const char*)e->Extra());
}

paroc_string paroc_system::GetHost()
{
	char str[128];
	char *t=getenv("POPC_HOST");
	if (t==NULL || *t==0)
	{
		gethostname(str,127);
		if (strchr(str,'.')==NULL || strstr(str,".local\0")!=NULL)
		{
			int len=strlen(str);
			char *domain=getenv("POPC_DOMAIN");
			if (domain!=NULL && domain!=0)
			{
				str[len]='.';
				strcpy(str+len+1,domain);
			}
			else
			{
				//DEBUG("GetHost returns %s",(const char*)GetIP());
				return GetIP();
			}
		}
		return paroc_string(str);
	} else return paroc_string(t);
}


paroc_string paroc_system::GetIP()
{
	paroc_string iface,ip;
	char* tmp;
	tmp=getenv("POPC_IP");
	if (tmp!=NULL) {
		ip=tmp;
		return tmp;
	}

	tmp=getenv("POPC_IFACE");
	if (tmp!=NULL) {
		iface=tmp;
		if (GetIPFromInterface(iface,ip)) {return ip;}
		DEBUG("Warning: Cannot find an IP for interface %s.",(const char*)iface);
	}
	iface=GetDefaultInterface();
	if (GetIPFromInterface(iface,ip)) {return ip;}

	DEBUG("Warning: host IP not found, using 127.0.0.1 as IP address.");
	return paroc_string("127.0.0.1");
}

int paroc_system::GetIP(const char *hostname, int *iplist, int listsize)
{
	assert(listsize==1); /* This method should normally not be used to return more than one ip*/
	struct hostent *hp;
	int n;
	char **p;
	int addr;
	if ((int)(addr = inet_addr(hostname)) == -1)
	{
		hp=gethostbyname(hostname);
	}
	else
	{
		if (listsize>0)
		{
			*iplist=ntohl(addr);
			return 1;
		}
		return 0;
	}
	if (hp==NULL) return 0;
	n=0;
	for (p = hp->h_addr_list; *p != 0 && n<listsize; p++)
	{
		memcpy(iplist, *p, sizeof (int));
		*iplist=ntohl(*iplist);
		if (*iplist==(int(127)<<24)+1) continue;
		n++;
		iplist++;

	}
	endhostent();
	if (n==0) n=1;
	return n;
}


int paroc_system::GetIP(int *iplist, int listsize)
{
	assert(listsize==1); /* This method cannot return more than one ip*/
	char* parocip=strdup((const char*)GetIP());
	int n;
	int addr;
	char *tmp;
	char *tok=strtok_r(parocip," \n\r\t",&tmp);
	n=0;
	while (tok!=NULL && n<listsize) {
		if ((int)(addr = inet_addr(tok)) != -1) {
			*iplist=ntohl(addr);
			iplist++;
			n++;
		}
		tok=strtok_r(NULL," \n\r\t",&tmp);
	}
	return n;
}

paroc_string paroc_system::GetDefaultInterface()
{
	char buff[1024], iface[16], net_addr[128];
	//char flags[64], mask_addr[128], gate_addr[128];
	//int iflags, metric, refcnt, use, mss, window, irtt;
	FILE *fp = fopen("/proc/net/route", "r");

	if (!fp) {
		paroc_exception::paroc_throw(POPC_NETWORK_FAIL,"Cannot open /proc/net/route to get the default network interface. To avoid this specify POPC_IFACE=<myinterface> or POPC_IP=<myip> at installation.");
	}
	bool found=false;
	while (fgets(buff, 1023, fp) && !found) {
		//num = sscanf(buff, "%16s %128s %128s %X %d %d %d %128s %d %d %d",
		//	     iface, net_addr, gate_addr, &iflags, &refcnt, &use, &metric, mask_addr, &mss, &window, &irtt);
		int num = sscanf(buff, "%16s %128s",iface, net_addr);
		if (num < 2)
			paroc_exception::paroc_throw_errno();
		//DEBUG("iface %s, net_addr %s, gate_addr %s, iflags %X, &refcnt %d, &use %d, &metric %d, mask_addr %s, &mss %d, &window %d, &irtt %d\n\n",iface, net_addr, gate_addr,iflags, refcnt, use, metric, mask_addr, mss, window, irtt);

		if (!strcmp(net_addr,"00000000")) {
			//DEBUG("Default gateway : %s", iface);
			found=true;
		}
	}

	(void) fclose(fp);
	if (found)
		return paroc_string(iface);
	else return paroc_string("(error)");
}

bool paroc_system::GetIPFromInterface(paroc_string& iface, paroc_string& str_ip)
{
	struct ifaddrs *addrs, *iap;
	struct sockaddr_in *sa;
	char str_ip_local[32];

	getifaddrs(&addrs);

	for (iap = addrs; iap != NULL; iap = iap->ifa_next)//printf("%s fam %d\n",iap->ifa_name,iap->ifa_addr->sa_family);
		if (iap->ifa_addr && (iap->ifa_flags & IFF_UP) && iap->ifa_addr->sa_family == AF_INET
				&& !strcmp(iap->ifa_name,(const char*)iface)) {
			sa = (struct sockaddr_in *)(iap->ifa_addr);
			inet_ntop(iap->ifa_addr->sa_family, (void *)&(sa->sin_addr), str_ip_local, sizeof(str_ip_local));

			//DEBUG("The IP of interface %s is %s",iap->ifa_name,str_ip_local);
			str_ip=str_ip_local;
			freeifaddrs(addrs);
			return true;
		}
	freeifaddrs(addrs);
	return false;
}


bool paroc_system::Initialize(int *argc,char ***argv)
{
	char *info=paroc_utils::checkremove(argc,argv,"-jobservice=");
	if (info==NULL) return false;
	paroc_system::jobservice.SetAccessString(info);

	char *codeser=paroc_utils::checkremove(argc,argv,"-appservicecode=");
	char *proxy=paroc_utils::checkremove(argc,argv,"-proxy=");

	if (paroc_utils::checkremove(argc,argv,"-runlocal"))  paroc_od::defaultLocalJob=true;
	char *appcontact=paroc_utils::checkremove(argc,argv,"-appservicecontact=");

	if (codeser==NULL && appcontact==NULL) return false;

	try {
		if (appcontact==NULL)
		{
			char url[1024];
			if (proxy==NULL) strcpy(url,codeser);
			else sprintf(url,"%s -proxy=%s",codeser, proxy);
			mgr=CreateAppCoreService(url);
		}
		else
		{
			challenge=NULL;
			paroc_accesspoint app;
			app.SetAccessString(appcontact);
			mgr=new AppCoreService(app);
		}

		paroc_system::appservice=mgr->GetAccessPoint();
	}
	catch (POPException *e)
	{
		printf("Exception occurs in paroc_system::Initialize\n");
		POPSystem::perror(e);
		delete e;
		if (mgr!=NULL)
		{
			mgr->KillAll();
			mgr->Stop(challenge);
			delete mgr;
			mgr=NULL;
		}

		return false;
	}
	catch (...)
	{
		if (mgr!=NULL)
		{
			mgr->KillAll();
			mgr->Stop(challenge);
			delete mgr;
			mgr=NULL;
		}
		return false;
	}

	char *codeconf=paroc_utils::checkremove(argc,argv,"-codeconf=");

	DEBUGIF(codeconf==NULL,"No code config file\n");

	if (codeconf!=NULL && !paroc_utils::InitCodeService(codeconf,mgr)) return false;

	return true;


}

void paroc_system::Finalize(bool normalExit)
{

	if (mgr!=NULL)
	{
		try
		{
			if (normalExit)
			{
				//Wait all object to be terminated!
				int timeout=10;
				int oldcount=0, count;

				while ((count=mgr->CheckObjects())>0)
				{
					if (timeout<1800 && oldcount==count) timeout=timeout*4/3;
					else timeout=10;

					sleep(timeout);
					oldcount=count;
				}
			}
			else mgr->KillAll();

			mgr->Stop(challenge);
			delete mgr;
			//	DEBUG("Application scope services are terminated");
		}
		catch (paroc_exception *e)
		{
			paroc_system::perror(e->Extra());
			delete e;
		}
		catch (...)
		{
			fprintf(stderr,"ERROR on finalizing the application\n");
		}
		mgr=NULL;
	}
}



AppCoreService *paroc_system::CreateAppCoreService(char *codelocation)
{
	int i=0;
	int range=40;
	srand(time(NULL));
	char tmp[256];

	for (int i=0;i<255;i++) tmp[i]=(char)(1+254.0*rand()/(RAND_MAX+1.0) );
	tmp[255]=0;
	challenge=tmp;

	return new AppCoreService(challenge, false, codelocation);
}


void paroc_system::processor_set(int cpu)
{
#ifndef ARCH_MAC
	//debug(1, "cpu=%d", cpu);
	if (cpu < 0) {
		printf("Warning : Cannot set processor to %d<0", cpu);
		exit(EXIT_FAILURE);
	}
	if (cpu >= CPU_SETSIZE) {
		printf("Warning : Cannot set processor to %d while CPU_SETSIZE=%d", cpu, CPU_SETSIZE);
		exit(EXIT_FAILURE);
	}

	cpu_set_t cpu_set;
	CPU_ZERO(&cpu_set);
	CPU_SET(cpu, &cpu_set);
	if (sched_setaffinity(0, sizeof(cpu_set), &cpu_set) == -1) {
		printf("Warning : Cannot set processor to %d (cpu_set %p)", cpu,(void *)&cpu_set);
		exit(EXIT_FAILURE);
	}

	cpu_set_t cpu_get;
	CPU_ZERO(&cpu_get);
	if (sched_getaffinity(0, sizeof(cpu_get), &cpu_get) == -1) {
		printf("Warning : Unable to sched_getaffinity to (cpu_get) %p", (void *)&cpu_get);
		exit(EXIT_FAILURE);
	}

	if (memcmp(&cpu_get, &cpu_set, sizeof(cpu_set_t))) {
		printf("Warning : Unable to run on cpu %d", cpu);
		exit(EXIT_FAILURE);
	}
#endif
}
