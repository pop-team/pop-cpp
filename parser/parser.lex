%{

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "parser.tab.h"
#include "parser.h"
#include "paroc_utils.h"

  int c;
  int linenumber=0;
  char filename[1024];
  char classname[1024];
  int mutexCount=0;
  int dummyCount=0;

  extern CArrayCharPtr searchpath, sources;
  extern CodeFile *thisCodeFile;

  CArrayChar othercodes;
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
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
};

"@"{whitespace2}"pack" {
  startPos=othercodes.size();
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return PACK_KEYWORD;
};

^"@"{whitespace2}"parocfile"[ \t]+\"[^\"]*\"[^\n]* {
  char *t1, *t2;
  t1 = strchr(yytext,'"');
  if (t1!=NULL) {
    t1++;
    t2=strrchr(t1,'"');
    if (t2!=NULL) {
      *t2=0;
      strcpy(filename, t1);
      thisCodeFile->SetFileName(filename);
      *t2='"';
    }
  }
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
  //char *t1, *t2;
  sscanf(yytext+1, "%d", &linenumber);
  linenumber++;
  //  printf("LINE DIRECTIVE:line:%d in %s\n", linenumber,filename);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  //  yylval=PutToken(yytext);
  //  return DIRECTIVE;
};

^"#line"[ \t]*[0-9]+[ \t]+\"[^\"]*\"[^\n]* {
  char *t1, *t2;
  sscanf(yytext+1, "%d", &linenumber);
  t1=strchr(yytext,'"');
  if (t1 != NULL) {
    t1++;
    t2 = strchr(t1,'"');
    if (t2 != NULL) {
      *t2=0;
      strcpy(filename,t1);
      if (thisCodeFile->GetFileName()==NULL) {
        thisCodeFile->SetFileName(filename);
      }
      *t2='"';
    }
  }
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
};

^"#"[ \t]*[0-9]+[ \t]+\"[^\"]*\"[^\n]* {
  char *t1, *t2;
  sscanf(yytext+1, "%d", &linenumber);
  t1 = strchr(yytext,'"');
  if (t1 != NULL) {
    t1++;
    t2 = strchr(t1,'"');
    if (t2 != NULL) {
      *t2=0;
      strcpy(filename,t1);
      if (thisCodeFile->GetFileName()==NULL) {
        thisCodeFile->SetFileName(filename);
      }
      *t2='"';
    }
  }
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
};



^"#"[^\n]* {
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  //  yylval=PutToken(yytext);
  //  return DIRECTIVE;
};

"\""("\\\\"|"\\\""|[^"\""])*"\"" {
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  linenumber+=CountLine(yytext);

  yylval=PutToken(yytext);
  return STRING;

};

"\'"("\\\\"|"\\\'"|[^"\'"])*"\'" {
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  linenumber+=CountLine(yytext);

  yylval=PutToken(yytext);
  return STRING;
};


{id}{whitespace2}"::"{whitespace2}"~"{whitespace2}{id} {
  char clname[256];
  //char methname[256];

  int len=0;
  char *tmp=yytext;
  while (!isspace(*tmp) && *tmp!=':')
    {
      clname[len]=*tmp;
      classname[len]=*tmp;
      tmp++;
      len++;
    }
  clname[len]=0;
  classname[len]=0;

  if (thisCodeFile->FindClass(clname) != NULL) {
    while (isspace(*tmp) || *tmp==':') tmp++;
    //bool constructor=paroc_utils::isEqual(clname,tmp);

      char postfix[32]="_popcobject";
      int len=strlen(clname);
      int len1=strlen(postfix);
      std::copy(clname, clname+len, std::back_inserter(othercodes));
      std::copy(postfix, postfix+len1, std::back_inserter(othercodes));
      std::copy(yytext+len, yytext+strlen(yytext), std::back_inserter(othercodes));
      std::copy(postfix, postfix+len1, std::back_inserter(othercodes));
    } else {
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
    }
    linenumber+=CountLine(tmp);
};

{id}{whitespace2}("::"{whitespace2}{id})+ {
  char clname[256];
  bool shouldreturn = true;
  char newyytext[1024];
  char thisBuf[1024];
  int len = 0;
  char *tmp = yytext;

  while (!isspace(*tmp) && *tmp!=':') {
    clname[len]=*tmp;
    classname[len]=*tmp;
    tmp++;
    len++;
  }
  clname[len] = 0;
  classname[len] = 0;

  if (thisCodeFile->FindClass(clname) != NULL) {
    while (isspace(*tmp) || *tmp == ':') {
      tmp++;
    }
    bool constructor = paroc_utils::isEqual(clname,tmp);
    sprintf(newyytext,"%s_popcobject%s", clname, yytext+len);
    std::copy(newyytext, newyytext+strlen(newyytext), std::back_inserter(othercodes));
    Class *cl = thisCodeFile->FindClass(clname);
    if(!cl->is_collective()){
      //Create the string to be inserted in every paroc_object constructor
      sprintf(thisBuf, "__POPThis_%s=new %s(GetAccessPointForThis());", clname, clname);
    }


  if (constructor) {
	  shouldreturn = false;
	  char postfix[] = "_popcobject";
	  int len1 = strlen(postfix);
	  std::copy(postfix, postfix+len1, std::back_inserter(othercodes));

	  char buf[10240];
	  int n = ReadUntil((char*)");{", buf, 10240);
	  std::copy(buf, buf+n, std::back_inserter(othercodes));

	  linenumber+=CountLine(buf);
	  if (n && buf[n-1]==')'){
      n=ReadUntil((char*)":;{", buf, 10240);
	    std::copy(buf, buf+n, std::back_inserter(othercodes));
	    linenumber+=CountLine(buf);
    }
	  if (n && buf[n-1]==':') {
      while (1) {
  		  //extract base class name
	  	  n=ReadUntil((char*)"({;",buf,10240);
		    if (!n) break;

		    linenumber+=CountLine(buf);
  		  if (buf[n-1]!='(') {
		      fprintf(stderr, "ERROR: %s:%d: Bad base class initialization\n",filename, linenumber);
		      exit(1);
		    }
  		  sscanf(buf," %[_a-zA-Z0-9]",clname);

	  	  if (thisCodeFile->FindClass(clname)!=NULL) {
		      char *t=strstr(buf,clname)+ strlen(clname);
		      std::copy(buf, buf + (t-buf), std::back_inserter(othercodes));
		      std::copy(postfix, postfix+len1, std::back_inserter(othercodes));
		      std::copy(t, t+strlen(t), std::back_inserter(othercodes));
		    } else {
		      std::copy(buf, buf+n, std::back_inserter(othercodes));
		    }
  		  // Extract parametters...

		    n = ReadUntil((char*)"){;",buf,10240);
		    std::copy(buf, buf+n, std::back_inserter(othercodes));
        if (!n || buf[n-1]!=')')
		      break;

		    // Extract separators
    		n=ReadUntil((char*)",{;",buf,10240);
		      std::copy(buf, buf+n, std::back_inserter(othercodes));
  		    if (!n || buf[n-1]!=',')
	  	      break;
        }
      }
      // Print the THIS handling string line
      std::copy(thisBuf, thisBuf+strlen(thisBuf), std::back_inserter(othercodes));
	  }
  } else {
    strcpy(newyytext,yytext);
    std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  }

  linenumber += CountLine(tmp);

  if (shouldreturn) {
    yylval=PutToken(newyytext);
    return ID;
  }
};


{newline} {
  linenumber++;
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
};

parclass {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
      return ID;
    }

  /*  printf(" class keyword\n");*/
  yylval=PutToken(char(100));

  startPos=othercodes.size();
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return PARCLASS_KEYWORD;
};

class {
  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return CLASS_KEYWORD;

};

enum {
	yylval=PutToken(yytext);
	std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
	return ENUM;
};

namespace {
	yylval=PutToken(yytext);
	std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
	return NAMESPACE;
};

broadcast {
	yylval=PutToken(yytext);
	std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
	return BROADCAST;
};

classuid {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
      return ID;
    }

  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return CLASSID;
};

auto {
  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return AUTO_KEYWORD;
};

register {
  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return REGISTER_KEYWORD;
};


public {
  if (!insideClass) std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return PUBLIC_KEYWORD;
};
private {
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return PRIVATE_KEYWORD;
};
protected {
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return PROTECTED_KEYWORD;
};


virtual {
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return VIRTUAL_KEYWORD;
};

const {
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return CONST_KEYWORD;
};

struct {
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return STRUCT_KEYWORD;
};

static {
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return STATIC_KEYWORD;
};

sync {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
      return ID;
    }
  else
    {
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
      return SYNC_INVOKE;
    }
};


async {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
      return ID;
    }

  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return ASYNC_INVOKE;
};

in {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
      return ID;
    }

  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return INPUT;
};

out {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
      return ID;
    }

  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return OUTPUT;
};

conc {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
      return ID;
    }

  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return CONCURRENT;
};


seq {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
      return ID;
    }

  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return SEQUENTIAL;
};

mutex[ \a\b\v\f\t\r\n]*"{" {
  if (IsSystemHeader(filename))
    {
      char *yycopy=strdup(yytext+5);
      int len=strlen(yycopy);
      yylval=PutToken((char*)"mutex");
      std::copy(yytext, yytext+5, std::back_inserter(othercodes));
      for (char *t=yycopy+len-1;t!=yycopy;t--) unput(*t);
      free(yycopy);
      return ID;

      //      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
    }
  else
    {
      char str[256];
      int len=strlen(yytext)-6;
      sprintf(str," { paroc_mutex_locker _paroc_mutex%d(_paroc_omutex); ",mutexCount++);
      std::copy(str, str+strlen(str), std::back_inserter(othercodes));
      std::copy(yytext+5, yytext+5+len, std::back_inserter(othercodes));
    }
  linenumber+=CountLine(yytext+5);
};

mutex {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
      return ID;
    }

  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return MUTEX;

};

"::" {

  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return SCOPE;
};

__hidden {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
      return ID;
    }

  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return HIDDEN;
};

proc {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
      return ID;
    }

  yylval=PutToken(char(USERPROC));
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return PROC;
};
size {
  if (IsSystemHeader(filename))
    {
      yylval=PutToken(yytext);
      std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
      return ID;
    }

  yylval=PutToken(char(PARAMSIZE));
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return SIZE;
};

this {

	/* This part of parser is possible source of wrong "this" handling */
	Class *cl = thisCodeFile->FindClass(classname);
        bool insertNormalThis = true;
        if(cl!=NULL)
        {
            //If the class is a parclass, replace THIS keyword by the interface pointer __POPThis_ClassName
            if(cl->IsParClass()) {
                std::string tmp{"__POPThis_"};
                std::copy(tmp.begin(), tmp.end(), std::back_inserter(othercodes));
                std::copy(cl->GetName(), cl->GetName() + strlen(cl->GetName()), std::back_inserter(othercodes));
                insertNormalThis = false;
            }
        }

        if(insertNormalThis)
            std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));


	/*
	yylval=PutToken(yytext);
	othercodes.InsertAt(-1,"this",strlen("this"));

	printf("handle at Flex -> ");
	return THIS_KEYWORD;*/
}

unsigned{whitespace1}int {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return(ID1);
};

signed{whitespace1}int {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return(ID1);
};

unsigned{whitespace1}long {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return(ID1);
};

signed{whitespace1}long {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return(ID1);
};

signed{whitespace1}char {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return(ID1);
};

unsigned{whitespace1}char {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return(ID1);
};


signed{whitespace1}short {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return(ID1);
};

unsigned{whitespace1}short {
  yylval=PutToken(yytext);
  linenumber+=CountLine(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return(ID1);
};

typedef {
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return(TYPEDEF_KEYWORD);
};

{id} {
  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return(ID);
};

[0-9]+   {
  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return (INTEGER);
};

[0-9]*"."[0-9]+([Ee][0-9]+)? {
  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return (REAL);
};



"//"[^\n]*   ;
"/*"[^"*/"]*"*/" {
  linenumber+=CountLine(yytext);
} ;

"&&" {
  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return (AND_OP);
};

"||" {
  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return (OR_OP);
};

"==" {
  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return (EQUAL_OP);
};

"!=" {
  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return (NOTEQUAL_OP);
};

">=" {
  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return (GREATEREQUAL_OP);
};

"<=" {
  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return (LESSEQUAL_OP);
};

"?"{whitespace2}":" {
  yylval=PutToken(yytext);
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return (NONSTRICT_OD_OP);
};


"\'"|"\""|"#"|"("|")"|"{"|"}"|"["|"]"|";"|":"|","|"*"|"&"|"~"|"="|"+"|"%"|"@"|"$"|"^"|"-"|"|"|"`"|"!"  {
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
  return yytext[0];
};

<<EOF>> {
	return EOFCODE;
};
. {
  std::copy(yytext, yytext+strlen(yytext), std::back_inserter(othercodes));
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
	  while ((n=ReadUntil((char*)"\"", tmp,sz))>0 && tmp[n-2]=='\\');
	}
      else if (ch=='\'')
	{
	  int n;
	  while ((n=ReadUntil((char*)"\'", tmp,sz))>0 && tmp[n-2]=='\\');
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
  //int len=strlen(fname);

  //  return strcmp(fname+len-2,".h")==0;

  return strncmp(fname,system_header,strlen(system_header))==0;
}

