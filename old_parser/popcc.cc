#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "config.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "paroc_utils.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef POPC_BUILD_ARCH
char arch[256]= "i686-pc-Linux";
#else
char arch[256]= POPC_BUILD_ARCH;
#endif

#ifndef SVNREV 
#define SVNREV "(unknown)"
#endif

void Usage()
{
  fprintf(stderr,"\nPOP-C++ version %s %s on %s\n", VERSION, SVNREV, arch);
  fprintf(stderr,"\npopcc [-cxxmain] [-object[=type]] [-cpp=<C++ preprocessor>] [-cxx=<compiler>] ] [-parocld=linker] [-parocdir=<path>] [-popcpp=<POP-C++ parser>] [-verbose] [-noclean] [other C++ options] sources...\n");

  fprintf(stderr,"   -cxxmain:              Use standard C++ main (ignore POP-C++ initialization)\n");
  fprintf(stderr,"   -paroc-static:         Link with standard POP-C++ libraries statically\n");
  fprintf(stderr,"   -paroc-nolib:          Avoid standard POP-C++ libraries from linking\n");
  fprintf(stderr,"   -parclass-nointerface: Do not generate POP-C++ interface codes for parallel objects\n");
  fprintf(stderr,"   -parclass-nobroker:    Do not generate POP-C++ broker codes for parallel objects\n");

 fprintf(stderr,"\n   -object[=type]:      Generate parallel object executable (linking only) (type: std (default) or mpi)\n");
  fprintf(stderr,"   -popcpp:            POP-C++ parser\n");
  fprintf(stderr,"   -cpp=<preprocessor>: C++ preprocessor command\n");
  fprintf(stderr,"   -cxx=<compiler>:     C++ compiler\n");
  fprintf(stderr,"   -parocld=<linker>:   C++ linker (default: same as C++ compiler)\n");
  fprintf(stderr,"   -parocdir:           POP-C++ installed directory\n");
  fprintf(stderr,"   -noclean:            Do not clean temporary files\n");
  fprintf(stderr,"   -verbose:            Print out additional information\n");

  fprintf(stderr,"\nEnvironment variables change the default values used by POP-C++:\n");
  fprintf(stderr,"   POPC_LOCATION:  Directory where POP-C++ has been installed\n");
  fprintf(stderr,"   POPC_CXX:       The C++ compiler used to generate object code\n");
  fprintf(stderr,"   POPC_CPP:       The C++ preprocessor\n");
  fprintf(stderr,"   POPC_LD:        The C++ linker used to generate binary code\n");
  fprintf(stderr,"   POPC_PP:        The POP-C++  parser\n");

  exit(1);
}

bool verbose=false;
bool noclean=false;

void Verbose(int argc, char *argv[])
{
  printf("\nEXEC:");
  for (int i=0;i<argc;i++) printf("%s ", argv[i]);
  printf("\n");
}

int RunCmd(int argc, char *argv[])
{
  argv[argc]=0;
  if (verbose) Verbose(argc,argv);

  int status;
  int pid=vfork();
  if (pid<0)
    {
      perror("ERROR");
      _exit(1);
    }
  else if (pid==0)
    {
      execvp(argv[0],argv);
      fprintf(stderr,"ERROR: %s not found\n",argv[0]);
      _exit(1);
    }
  wait(&status);
  int ret=WEXITSTATUS(status);
  return ret;
}

int RunPipe(int argc1, char *argv1[], int argc2, char *argv2[])
{
  argv1[argc1]=0;
  argv2[argc2]=0;

  if (verbose)
  {	
	 Verbose(argc1,argv1);
	 Verbose(argc2,argv2);
  }

  int p[2]; 
  if (pipe(p)!=0) 
  {
	perror("Error");
	_exit(1);
  }

  int status;
  int pid1=fork();
  if (pid1<0)
    {
      perror("ERROR");
      _exit(1);
    }
  else if (pid1==0)
    {
	close(p[0]);
	dup2(p[1],1);
     	execvp(argv1[0],argv1);
      	fprintf(stderr,"ERROR: %s not found\n",argv1[0]);
      _exit(1);
    }

  int pid2=fork();
  if (pid2<0)
  {
  	perror("ERROR");
  	_exit(1);
  }

  if (pid2==0)
  {
	close(p[1]);
	dup2(p[0],0);
   	execvp(argv2[0],argv2);
      	fprintf(stderr,"ERROR: %s not found\n",argv2[0]);
     	_exit(1);		
  }
  close(p[0]);
  close(p[1]);

  wait(&status);
  int ret=WEXITSTATUS(status);
  if (ret!=0) return ret;

  wait(&status);
  ret=WEXITSTATUS(status);
  return ret;
}


void PrepareSource(char *src, char *dest)
{
  FILE *sf=fopen(src,"r+t");
  if (sf==NULL)
    {
      perror(src);
      exit(1);
    }
  FILE *df=fopen(dest,"w+t");
  if (df==NULL)
    {
      perror("Temporary file:");
      exit(1);
    }
  char buf[1024];
  fprintf(df,"\n# 1 \"<paroc system>\"\n#define _POPC_\n#include \"paroc_sys.h\"\n@parocfile \"%s\"\n# 1 \"%s\"\n",src,src);
  buf[1023]=0;
  while (fgets(buf,1023,sf)!=NULL)
    {
      if (fputs(buf,df)==EOF)
	{
	  perror("Writing temporary file");
	  exit(1);
	}
    }
  fputs("\n",df);
  fclose(df);
  fclose(sf);
}

char *Compile(char *preprocessor, char *popcpp, char *cpp, char *pre_opt[], char *cpp_opt[], char *source, char *dest, bool usepipe, bool client, bool broker)
{
  char *cmd[1000];
  int count=0;
  char *cmd1[1000];
  int count1=0;

  char sdir[1024];
  char tmpfile1[1024];
  char tmpfile2[1024];
  char tmpfile3[1024];

  char output_opt[]="-o";
  char compile_opt[]="-c";
  char noclient[]="-parclass-nointerface";
  char nobroker[]="-parclass-nobroker";

  bool paroc=false;
  static char output[1024];
  int ret=0;
  
  char *fname=strrchr(source,'/');
  if (fname!=NULL)
    {
      fname++;
      int n=fname-source+1;
      strncpy(sdir,source,n);
      sdir[n]=0;
    }
  else
    { fname=source;
      *sdir=0;
    }
  char *str=strrchr(fname,'.');
  if (str==NULL) return NULL;

  bool paroc_extension= (strcmp(str,".ph")==0 || strcmp(str,".pc")==0);
  if (paroc_extension || strcmp(str,".cc")==0 ||  strcmp(str,".C")==0 || strcmp(str,".cpp")==0) 
    {
      sprintf(tmpfile1,"%s_paroc1_%s", sdir,fname);
      if (usepipe) sprintf(tmpfile2,"-"); else sprintf(tmpfile2,"%s_paroc2_%s", sdir,fname);
      sprintf(tmpfile3,"%s_paroc3_%s", sdir,fname);
      if (paroc_extension)
	{
	  strcat(tmpfile1 ,".cc");
	  strcat(tmpfile2 ,".cc");
	  strcat(tmpfile3 ,".cc");
	}
      
      
      PrepareSource(source,tmpfile1);
      
      //Run C++ preprocessor... 
      cmd[0]=preprocessor;
      char **t1=cmd+1;
      count=1;
      for (char **t2=pre_opt; *t2!=NULL; t2++, t1++)
	{
	  *t1=*t2;
	  count++;
	}
      *t1=tmpfile1; t1++; count++;

//Preprocessor output...
      if (!usepipe)
	{ 
      	    if (*output_opt!=0) 
		{
		  *t1=output_opt;
		  t1++; count++;
		}
   	   *t1=tmpfile2; t1++; count++;
  	    RunCmd(count, cmd);
        }
      
      //Run POP-C++ preprocessor...
      
      cmd1[0]=popcpp;
      cmd1[1]=tmpfile2;
      cmd1[2]=tmpfile3;
      int countparoc=3;
      if (!client) cmd1[countparoc++]=noclient;
      if (!broker) cmd1[countparoc++]=nobroker;

      if (!usepipe)
	{
  	    ret=RunCmd(countparoc, cmd1);
   	    if (!noclean) unlink(tmpfile2);
	}
      else
	{
	  ret=RunPipe(count,cmd,countparoc,cmd1);
	}
      paroc=true;
    }

   if (!noclean) unlink(tmpfile1);

  //Run C++ compiler...
  
  cmd[0]=cpp;
  char **t1=cmd+1;
  count=1;
  for (char **t2=cpp_opt; *t2!=NULL; t2++, t1++)
    {
      *t1=*t2;
      count++;
    }

  *t1=compile_opt; t1++; count++;

  *t1=(paroc) ? tmpfile3 : source; t1++; count++;
  *t1=output_opt; t1++; count++;
  if (dest==NULL)
    {
      strcpy(output,source);
      str=strrchr(output,'.');
      if (strcmp(str,".ph")==0) strcpy(str,".stub.o");
      else strcpy(str,".o");
      dest=output;
      *t1=output;
    }
  else *t1=dest;
  t1++; count++;

  if (ret==0) ret=RunCmd(count, cmd);
  
  if (!noclean && paroc) unlink(tmpfile3);

  if (ret!=0)
  {
	_exit(ret);
  }

  return dest;
}

bool FindLib(char *libpaths[1024], int count, const char *libname,char libfile[1024])
{
	for (int i=0;i<count;i++)
	{
		sprintf(libfile,"%s/lib%s.a", libpaths[i], libname);
		if (access(libfile,F_OK)==0) return true;
	}
	return false;
}

int main(int argc, char *argv[])
{
  if (argc<=1) Usage();

  char popcpp[1024];
#ifndef POPC_CXX
  char parocxx[1024]="g++";
  char parocld[1024]="g++";
#else
  char parocxx[1024]=POPC_CXX;
  char parocld[1024]=POPC_CXX;
#endif
#ifndef POPC_CPP
  char cpp[1024]="g++ -E";
#else
  char cpp[1024]=POPC_CPP;
#endif
  char opt_compile[]="-c";
  char opt_output[]="-o";
  
  char parocdir[1024]="/home/clementval/popc";
  char includedir[1024];

  char libdir[1024];

  char *link_cmd[1024];

  int link_count=0;

  char *libpaths[1024];
  int libpaths_count=0;
	

  char *cpp_opts[1000];
  int cpp_count;
  
  char *cxx_opts[1000];
  int cxx_count;

  char buf[256];

  char outputfile[1024]="";

  bool useparocmain=true;
  bool compile=false;
  bool drun=false;
  bool object=false;
  bool paroc_static=false;
  bool paroc_nolib=false;
  bool broker=true;
  bool client=true;
  bool staticlib=false;

  char objmain[256]="std";


  char *tmp;
  //Check for POP-C++ installed dir...
  if ((tmp=paroc_utils::checkremove(&argc,&argv,"-parocdir="))!=NULL) strcpy(parocdir,tmp);
  else if ((tmp=getenv("POPC_LOCATION"))!=NULL) strcpy(parocdir,tmp);

  paroc_static=(paroc_utils::checkremove(&argc,&argv,"-paroc-static")!=NULL);
  paroc_nolib=(paroc_utils::checkremove(&argc,&argv,"-paroc-nolib")!=NULL);

  if ((tmp=paroc_utils::checkremove(&argc,&argv,"-popcpp="))!=NULL) strcpy(popcpp,tmp);
  else if ((tmp=getenv("POPC_PP"))!=NULL) strcpy(popcpp,tmp);
  else sprintf(popcpp,"%s/bin/popcpp",parocdir);

  if (access(popcpp, X_OK)!=0)
    {
      int code=errno;
      perror(popcpp); 
      Usage();
    }

  if ((tmp=paroc_utils::checkremove(&argc,&argv,"-cpp="))!=NULL) strcpy(cpp,tmp);
  else if ((tmp=getenv("POPC_CPP"))!=NULL) strcpy(cpp,tmp);

  if ((tmp=paroc_utils::checkremove(&argc,&argv,"-cxx="))!=NULL) strcpy(parocxx,tmp);
  else if ((tmp=getenv("POPC_CXX"))!=NULL) strcpy(parocxx,tmp);

  if ((tmp=paroc_utils::checkremove(&argc,&argv,"-parocld="))!=NULL) strcpy(parocld,tmp);
  else if ((tmp=getenv("POPC_LD"))!=NULL) strcpy(parocld,tmp);
  else strcpy(parocld, parocxx);

 //Check for POP-C++ options...  
  noclean=(paroc_utils::checkremove(&argc,&argv,"-noclean")!=NULL);

  broker=(paroc_utils::checkremove(&argc,&argv,"-parclass-nobroker")==NULL);
  client=(paroc_utils::checkremove(&argc,&argv,"-parclass-nointerface")==NULL);

  cpp_count=0;
  char *tok=strtok(cpp," \t");
  while ((tok=strtok(NULL," \t"))!=NULL) cpp_opts[cpp_count++]=tok;

  cxx_count=0;
  tok=strtok(parocxx," \t");
  while ((tok=strtok(NULL," \t"))!=NULL) cxx_opts[cxx_count++]=tok;

  link_cmd[0]=parocld;
  link_count=1;
  tok=strtok(parocld," \t");
  while ((tok=strtok(NULL," \t"))!=NULL) link_cmd[link_count++]=tok;

  sprintf(buf,"-L%s/lib",parocdir);
  link_cmd[link_count]=strdup(buf);
  link_count++;

  char paroclibdir[1024];
  sprintf(paroclibdir,"%s/lib",parocdir);
  libpaths[libpaths_count++]=paroclibdir;
  
	
#ifdef POPC_EXTRA_LINK
  link_cmd[link_count++]=strdup(POPC_EXTRA_LINK);	
#endif

  for (int i=1;i<argc;i++)
    {
      if (strcmp(argv[i],"-c")==0) 
	{
	  argv[i][0]=0;
	  compile=true;
	}
      else if (strcmp(argv[i],"-o")==0)
	{
	  if (i==argc-1)
	    {
	      fprintf(stderr,"Error: option -o is used but no output file is specified\n");
	      exit(1);
	    }
	  if (*outputfile!=0)
	    {
	      fprintf(stderr,"Error: multiple output files specified\n");
	      exit(1);
	    }
	  argv[i][0]=0;
	  strcpy(outputfile,argv[i+1]);
	  i++;
	  argv[i][0]=0;
	}
      else if (strcmp(argv[i],"-object")==0)
	{
	  argv[i][0]=0;
	  object=true;
	}
      else if (strncmp(argv[i],"-object=",8)==0)
	{
	  if (argv[i][8]!=0) strcpy(objmain, argv[i]+8);
	  argv[i][0]=0;
	  object=true;
	}
      else if (strcmp(argv[i],"-cxxmain")==0)
	{
	  argv[i][0]=0;
	  useparocmain=false;
	}  
     else if (strcmp(argv[i],"-verbose")==0)
	{
	  argv[i][0]=0;
	  verbose=true;
	}  
      else if (strncmp(argv[i],"-I",2)==0)
	{
	  cpp_opts[cpp_count++]=argv[i];
	}
      else if (strcmp(argv[i],"-shared")==0)
	{
	  staticlib=false;
	}
      else if (strncmp(argv[i],"-L",2)==0)
	{
	  libpaths[libpaths_count++]=argv[i]+2;	
	}

      else if (strncmp(argv[i],"-D",2)==0 || strncmp(argv[i],"-U",2)==0 )
	{
	  cpp_opts[cpp_count++]=argv[i];
	  cxx_opts[cxx_count++]=argv[i];
	}

       else if (argv[i][0]=='-' && argv[i][1]!='L' && argv[i][1]!='l')
	{
	  cxx_opts[cxx_count++]=argv[i];
	}
	
    }

   libpaths[libpaths_count++]="/usr/lib";
   libpaths[libpaths_count++]="/lib";


    sprintf(buf,"-DPOPC_ARCH=\"%s\"",arch);
    cpp_opts[cpp_count++]=strdup(buf);

  if (useparocmain)
    {
      cpp_opts[cpp_count++]=strdup("-Dmain=parocmain");
    }

  sprintf(buf,"-I%s/include",parocdir);
  cpp_opts[cpp_count++]=strdup(buf);

  if (*outputfile!=0)
    {
      link_cmd[link_count++]=strdup("-o");
      link_cmd[link_count++]=outputfile;
    }

  cxx_opts[cxx_count++]=strdup("-Dparclass=class");

  cpp_opts[cpp_count]=NULL;
  cxx_opts[cxx_count]=NULL;


  for (int i=1;i<argc;i++) if (argv[i][0]!=0)
    {
      if (argv[i][0]!='-')
	{
	  char *str=strrchr(argv[i],'.');
	  if (str!=NULL)
	    {
	      bool paroc_extension= (strcmp(str,".ph")==0 || strcmp(str,".pc")==0);
	      if (paroc_extension || strcmp(str,".cc")==0 ||  strcmp(str,".C")==0 || strcmp(str,".cpp")==0)
		{

		  char *outf=Compile(cpp, popcpp, parocxx, cpp_opts, cxx_opts, argv[i], ((*outputfile==0 || (!compile) ) ? NULL:  outputfile), true, client, broker);

		  link_cmd[link_count++]=(outf==NULL)? argv[i]: strdup(outf);
		  continue;
		} 
	    }
	}

      if (staticlib && strncmp(argv[i],"-l",2)==0)
	{
  	   char libfile[1024];
	   if (FindLib(libpaths, libpaths_count, argv[i]+2,libfile))
	     {
		link_cmd[link_count++]=strdup(libfile);
		continue;
	     }
	   
	}
      link_cmd[link_count++]=argv[i];
    }

  if (!compile)
    {
      if (!paroc_nolib)
	{
          if (useparocmain)
	   {
  	      if (object)
 	        sprintf(buf, "%s/lib/paroc_objmain.%s.o",parocdir,objmain); 
 	      else
 	        sprintf(buf, "%s/lib/paroc_infmain.std.o",parocdir); 
	    link_cmd[link_count++] = strdup(buf);
	   }
          if (paroc_static || staticlib) sprintf(buf, "%s/lib/libparoc_common.a",parocdir); else strcpy(buf,"-lparoc_common");
          link_cmd[link_count++]=strdup(buf);


	char tmplibfile[1024];

#ifdef HAVE_LIBNSL
       link_cmd[link_count++]= (staticlib && FindLib(libpaths, libpaths_count,"nsl", tmplibfile))? strdup(tmplibfile) : strdup("-lnsl");
#endif
  
#ifdef HAVE_LIBSOCKET
       link_cmd[link_count++]=(staticlib && FindLib(libpaths, libpaths_count,"socket", tmplibfile))? strdup(tmplibfile) : strdup("-lsocket");
#endif
  
#ifdef HAVE_LIBPTHREAD
       link_cmd[link_count++]=(staticlib && FindLib(libpaths, libpaths_count,"pthread", tmplibfile))? strdup(tmplibfile) : strdup("-lpthread");
#endif

#ifdef HAVE_LIBDL
       link_cmd[link_count++]=(staticlib && FindLib(libpaths, libpaths_count,"dl", tmplibfile))? strdup(tmplibfile) : strdup("-ldl");
#endif
     }
     link_cmd[link_count]=NULL;
     RunCmd(link_count, link_cmd);
  }
  return 0;
}
