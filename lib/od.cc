/**
 * File : od.cc
 * Author : Tuan Anh Nguyen
 * Description : parallel object description implementation
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval  05/2010     Add od.search support
 * clementval  10/2010     Add od.service support
 */

#include "paroc_od.h"
#include <unistd.h>

bool paroc_od::defaultLocalJob=false;


paroc_od::paroc_od()
{
	mflops=min_mflops=ram=min_ram=net=min_net=time=-1;
#ifdef OD_DISCONNECT
	time_alive=time_control=-1;
#endif
	isManual=false;
	batchSystem=getenv("POPC_BATCH");
	if (batchSystem!=NULL)hostname=batchSystem; // To avoid letting the hostname empty
	isLocalJob=defaultLocalJob;
	sameDirectory(true); // Set the working directory to the current one by default
   secureSet=false;
   searchSet=false;
   serviceSet=false;
	max_depth=100;
	max_size=0;
	wait_time=0;
}

paroc_od::~paroc_od()
{
}


/** 
 * ViSaG : clementval
 * Set the value of the od service
 * @param serv Boolean value to set to the od service
 */
void paroc_od::service(bool serv){
   serviceSet=serv;
}

/**
 * ViSaG : clementval
 * Check is the od service is set 
 * @return TRUE is the od service is set
 */
bool paroc_od::isServiceSet() const {
   return serviceSet;
}

void paroc_od::power(float require, float min)
{
	if (min>require)
	{
		float t=min;
		min=require;
		require=t;
	}
	mflops=require;
	min_mflops=min;
}

void paroc_od::memory(float require, float min)
{
	if (min>require)
	{
		float t=min;
		min=require;
		require=t;
	}
	ram=require;
	min_ram=min;
}

void paroc_od::bandwidth(float require, float min)
{
	if (min>require)
	{
		float t=min;
		min=require;
		require=t;
	}
	net=require;
	min_net=min;
}

void paroc_od::walltime(float t)
{
	time=t;
}

void paroc_od::url(const char *str)
{
	char h[256];
	char *tmpstr;
	strcpy(h,str);

	// Read if user specified for rsh/ssh
	if (h!=NULL&&(tmpstr=strchr(h,'@'))!=NULL)
	{
		*tmpstr=0;
		hostuser=h;
		strcpy(h,tmpstr+1);
	}
	// Read if core specified
	if (h!=NULL&&(tmpstr=strchr(h,'{'))!=NULL)
	{
		*tmpstr=0;
		char * tmpstr2;
		if ((tmpstr2=strchr(tmpstr+1,'}'))!=NULL)
		{
			*tmpstr2=0;
			hostcore=tmpstr+1;
		}
		else
		{
			DEBUG("Error in object description. user@ip(core):port");
		}

	}
	hostname=h;
	if (!strcmp(hostname,"localhost"))runLocal(true);
}

void paroc_od::url(const char *h, const char *arch)
{
	hostarch=arch;
	url(h);
}

/*void paroc_od::url(std::string h)
{
	url((const char*)h.c_str());
}*/
/*void paroc_od::url(std::string h, std::string arch)
{
	url((const char*)h.c_str(),(const char*)arch.c_str());
}*/
void paroc_od::joburl(const char *jobservice)
{
	jobcontact=jobservice;
}

void paroc_od::executable(const char *code)
{
	codefile=code;
}


void paroc_od::protocol(const char *myproto)
{
	if (myproto==NULL) return;
	proto=myproto;
}

void paroc_od::encoding(const char *myencode)
{
	if (myencode==NULL) return;
	encode=myencode;
}

void paroc_od::manual(bool a)
{
	url("localhost");
	isManual=a;
}

void paroc_od::runLocal(bool isLocal)
{
	isLocalJob=isLocal;
}

// Set working directory
void paroc_od::directory(const char *h)
{
	cwd=h;
}

//Set working dir to the current dir on interface side
void paroc_od::sameDirectory(bool a)
{
	if (a) {
		char tmp[256];
		if (getcwd(tmp,sizeof(tmp))!=NULL) {
			cwd=tmp;
		} else DEBUG("getcwd returned an error!");
	}
}

//Added by clementval
//set resource discovery parameter
void paroc_od::search(int maxdepth, int maxsize, int waittime){
	searchSet = true;
	max_depth=maxdepth;
	max_size=maxsize;
	wait_time=waittime;
}

//Return max depth
int paroc_od::getSearchMaxDepth() const {
	return max_depth;
}

//Return max requst size
int paroc_od::getSearchMaxReqSize() const {
	return max_size;
}

//Return discovery request waiting time
int paroc_od::getSearchWaitTime() const {
	return wait_time;
}

//Return true if the od.search is set
bool paroc_od::isSearchSet() const {
	return searchSet;
}
//End of add


//Used to specify if the used protocol is secure
void paroc_od::secure(int foo){
   secureSet=true;
}

bool paroc_od::isSecureSet() const {
   return secureSet;
}




//Methods used by Runtime system
void paroc_od::getPower(float &require, float &min) const
{
	require=mflops;
	min=min_mflops;
}

void paroc_od::getMemory(float &require, float &min) const
{
	require=ram;
	min=min_ram;
}

void paroc_od::getBandwidth(float &require, float &min) const
{
	require=net;
	min=min_net;
}

float paroc_od::getWallTime() const
{
	return time;
}

void paroc_od::getDirectory(POPString &str) const
{
	str=cwd;
}

void paroc_od::getURL(POPString &url) const
{
	url=hostname;
}

void paroc_od::getUser(POPString &s) const
{
	s=hostuser;
}

void paroc_od::getCore(POPString &s) const
{
	s=hostcore;
}

void paroc_od::getArch(POPString &s) const
{
	s=hostarch;
}

void paroc_od::getJobURL(POPString &joburl) const
{
	joburl=jobcontact;
}

void paroc_od::getExecutable(POPString &exec) const
{
	exec=codefile;
}

void paroc_od::getProtocol(POPString &myproto) const
{
	//DEBUG("Set protocol in OD %s\n", myproto.GetString());
	myproto=proto;
}

void paroc_od::getEncoding(POPString &myencode) const
{
	myencode=encode;
}

bool paroc_od::getIsManual() const
{
	return isManual;
}

void paroc_od::getBatch(POPString& batch) const
{
	batch=batchSystem;
}


#ifdef OD_DISCONNECT
void paroc_od::getCheckConnection(int &my_time_alive, int &my_time_control) const
{
	my_time_alive=time_alive;
	my_time_control=time_control;
}
bool paroc_od::getCheckConnection() const
{
	int  time_alive;
	int  time_control;
	getCheckConnection(time_alive, time_control);
	if (time_alive!=-1 && time_control!=-1) {
		return true;
	}
	return false;
}
void paroc_od::checkConnection(int t_a, int t_c)
{
	if (t_a==-1&&t_c==-1) {
		time_alive=-1;
		time_control=-1;
	} else {
		if (t_a > 0)
			time_alive = t_a;
		else
			time_alive = TIME_ALIVE;
		if (t_c > 0)
			time_control = t_c;
		else
			time_control = TIME_CONTROL;
	}
}

void paroc_od::checkConnection(bool doCheck)
{
	if (doCheck)checkConnection(TIME_ALIVE, TIME_CONTROL);
}
#endif

paroc_od &paroc_od::operator =(const paroc_od &od)
{
	if (&od!=this)
	{
		od.getPower(mflops,min_mflops);
		od.getMemory(ram,min_ram);
		od.getBandwidth(net,min_net);
		time=od.getWallTime();
		od.getURL(hostname);
		od.getJobURL(jobcontact);
		od.getExecutable(codefile);
		od.getProtocol(proto);
		od.getEncoding(encode);
#ifdef OD_DISCONNECT
		od.getCheckConnection(time_alive, time_control);
#endif
		runLocal(od.IsLocal());
	}
	return *this;
}

bool paroc_od::IsEmpty() const
{
	return (mflops<0 && min_mflops<0 && ram<0 && min_ram<0 && net<0 && min_net<0 && time<0 && hostname==NULL /*&& time_alive < 0 && time_control < 0*/);
}

bool paroc_od::IsLocal() const
{
	return isLocalJob;
}

void paroc_od::setPlatforms(const char *objplatforms)
{
	platforms=objplatforms;
}


void paroc_od::getPlatforms(POPString &objplatforms) const
{
	objplatforms=platforms;
}

void paroc_od::setValue(const POPString &key, const POPString &val)
{
	POPString &t1=keys.AddTailNew();
	POPString &t2=values.AddTailNew();
	t1=key;
	t2=val;
}

void paroc_od::getValue(const POPString &key, POPString &val)
{
	POSITION posk=keys.GetHeadPosition();
	POSITION posv=values.GetHeadPosition();

	while (posk!=NULL)
	{
		POPString &t1=keys.GetNext(posk);
		POPString &t2=values.GetNext(posv);
		if (paroc_utils::isEqual(t1,key))
		{
			val=t2;
			return;
		}
	}
	val=NULL;
}

void paroc_od::Serialize(paroc_buffer &buf, bool pack)
{
	float val[2];
	int valInt[2];
	int valSearch[3];
	POPString t;
	if (pack)
	{

		getPower(val[0],val[1]);
		buf.Push("power","float",2);
		buf.Pack(val,2);
		buf.Pop();

		getMemory(val[0],val[1]);
		buf.Push("memory","float",2);
		buf.Pack(val,2);
		buf.Pop();

		getBandwidth(val[0],val[1]);
		buf.Push("bandwidth","float",2);
		buf.Pack(val,2);
		buf.Pop();

		val[0]=getWallTime();
		buf.Push("walltime","float",1);
		buf.Pack(val,1);
		buf.Pop();

		valInt[0]=getIsManual();
		buf.Push("manual","int",1);
		buf.Pack(valInt,1);
		buf.Pop();

		getDirectory(t);
		buf.Push("cwd","POPString",1);
		buf.Pack(&t,1);
		buf.Pop();

		//Added by clementval
		valSearch[0] = getSearchMaxDepth();
		valSearch[1] = getSearchMaxReqSize();
		valSearch[2] = getSearchWaitTime();
		buf.Push("search", "int", 3);
		buf.Pack(valSearch, 3);
		buf.Pop();		
		//End of add

		getURL(t);
		buf.Push("url","POPString",1);
		buf.Pack(&t,1);
		buf.Pop();

		getUser(t);
		buf.Push("user","POPString",1);
		buf.Pack(&t,1);
		buf.Pop();

		getCore(t);
		buf.Push("core","POPString",1);
		buf.Pack(&t,1);
		buf.Pop();

		getArch(t);
		buf.Push("arch","POPString",1);
		buf.Pack(&t,1);
		buf.Pop();

		getBatch(t);
		buf.Push("batch","POPString",1);
		buf.Pack(&t,1);
		buf.Pop();

		

		getJobURL(t);
		buf.Push("joburl","POPString",1);
		buf.Pack(&t,1);
		buf.Pop();

		getExecutable(t);
		buf.Push("executable","POPString",1);
		buf.Pack(&t,1);
		buf.Pop();

		getPlatforms(t);
		buf.Push("platforms","POPString",1);
		buf.Pack(&t,1);
		buf.Pop();

		getProtocol(t);
		buf.Push("protocol","POPString",1);
		buf.Pack(&t,1);
		buf.Pop();

		getEncoding(t);
		buf.Push("encoding","POPString",1);
		buf.Pack(&t,1);
		buf.Pop();

		//Pack additional attributes
		int count=keys.GetCount();
		buf.Push("attributes","paroc_list",count);

		buf.Push("count","int",1);
		buf.Pack(&count,1);
		buf.Pop();
		if (count)
		{
			POSITION posk=keys.GetHeadPosition();
			POSITION posv=values.GetHeadPosition();
			while (posk!=NULL)
			{
				POPString &t1=keys.GetNext(posk);
				POPString &t2=values.GetNext(posv);
				buf.Push("element","POPString", 2);

				buf.Push("key", "POPString", 1);
				buf.Pack(&t1,1);
				buf.Pop();

				buf.Push("value", "POPString", 1);
				buf.Pack(&t2,1);
				buf.Pop();

				buf.Pop();//element
			}
		}

		buf.Pop(); // paroc_list
#ifdef OD_DISCONNECT
		getCheckConnection(valInt[0],valInt[1]);
		buf.Push("checkConnection","int",2);
		buf.Pack(valInt,2);
		buf.Pop();
#endif
	}
	else
	{
		buf.Push("power","float",2);
		buf.UnPack(val,2);
		buf.Pop();
		power(val[0],val[1]);


		buf.Push("memory","float",2);
		buf.UnPack(val,2);
		buf.Pop();
		memory(val[0],val[1]);

		buf.Push("bandwidth","float",2);
		buf.UnPack(val,2);
		buf.Pop();
		bandwidth(val[0],val[1]);

		buf.Push("walltime","float",1);
		buf.UnPack(val,1);
		buf.Pop();
		walltime(val[0]);

		buf.Push("manual","int",1);
		buf.UnPack(valInt,1);
		buf.Pop();
		valInt[0]=isManual;

		buf.Push("cwd","POPString",1);
		buf.UnPack(&cwd,1);
		buf.Pop();
		
		//Added by clementval
		buf.Push("search", "int", 3);
		buf.UnPack(valSearch, 3);
		buf.Pop();		
		search(valSearch[0], valSearch[1], valSearch[2]);
		//End of add

		buf.Push("url","POPString",1);
		buf.UnPack(&hostname,1);
		buf.Pop();
		//url(t);

		buf.Push("user","POPString",1);
		buf.UnPack(&hostuser,1);
		buf.Pop();

		buf.Push("core","POPString",1);
		buf.UnPack(&hostcore,1);
		buf.Pop();

		buf.Push("arch","POPString",1);
		buf.UnPack(&hostarch,1);
		buf.Pop();

		buf.Push("batch","POPString",1);
		buf.UnPack(&batchSystem,1);
		buf.Pop();

		buf.Push("joburl","POPString",1);
		buf.UnPack(&t,1);
		buf.Pop();
		joburl(t);

		buf.Push("executable","POPString",1);
		buf.UnPack(&t,1);
		buf.Pop();
		executable(t);

		buf.Push("platforms","POPString",1);
		buf.UnPack(&t,1);
		buf.Pop();
		setPlatforms(t);

		buf.Push("protocol","POPString",1);
		buf.UnPack(&t,1);
		buf.Pop();
		protocol(t);

		buf.Push("encoding","POPString",1);
		buf.UnPack(&t,1);
		buf.Pop();
		encoding(t);

		//Unpack additional attributes
		int count;
		buf.Push("attributes","paroc_list",count);

		buf.Push("count","int",1);
		buf.UnPack(&count,1);
		buf.Pop();
		keys.RemoveAll();
		values.RemoveAll();

		for (int i=0;i<count;i++)
		{
			POPString t1, t2;
			buf.Push("element","POPString", 2);

			buf.Push("key", "POPString", 1);
			buf.UnPack(&t1,1);
			buf.Pop();

			buf.Push("value", "POPString", 1);
			buf.UnPack(&t2,1);
			buf.Pop();

			buf.Pop();//element

			setValue(t1,t2);
		}

		buf.Pop();

#ifdef OD_DISCONNECT
		buf.Push("checkConnection","int",2);
		buf.UnPack(valInt,2);
		buf.Pop();
		checkConnection(valInt[0],valInt[1]);
#endif
	}
}
