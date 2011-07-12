/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: POP-C++ null terminated string implementation
 */

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "paroc_string.h"

paroc_string::paroc_string()
{
	data=NULL;
}

paroc_string::paroc_string(const char *x)
{
	data= (x==NULL)? NULL : strdup(x);
}

paroc_string::paroc_string(const char *x, int n)
{
	if (x==NULL || n<=0) data=NULL;
	else
	{
		data= (char *)malloc(sizeof(char)*(n+1));
		strncpy(data,x,n);
		data[n]=0;
	}
}

paroc_string::paroc_string(std::string x)
{
	data= (x.c_str()==NULL)? NULL : strdup(x.c_str());
}

paroc_string::paroc_string(const paroc_string &x)
{
	data= (x==NULL)? NULL : strdup(x);
}

paroc_string::~paroc_string()
{
	if (data!=NULL)
	{
		free(data);
		data=NULL;
	}

}

paroc_string::operator const char *() const
{
	return data;
}

paroc_string::operator std::string () const
{
	return data;
}

const char * paroc_string::operator =(const char *x)
{
	if (data!=x)
	{
		if (data!=NULL) free(data);
		data=(x==NULL)? NULL: strdup(x);
	}
	return data;
}

const paroc_string &paroc_string::operator =(const paroc_string &x)
{
	if (this!=&x)
	{
		if (data!=NULL) free(data);
		data=(x==NULL)? NULL: strdup(x);
	}
	return (*this);
}

void paroc_string::operator +=(const char *x)
{
	if (data==NULL)
	{
		*this=x;
	}
	else if (x!=NULL)
	{
		int newsz=Length()+strlen(x)+1;
		if (newsz)
		{
			char *tmp=(char *)realloc(data,newsz+1);
			if (tmp==NULL) paroc_exception::paroc_throw(ENOMEM,"paroc_string");
			data=tmp;
			strcat(data,x);
		}
	}
}

paroc_string paroc_string::operator + (const paroc_string &x)
{
	paroc_string ret(data);
	ret+=x;
	return ret;
}

void paroc_string::substring(int start, int end, paroc_string &sub)
{
	if (data==NULL) sub=NULL;
	else
	{
		int l=strlen(data);
		if (start<0) start=0;
		if (end>=l) end=l-1;
		if (start>end) sub=NULL;
		else sub=paroc_string(data+start,end-start+1);
	}
}

int paroc_string::Length() const
{
	if (data==NULL) return -1;
	return strlen(data);
}

char *paroc_string::GetString()
{
	return data;
}
