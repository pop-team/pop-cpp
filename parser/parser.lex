%{

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "parser.tab.h"
#include "parser.h"
#include "paroc_utils.h"
#include "debug.h"

  int c;
  int linenumber=0;
  char filename[1024];
  int mutexCount=0;

  extern CArrayCharPtr searchpath, sources;
  extern CodeFile *thisCodeFile;

  CArrayChar othercodes(0,32536);
  bool insideClass;
  int startPos=-1;

  /*
#if !defined (YYSTYPE)
#define YYSTYPE long
#endif
  */

  extern YYSTYPE yylval;
  extern char token[];
  extern int yylex(void);

  char tokenbuf[32000];
  char *tokenpos;

  int  PutToken(char *str);
  int PutToken(char chr);
  char *GetToken(int yyval);
  int CountLine(char *str);
  bool IsSystemHeader(char *fname);

  int ReadUntil(char *sep, char *output, int sz);
   
%}

DIGIT [0-9]
LETTER [a-zA-Z]
whitespace [ \a\b\v\f\t\r]+
whitespace1 [ \a\b\v\f\t\r\n]+
whitespace2 [ \a\b\v\f\t\r\n]*
param "("[^")"]*")"

newline [\n]
id [_a-zA-Z][_a-zA-Z0-9]*

%%

{whitespace} {
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
};

"@"{whitespace2}"pack" {
  startPos=othercodes.GetSize();
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return PACK_KEYWORD;
};

^"@"{whitespace2}"parocfile"[ \t]+\"[^\"]*\"[^\n]* {
  char *t1, *t2;
  t1=strchr(yytext,'"');
  if (t1!=NULL)
    {
      t1++;
      t2=strrchr(t1,'"');
      if (t2!=NULL)
	{
	  *t2=0;
	  strcpy(filename,t1);
	  thisCodeFile->SetFileName(filename); 
	  *t2='"';
	}
    }
  //  printf("LINE DIRECTIVE:line:%d in %s\n", linenumber,filename);
};

^"#pragma"[ \t]*"interface"[ \t]*"="[ \t]*{id}[ \t]* {
  char *t=strchr(yytext,'=');
  t++;
  while (isspace(*t)) t++;
  sscanf(t,"%[A-z0-9_]*)",Class::interface_base);

};
^"#pragma"[ \t]*"broker"[ \t]*"="[ \t]*{id}[ \t]* {
  char *t=strchr(yytext,'=');
  t++;
  while (isspace(*t)) t++;
  sscanf(t,"%[A-z0-9_]*)",Class::broker_base);
};

^"#pragma"[ \t]*"object"[ \t]*"="[ \t]*{id}[ \t]* {
  char *t=strchr(yytext,'=');
  t++;
  while (isspace(*t)) t++;
  sscanf(t,"%[A-z0-9_]*)",Class::object_base);
};




^"#"[ \t]*[0-9]+[ \t]*[\n] {
  char *t1, *t2;
  sscanf(yytext+1, "%d", &linenumber);
  linenumber++;
  //  printf("LINE DIRECTIVE:line:%d in %s\n", linenumber,filename);
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
  //  yylval=PutToken(yytext);
  //  return DIRECTIVE;  
};

^"#"[ \t]*[0-9]+[ \t]+\"[^\"]*\"[^\n]* {
  char *t1, *t2;
  sscanf(yytext+1, "%d", &linenumber);
  t1=strchr(yytext,'"');
  if (t1!=NULL)
    {
      t1++;
      t2=strchr(t1,'"');
      if (t2!=NULL)
	{
	  *t2=0;
	  strcpy(filename,t1);
	  if (thisCodeFile->GetFileName()==NULL) thisCodeFile->SetFileName(filename); 
	  *t2='"';
	}
    }
  //  printf("LINE DIRECTIVE:line:%d in %s\n", linenumber,filename);
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
  //  yylval=PutToken(yytext);
  //  return DIRECTIVE;  
};

^"#"[^\n]* {
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  //  yylval=PutToken(yytext);
  //  return DIRECTIVE;  
};

"\""("\\\\"|"\\\""|[^"\""])*"\"" {
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  linenumber+=CountLine(yytext);

  yylval=PutToken(yytext);
  return STRING;

};

"\'"("\\\\"|"\\\'"|[^"\'"])*"\'" {
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  linenumber+=CountLine(yytext);

  yylval=PutToken(yytext);
  return STRING;
};

{id}{whitespace2}"::"{whitespace2}"~"{whitespace2}{id} {
  char clname[256];
  char methname[256];

  int len=0;
  char *tmp=yytext;
  while (!isspace(*tmp) && *tmp!=':') 
    {
      clname[len]=*tmp;
      tmp++;
      len++;
    }
  clname[len]=0;
 if (thisCodeFile->FindClass(clname)!=NULL)
    {
      while (isspace(*tmp) || *tmp==':') tmp++;
      bool constructor=paroc_utils::isEqual(clname,tmp);
      
      char postfix[32]="__parocobj";
      int len=strlen(clname);
      int len1=strlen(postfix);
      othercodes.InsertAt(-1,clname,len);
      othercodes.InsertAt(-1,postfix,len1);
      othercodes.InsertAt(-1,yytext+len,strlen(yytext)-len);
      othercodes.InsertAt(-1,postfix,len1);
    }
  else
    {
      othercodes.InsertAt(-1,yytext,strlen(yytext));
    }
  linenumber+=CountLine(tmp);
};

{id}{whitespace2}("::"{whitespace2}{id})+ {
  char clname[256];
  char methname[256];
  bool shouldreturn=true;
  char newyytext[1024];

  int len=0;
  char *tmp=yytext;
  while (!isspace(*tmp) && *tmp!=':') 
    {
      clname[len]=*tmp;
      tmp++;
      len++;
    }
  clname[len]=0;

  //  printf("Method of class [%s]\n",clname);

  if (thisCodeFile->FindClass(clname)!=NULL)
    {
      while (isspace(*tmp) || *tmp==':') tmp++;
      bool constructor=paroc_utils::isEqual(clname,tmp);
      sprintf(newyytext,"%s__parocobj%s",clname,yytext+len);
      othercodes.InsertAt(-1,newyytext,strlen(newyytext));

      if (constructor)
	{
	  shouldreturn=false;
	  char postfix[]="__parocobj";
	  int len1=strlen(postfix);
	  othercodes.InsertAt(-1,postfix,len1);

	  char buf[10240];
	  int n=ReadUntil(");{", buf, 10240);
	  othercodes.InsertAt(-1,buf,n);
	  linenumber+=CountLine(buf);
	  if (n && buf[n-1]==')')
	  {
	     n=ReadUntil(":;{", buf, 10240);
	     othercodes.InsertAt(-1,buf,n);
	     linenumber+=CountLine(buf);
   	  }
	  if (n && buf[n-1]==':')
	    {
	      while (1)
		{
		  //extract base class name
		  n=ReadUntil("({;",buf,10240);
		  if (!n) break;

		  linenumber+=CountLine(buf);
		  if (buf[n-1]!='(')
		    {
		      fprintf(stderr, "ERROR: %s:%d: Bad base class initialization\n",filename, linenumber);
		      exit(1);
		    }
		  sscanf(buf," %[_a-zA-Z0-9]",clname);

		  if (thisCodeFile->FindClass(clname)!=NULL)
		    {
		      char *t=strstr(buf,clname)+ strlen(clname);
		      othercodes.InsertAt(-1,buf,t-buf);
		      othercodes.InsertAt(-1,postfix,len1);
		      othercodes.InsertAt(-1,t,strlen(t));
		    }
		  else othercodes.InsertAt(-1,buf,n);
		  //Extract parametters...
		  
		  n=ReadUntil("){;",buf,10240);
		  othercodes.InsertAt(-1,buf,n);
		  if (!n || buf[n-1]!=')') break;

		  //Extract separators...
		  n=ReadUntil(",{;",buf,10240);
		  othercodes.InsertAt(-1,buf,n);
		  if (!n || buf[n-1]!=',') break;
		}
	    }
	}
    }
  else
    {
      strcpy(newyytext,yytext);
      othercodes.InsertAt(-1,yytext,strlen(yytext));
    }
  linenumber+=CountLine(tmp);

  if (shouldreturn)
    {
      yylval=PutToken(newyytext);
      return ID;
    }
};


{newline} {
  linenumber++; 
  othercodes.InsertAt(-1,yytext,strlen(yytext));
};

parclass {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      othercodes.InsertAt(-1,yytext,strlen(yytext));
      return ID;
    }

  /*  printf(" class keyword\n");*/
  yylval=PutToken(char(100));
  
  startPos=othercodes.GetSize();
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return PARCLASS_KEYWORD;
};

class {
  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return CLASS_KEYWORD;

};
 
classuid {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      othercodes.InsertAt(-1,yytext,strlen(yytext));
      return ID;
    }

  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
  return CLASSID;
};

auto {
  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return AUTO_KEYWORD;
};

register {
  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return REGISTER_KEYWORD;
}; 


public {
  if (!insideClass) othercodes.InsertAt(-1,yytext,strlen(yytext));
  return PUBLIC_KEYWORD;
};
private {
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return PRIVATE_KEYWORD;
};
protected {
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return PROTECTED_KEYWORD;
};


virtual {
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return VIRTUAL_KEYWORD;
};

const {
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return CONST_KEYWORD;
};

struct {
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return STRUCT_KEYWORD;
};


sync {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      othercodes.InsertAt(-1,yytext,strlen(yytext));
      return ID;
    }
  else
    {
      othercodes.InsertAt(-1,yytext,strlen(yytext));
      return SYNC_INVOKE;
    }
}; 


async {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      othercodes.InsertAt(-1,yytext,strlen(yytext));
      return ID;
    }

  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return ASYNC_INVOKE;
};

in {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      othercodes.InsertAt(-1,yytext,strlen(yytext));
      return ID;
    }

  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return INPUT;
};

out {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      othercodes.InsertAt(-1,yytext,strlen(yytext));
      return ID;
    }

  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return OUTPUT;
};

conc {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      othercodes.InsertAt(-1,yytext,strlen(yytext));
      return ID;
    }

  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return CONCURRENT;
};


seq {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      othercodes.InsertAt(-1,yytext,strlen(yytext));
      return ID;
    }

  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return SEQUENTIAL;
};

mutex[ \a\b\v\f\t\r\n]*"{" {
  if (IsSystemHeader(filename))
    {
      char *yycopy=strdup(yytext+5);
      int len=strlen(yycopy);
      yylval=PutToken("mutex");
      othercodes.InsertAt(-1,yytext,5);
      for (char *t=yycopy+len-1;t!=yycopy;t--) unput(*t); 
      free(yycopy);
      return ID;
      
      //      othercodes.InsertAt(-1,yytext,strlen(yytext));
    }
  else
    {
      char str[256];
      int len=strlen(yytext)-6;
      sprintf(str," { paroc_mutex_locker _paroc_mutex%d(_paroc_omutex); ",mutexCount++); 
      othercodes.InsertAt(-1,str,strlen(str));
      othercodes.InsertAt(-1,yytext+5,len);
    }
  linenumber+=CountLine(yytext+5);
};

mutex {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      othercodes.InsertAt(-1,yytext,strlen(yytext));
      return ID;
    }

  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return MUTEX;

};

"::" {

  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return SCOPE;
};

__hidden {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      othercodes.InsertAt(-1,yytext,strlen(yytext));
      return ID;
    }

  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return HIDDEN;  
};

proc {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      othercodes.InsertAt(-1,yytext,strlen(yytext));
      return ID;
    }

  yylval=PutToken(char(USERPROC));
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return PROC;
};
size {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      othercodes.InsertAt(-1,yytext,strlen(yytext));
      return ID;
    }

  yylval=PutToken(char(PARAMSIZE));
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return SIZE;
};


unsigned{whitespace1}int {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
  return(ID1);
};

signed{whitespace1}int {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
  return(ID1);
};

unsigned{whitespace1}long {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
  return(ID1);
};

signed{whitespace1}long {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
  return(ID1);
};

signed{whitespace1}char {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
  return(ID1);
};

unsigned{whitespace1}char {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
  return(ID1);
};


signed{whitespace1}short {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
  return(ID1);
};

unsigned{whitespace1}short {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
  return(ID1);
};

typedef {
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
  return(TYPEDEF_KEYWORD);
};

{id} {
  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));  
  return(ID);
};

[0-9]+   {
  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return (INTEGER);
};

[0-9]*"."[0-9]+([Ee][0-9]+)? {
  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return (REAL);  
};



"//"[^\n]*   ;
"/*"[^"*/"]*"*/" {
  linenumber+=CountLine(yytext);
} ;

"&&" {
  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return (AND_OP);    
};

"||" {
  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return (OR_OP);    
};

"==" {
  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return (EQUAL_OP);    
};

"!=" {
  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return (NOTEQUAL_OP);    
};

">=" {
  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return (GREATEREQUAL_OP);    
};

"<=" {
  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return (LESSEQUAL_OP);    
};

"?"{whitespace2}":" {
  yylval=PutToken(yytext);
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return (NONSTRICT_OD_OP);    
};


"\'"|"\""|"#"|"("|")"|"{"|"}"|"["|"]"|";"|":"|","|"*"|"&"|"~"|"="|"+"|"%"|"@"|"$"|"^"|"-"|"|"|"`"|"!"  { 
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return yytext[0]; 
};

<<EOF>> {
  return EOFCODE;
};
. {
  othercodes.InsertAt(-1,yytext,strlen(yytext));
  return yytext[0];   
};

%%

int yylex();

int PutToken(char *str)
{
  assert(str!=NULL);
  int len=strlen(str)+1;
  if (tokenpos<tokenbuf || tokenpos+len>=tokenbuf+10000) tokenpos=tokenbuf;
  strcpy(tokenpos,str);
  int ret=tokenpos-tokenbuf;
  tokenpos+=len;
  return ret;
}


int PutToken(char chr)
{
  int len=2;
  if (tokenpos<tokenbuf || tokenpos+len>=tokenbuf+10000) tokenpos=tokenbuf;
  int ret=tokenpos-tokenbuf;

  tokenpos[0]=chr;
  tokenpos[1]=0;
  tokenpos+=2;
  return ret;
}


char *GetToken(int yyval)
{
  assert(yyval>=0 && yyval<10000);
  return (tokenbuf+yyval);
}


int CountLine(char *str)
{
  if (str==NULL) return 0;
  int n=0;
  for (;*str!=0;str++) if (*str=='\n') n++;
  return n;
}

int ReadUntil(char *sep, char *buf, int sz)
{
  if (sz<=1)
    {
      printf("Buffer size (%d) error\n", sz);
      if (sz==1) *buf=0;
      return 0;
    }
 
  char *tmp=buf;
  int ch=1;
  int bracket=0;

  while (strchr(sep,ch)==NULL && ch!=EOF)
    {
      ch=yyinput();
      *tmp=ch;
      tmp++;
      sz--;
      if (sz<=1)
	{
	  *tmp=0;
	  return (tmp-buf);
	}
      if (ch=='"')
	{
	  int n;
	  while ((n=ReadUntil("\"", tmp,sz))>0 && tmp[n-2]=='\\');
	}
      else if (ch=='\'')
	{
	  int n;
	  while ((n=ReadUntil("\'", tmp,sz))>0 && tmp[n-2]=='\\');
	}
      else if (ch=='(') bracket++;
      else if (ch==')')
	{
	  bracket--;
	  if (bracket>0) ch=1;
	}
    }
  
  *tmp=0;
  return (tmp-buf);
}


bool IsSystemHeader(char *fname)
{
  char system_header[]="/usr/include";
  if (fname==NULL) return false;
  int len=strlen(fname);

  //  return strcmp(fname+len-2,".h")==0;

  return strncmp(fname,system_header,strlen(system_header))==0;
}

