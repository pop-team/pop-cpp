#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

#include "paroc_utils.h"
#include "debug.h"

char *paroc_utils::checkremove(int *argc, char ***argv, char *opt)
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

#ifdef _PAROC_ 
#include "paroc_system.h"

bool paroc_utils::SameContact(const char *contact1, const char *contact2)
{
  if (isEqual(contact1,contact2)) return true;
  if (contact1==NULL || contact2==NULL) return false;

  char str1[1024], str2[1024];
  strcpy(str1,contact1);
  strcpy(str2,contact2);

  char *t1, *t2;
  char *s1, *s2;

  t1=strstr(str1,"socket://");
  t2=strstr(str2,"socket://");
  
  s1= (t1!=NULL)? t1+9 : str1;
  s2= (t2!=NULL)? t2+9 : str2;

  t1=strchr(s1,':');
  t2=strchr(s2,':');

  if (t1!=t2)
    {
      if (t1==NULL || t2==NULL) return false;
      int p1, p2;
      if (sscanf(t1+1,"%d",&p1)!=1 || sscanf(t2+1,"%d",&p2)!=1 || p1!=p2) return false;
      *t1=0;
      *t2=0;
    }
  

  int ip1, ip2;

  int n=paroc_system::GetIP(s1,&ip1,1);
  if (n!=1)
    {
      DEBUG("Can not find IP for %s",contact1);
      return false;
    }

  n=paroc_system::GetIP(s2,&ip2,1);
  if (n!=1)
    {
      DEBUG("Can not find IP for %s",contact2);
      return false;
    }

  return (ip1==ip2);
}

paroc_string paroc_utils::MakeContact(const char *host, int port)
{
  if (port<=0) return host;
  char tmpcontact[256];
  sprintf(tmpcontact,"%s:%d",host,port);
  return paroc_string(tmpcontact);
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
      fprintf(stdout,str);
      fflush(stdout);
      return 0;
    }
  try 
    {
      RemoteLog log(paroc_system::appservice);
      paroc_string msg(str);
      log.Log(msg);
    }
  catch (...)
    {
      fprintf(stdout,str);
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



#endif
