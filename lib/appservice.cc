#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "appservice.ph"

AppCoreService::AppCoreService(const paroc_string &challenge, bool daemon, const paroc_string &codelocation): paroc_service_base(challenge), CodeMgr(challenge), RemoteLog(challenge), ObjectMonitor(challenge)
{
  if (daemon) Start();
}

AppCoreService::~AppCoreService()
{
}

bool AppCoreService::QueryService(const paroc_string &name)
{
  if (name==NULL) return false;

  if (paroc_utils::isEqual(name,"CodeMgr")) return true;
  if (paroc_utils::isEqual(name,"RemoteLog")) return true;
  if (paroc_utils::isEqual(name,"ObjectMonitor")) return true;

  return false;
}

bool AppCoreService::QueryService(const paroc_string &name, paroc_service_base &service)
{
  return false;
}

bool AppCoreService::QueryService(const paroc_string &name, paroc_accesspoint &service)
{
  return false;
}

bool AppCoreService::RegisterService(const paroc_string &name, const paroc_service_base &newservice)
{
}
