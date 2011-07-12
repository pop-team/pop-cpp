#ifndef PAROC_EXCEPTION_H
#define PAROC_EXCEPTION_H

#include <paroc_base.h>

//PAROC EXCEPTION CODE

#define USER_DEFINE_ERROR 10000
#define OBJECT_NO_RESOURCE  USER_DEFINE_ERROR+1
#define OBJECT_BIND_FAIL    USER_DEFINE_ERROR+2
#define OBJECT_MISMATCH_METHOD   USER_DEFINE_ERROR+3
#define CODE_SERVICE_FAIL   USER_DEFINE_ERROR+4

#define ALLOCATION_EXCEPTION USER_DEFINE_ERROR+5

#define PAROC_BUFFER_FORMAT USER_DEFINE_ERROR+6

#define PAROC_APPSERVICE_FAIL USER_DEFINE_ERROR+7
#define PAROC_JOBSERVICE_FAIL USER_DEFINE_ERROR+8
#define PAROC_EXEC_FAIL  USER_DEFINE_ERROR+9

#define PAROC_BIND_BAD_REPLY  USER_DEFINE_ERROR+10

#define PAROC_NO_PROTOCOL  USER_DEFINE_ERROR+11
#define PAROC_NO_ENCODING  USER_DEFINE_ERROR+12

#define UNKNOWN_EXCEPTION USER_DEFINE_ERROR+13
#define USER_DEFINE_LASTERROR USER_DEFINE_ERROR+13

class paroc_exception: public paroc_base
{
 public:
  paroc_exception & operator = (paroc_exception &e);
  static void paroc_throw(int code, const char *reason=NULL);
  static void paroc_throw_errno(const char *reason=NULL);
  static paroc_exception *create(int code, const char *reason=NULL);

  virtual void Serialize(paroc_buffer &buf, bool pack);

  paroc_string & Extra();
  int & Code();  
  

 protected:
  paroc_exception(int code);
  paroc_exception();

 protected:
 paroc_string info;
  int errcode;
};

typedef paroc_exception POPException;
#endif
