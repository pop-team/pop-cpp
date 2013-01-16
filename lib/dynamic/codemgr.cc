/**
 * File : codemgr.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of the code manager service 
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "codemgr.ph"

CodeMgr::CodeMgr(const POPString &challenge): paroc_service_base(challenge)
{
}

CodeMgr::~CodeMgr()
{
	DEBUG("Now destroy CodeMgr\n");
}

void CodeMgr::RegisterCode(const POPString &objname, const POPString &platform, const POPString &codefile)
{
	int n=info.GetSize();
	int i;
	codedb *element;
	for (i=0;i<n;i++) if (paroc_utils::isEqual(objname,info[i].objname)) break;

	if (i<n) element=&(info[i]);
	else
	{
		info.SetSize(n+1);
		element=&(info[n]);
		strcpy(element->objname,objname);
	}

	n=element->platform.GetSize();
	for (i=0;i<n;i++) if (paroc_utils::isEqual(platform,element->platform[i].platform)) break;

	if (i<n)
	{
		DEBUG("Changing (%s, %s) -> %s\n",element->objname,element->platform[i].platform,(const char *)codefile);
		strcpy(element->platform[i].codefile,codefile);
	}
	else
	{
		element->platform.SetSize(n+1);
		strcpy(element->platform[n].codefile,codefile);
		strcpy(element->platform[n].platform,platform);
	}
}

int CodeMgr::QueryCode(const POPString &objname, const POPString &platform, POPString &codefile)
{
	codefile=NULL;
	int n=info.GetSize();
	int i;
	codedb *element;
	for (i=0;i<n;i++) if (paroc_utils::isEqual(objname,info[i].objname)) break;

	if (i>=n) return 0;

	element=&(info[i]);
	n=element->platform.GetSize();
	for (i=0;i<n;i++) if (paroc_utils::MatchWildcard(platform,element->platform[i].platform)) break;

	if (i>=n) return 0;
	codefile=element->platform[i].codefile;
	return 1;
}

int CodeMgr::GetPlatform(const POPString &objname, POPString &platform)
{
	platform=NULL;
	int n=info.GetSize();
	int i;
	for (i=0;i<n;i++) if (paroc_utils::isEqual(objname,info[i].objname)) break;
	if (i>=n) return 0;
	codedb &element=info[i];
	n=element.platform.GetSize();
	for (i=0;i<n;i++)
	{
		platform+=element.platform[i].platform;
		if (i<n-1) platform+=" ";
	}
	return n;
}