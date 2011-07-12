#include <string.h>
#include <errno.h>

#include "paroc_exception.h"

paroc_exception::paroc_exception()
{
  errcode=0;
}
paroc_exception::paroc_exception(int code)
{
  errcode=code;
}

paroc_exception & paroc_exception::operator =(paroc_exception &e)
{
  errcode=e.Code();
  info=e.Extra();
  return *this;
}
paroc_string & paroc_exception::Extra()
{
  return info;
}

int & paroc_exception::Code()
{
  return errcode;
}

void paroc_exception::paroc_throw(int code, const char *reason)
{
  paroc_exception *e=new paroc_exception(code);
  if (reason!=NULL) e->Extra()=reason;
  throw e;
}

void paroc_exception::paroc_throw_errno(const char *reason)
{
  paroc_exception *e=new paroc_exception(errno);
  if (reason!=NULL) e->Extra()=reason;
  throw e;
}

paroc_exception *paroc_exception::create(int code, const char *reason)
{
  paroc_exception *e=new paroc_exception(code);
  if (reason!=NULL) e->Extra()=reason;
  return e;
}

void paroc_exception::Serialize(paroc_buffer &buf, bool pack)
{
  if (pack)
    {
      buf.Push("code","int",1);
      buf.Pack(&errcode,1);
      buf.Pop();

      buf.Push("info","paroc_string",1);
      buf.Pack(&info,1);
      buf.Pop();
   }
  else
    {
      buf.Push("code","int",1);
      buf.UnPack(&errcode,1);
      buf.Pop();

      buf.Push("info","paroc_string",1);
      buf.UnPack(&info,1);
      buf.Pop();
    }
}
