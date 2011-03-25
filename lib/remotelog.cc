/**
 * File : remotelog.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of the remote log service
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 */

#include <stdio.h>
#include "remotelog.ph"

RemoteLog::RemoteLog(const paroc_string &challenge): paroc_service_base(challenge)
{
}
RemoteLog::~RemoteLog()
{
}

void RemoteLog::Log(const paroc_string &info)
{
	paroc_string prt=info;
	printf("%s",prt.GetString());
	fflush(stdout);
}
