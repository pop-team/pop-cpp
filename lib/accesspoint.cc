/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: implementation of network access point of parallel objects
 */

#include <stdio.h>
#include <string.h>
#include "paroc_accesspoint.h"
#include "paroc_utils.h"

//paroc_accesspoint class

paroc_accesspoint::paroc_accesspoint()
{
	endpoint=NULL;
}
// paroc_accesspoint::paroc_accesspoint(const char *hostport)
// {
//   endpoint=NULL;
//   SetAccessString(hostport);
// }

paroc_accesspoint::paroc_accesspoint(const paroc_accesspoint &p)
{
	endpoint=NULL;
	SetAccessString(p.GetAccessString());
}

paroc_accesspoint::~paroc_accesspoint()
{
	if (endpoint!=NULL) free(endpoint);
}


void paroc_accesspoint::SetAccessString(const char *hostport)
{
	if (endpoint!=hostport)
	{
		if (endpoint!=NULL)  free(endpoint);
		if (hostport!=NULL) endpoint=strdup(hostport);
		else endpoint=NULL;
	}
}
const char *paroc_accesspoint::GetAccessString() const
{
	return endpoint;
}

bool paroc_accesspoint::IsEmpty() const
{
	return (endpoint==NULL);
}

bool paroc_accesspoint::operator ==(const paroc_accesspoint &p) const
{
	return paroc_utils::isEqual(endpoint,p.GetAccessString());
}

paroc_accesspoint & paroc_accesspoint::operator =(const paroc_accesspoint &p)
{
	SetAccessString(p.GetAccessString());
	return *this;
}

void paroc_accesspoint::Serialize(paroc_buffer &buf, bool pack)
{
	if (pack)
	{
		paroc_string s(endpoint);
		buf.Push("url","paroc_string",1);
		buf.Pack(&s,1);
		buf.Pop();
	}
	else
	{
		paroc_string s;
		buf.Push("url","paroc_string",1);
		buf.UnPack(&s,1);
		buf.Pop();
		SetAccessString(s);
	}
}
