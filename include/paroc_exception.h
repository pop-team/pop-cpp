/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: POP-C++ exception. All runtime exceptions are thrown as paroc_exception.

 */

#ifndef POPC_EXCEPTION_H
#define POPC_EXCEPTION_H

#include <paroc_base.h>
#include <exception>

//PAROC EXCEPTION CODE

#define USER_DEFINE_ERROR 10000
#define OBJECT_NO_RESOURCE  USER_DEFINE_ERROR+1
#define OBJECT_BIND_FAIL    USER_DEFINE_ERROR+2
#define OBJECT_MISMATCH_METHOD   USER_DEFINE_ERROR+3
#define CODE_SERVICE_FAIL   USER_DEFINE_ERROR+4

#define ALLOCATION_EXCEPTION USER_DEFINE_ERROR+5
#define OBJECT_EXECUTABLE_NOTFOUND USER_DEFINE_ERROR+6

#define POPC_BUFFER_FORMAT USER_DEFINE_ERROR+7

#define POPC_APPSERVICE_FAIL USER_DEFINE_ERROR+8
#define POPC_JOBSERVICE_FAIL USER_DEFINE_ERROR+9
#define POPC_EXEC_FAIL  USER_DEFINE_ERROR+10

#define POPC_BIND_BAD_REPLY  USER_DEFINE_ERROR+11

#define POPC_NO_PROTOCOL  USER_DEFINE_ERROR+12
#define POPC_NO_ENCODING  USER_DEFINE_ERROR+13

#define STD_EXCEPTION USER_DEFINE_ERROR+14
#define ACK_NOT_RECEIVED USER_DEFINE_ERROR+15
#define POPC_NETWORK_FAIL USER_DEFINE_ERROR+16

#define UNKNOWN_EXCEPTION USER_DEFINE_ERROR+17
#define USER_DEFINE_LASTERROR USER_DEFINE_ERROR+17

/**
 * @class paroc_exception
 * @brief POP-C++ exception, used by POP-C++ runtime.
 *
 *  All runtime exceptions are thrown as paroc_exception
 *
 * @author Tuan Anh Nguyen
 *
 */
class paroc_exception: public paroc_base, public std::exception
{
public:
	paroc_exception(int code);
	paroc_exception();
	~paroc_exception()throw(){};
	
	paroc_exception & operator = (paroc_exception &e);
	static void paroc_throw(int code, const char *reason=NULL);
	static void paroc_throw(const char *reason=NULL);
	static void paroc_throw_errno(const char *reason=NULL);
	static paroc_exception *create(int code, const char *reason=NULL);

	virtual void Serialize(paroc_buffer &buf, bool pack);

	const paroc_string Extra()const;
	void SetExtra(const char* str);
	int Code()const;
	void Print()const;
	
	// Redefine the virtual what method of exception
	const char* what() const throw();

protected:
	
	paroc_string info;
	int errcode;
};

typedef paroc_exception POPException;
#endif
