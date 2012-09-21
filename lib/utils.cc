/**
 * File : utils.cc
 * Author : Tuan Anh Nguyen
 * Description : commonly used stuffs
 * Creation date : 2010/04/19
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval  10/22/2010  Add IsremoteDest() method.
 * clementval  10/24/2010  Add GetCurrentUser(), GetIPFromURL() and GetPortFromURL() methods.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>



#include "paroc_utils.h"
#include "debug.h"

char *paroc_utils::checkremove(int *argc, char ***argv, const char *opt)
{
	int i=0;
	int n=strlen(opt);
	char* ret=0;
	while (i<*argc)
	{
		if (strncmp((*argv)[i],opt,n)==0)
		{
			ret=(*argv)[i]+n;
			for (int j=i;j<*argc-1;j++) (*argv)[j]=(*argv)[j+1];
			(*argc)--;
		} else i++;
	}
	return ret;
}

bool paroc_utils::isEqual(const char *s1, const char *s2)
{
	if (s1==s2)  return true;
	if (s1==NULL || s2==NULL) return false;
	while (*s1!=0 && *s2!=0)
	{
		if (*s1!=*s2) return false;
		s1++;
		s2++;
	}
	return (*s1==*s2);
}

bool paroc_utils::isncaseEqual(const char *s1, const char *s2)
{
	if (s1==s2)  return true;
	if (s1==NULL || s2==NULL) return false;
	while (*s1!=0 && *s2!=0)
	{
		char ch1=*s1;
		char ch2=*s2;
		if (ch1>='a' && ch1<='z') ch1-=32;
		if (ch2>='a' && ch2 <='z') ch2-=32;
		if (ch1!=ch2) return false;
		s1++;
		s2++;
	}
	return (*s1==*s2);
}

bool paroc_utils::MatchWildcard(const char *str, const char *wildcard)
{
	if (str==wildcard) return true;
	if (str==NULL || wildcard==NULL) return false;
	while (*str!=0 && (*str==*wildcard || *wildcard=='?'))
	{
		if (*wildcard=='*') break;
		str++;
		wildcard++;
	}

	if (*wildcard==0) return (*str==0);
	if (*wildcard!='*') return false;

	while (*wildcard=='*') wildcard++;
	if (*wildcard==0) return true;

	const char *t=str;

	while (*t!=0)
	{
		if (*t==*wildcard || *wildcard=='?')
		{
			if (MatchWildcard(t+1,wildcard+1)) return true;
		}
		t++;
	}
	return false;

}

void paroc_utils::FindAbsolutePath(const char *fname, char *abspath)
{
	if (*fname=='/')
	{
		strcpy(abspath,fname);
		return;
	}

	char *t=(char*)strrchr(fname,'/');
	char dir[1024];

	if (t==NULL)
	{
		if (getcwd(dir,1024)==NULL) *dir=0;
		sprintf(abspath,"%s/%s",dir,fname);
		return;
	}
	char olddir[1024];
   char *trsh;
   trsh=getcwd(olddir,1024);
	*t=0;
   int ret;
	ret=chdir(fname);
	*t='/';
	if (getcwd(dir,1024)==NULL) *dir=0;
	ret=chdir(olddir);
	sprintf(abspath,"%s/%s",dir,t+1);
}



#ifdef _POPC_
#include "paroc_system.h"

bool paroc_utils::SameContact(const char *contact1, const char *contact2)
{
	if (contact1==contact2) return true;
	if (contact1==NULL || contact2==NULL) return false;
	if (strstr(contact1, contact2)!=NULL || strstr(contact2, contact1)!=NULL) return true;

	POPString str2(contact2);
	char *token, *ptr;

	token=strtok_r(str2.GetString()," \n\r\t",&ptr);
	while (token!=NULL)
	{
		if (strstr(contact1,token)!=NULL) return true;
		token=strtok_r(NULL," \n\r\t",&ptr);
	}
	return false;
}

//Return true if the destination is remote
bool paroc_utils::IsRemoteDest(const char *dest)
{
   std::string destination(dest);

   //Get local ip and hostame   
   POPString ip = paroc_system::GetIP();
   
   char host[256];
   gethostname(host, 256);

   //Three string to test with
   std::string _local("127.0.0.1");   
   std::string _ip(ip.GetString());
   std::string _host(host); 

  
   size_t c1, c2, c3;
   c1=destination.find(_local);
   c2=destination.find(_ip);
   c3=destination.find(_host);
   //If one of the 3 strings above is find in the destination, this is a local destination
   if(c1==std::string::npos && c2==std::string::npos && c3==std::string::npos){
      return true;
   }
	return false;
}



//Get the port defined in a URL
int paroc_utils::GetPortFromURL(const char *url){
   std::string surl(url);
   size_t pos;
   pos=surl.rfind(":");
   std::string port=surl.substr(pos+1, std::string::npos);   
   int p = atoi(port.c_str());
   return p;
}

//Get the IP address defined in a URL
const char* paroc_utils::GetIPFromURL(const char *url){
   std::string surl(url);
   size_t pos1, pos2;
   pos1=surl.find("://");
   pos2=surl.rfind(":");
   std::string ip;
   if(pos1!=std::string::npos)
      ip=surl.substr(pos1+3, pos2-pos1-3);   
   else 
      ip=surl.substr(0, pos2);
   return ip.c_str();
}

//Get the current user
const char* paroc_utils::GetCurrentUser(){
  /* int BUF_SIZE=20;  //TODO set as constant
   char buf[BUF_SIZE];
   std::ostringstream cmd;
   std::ostringstream res;
   res.str("");
   res.clear();
   cmd.str("");
   cmd.clear();
   cmd << "whoami";
   FILE *fp;
   fp=popen(cmd.str().c_str(), "r");
   if(fp!=NULL){
      if(fgets(buf, BUF_SIZE, fp) != NULL)
         res << buf;
      return res.str().c_str();
   }*/
   char *username;
   username = getlogin();
   return username;  
}

POPString paroc_utils::MakeContact(const char *host, int port)
{
	if (port<=0) return host;
	char tmpcontact[256];
	sprintf(tmpcontact,"%s:%d",host,port);
	return POPString(tmpcontact);
}


#include "appservice.ph"
int rprintf(const char *format,...)
{
	char str[1024];

	va_list ap;
	va_start(ap, format);
	vsnprintf(str,1023, format, ap);
	va_end(ap);
	if (paroc_system::appservice.IsEmpty())
	{
		fprintf(stdout,"%s",str);
		fflush(stdout);
		return 0;
	}
	try
	{
		RemoteLog log(paroc_system::appservice);
		POPString msg(str);
		log.Log(msg);
	}
	catch (...)
	{
		fprintf(stdout,"%s",str);
		fflush(stdout);
		return 0;
	}
	return 1;
}

int paroc_utils::InitCodeService(char *fileconf, AppCoreService *s)
{
	if (s==NULL || fileconf==NULL) return 0;

	FILE *f=fopen(fileconf,"r");
	char objname[256],arch[256], codefile[256];
	char line[256];
	char sep[]=" \n\t";

	if (f==NULL) return 0;
	try
	{
		while (!feof(f))
		{
			if (fgets(line,256,f)!=NULL)
			{

				int last=strlen(line)-1;
				while (last>=0 && isspace(line[last]))
				{
					line[last]=0;
					last--;
				}
				if (last==0) continue;

				char *tmp=strtok(line,sep);
				if (tmp==NULL) continue;
				strcpy(objname,tmp);
				tmp=strtok(NULL,sep);
				if (tmp==NULL) continue;
				strcpy(arch,tmp);
				tmp+=strlen(tmp)+1;
				if (*tmp==0) continue;
				strcpy(codefile,tmp);

				s->RegisterCode(objname,arch,codefile);
			}
		}
	}
	catch (...)
	{
		fclose(f);
		return 0;
	}
	fclose(f);
	return 1;
}

/**
 * ViSaG : clementval
 * Check if the given string is a IP v4 address
 * @param
 *
 */
bool paroc_utils::isIPv4Address(POPString value){
   std::string ip(value.GetString());

   //check max size
   if(ip.size() > 15)
      return false;

   //check if the IP address has three dots
   size_t dot1, dot2, dot3;
   dot1 = ip.find(".");
   dot2 = ip.find(".", dot1+1);
   dot3 = ip.find(".", dot2+1);

   if(dot1 == std::string::npos || dot2 == std::string::npos || dot3 == std::string::npos){
      return false;
   }

   //check if char are number
   for(size_t i=0; i<ip.length();i++){
      char c = ip.at(i);
      if((c != '.') && !isdigit(c))
         return false;
   }
   
   
   return true;
}

/**
 * ViSaG : clementval
 * Check is a value is only letter and number
 * @param
 * @retrun
 */

bool paroc_utils::isValidName(POPString value){
   std::string checked(value.GetString());
   for(size_t i=0; i<checked.length();i++){
      char c = checked.at(i);
      if((c != '_') && !isdigit(c) && !isalpha(c))
         return false;
   }
   return true;
}


#endif
