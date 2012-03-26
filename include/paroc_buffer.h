/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: buffer abstract class used to pack/unpack data.
 */

#ifndef _POPC_DATAPACK_MARSHAL_H
#define _POPC_DATAPACK_MARSHAL_H

#include <paroc_string.h>
#include <paroc_combox.h>
#include <string>
#include <vector>


#define EXCEPTION_INT  1
#define EXCEPTION_UINT 2

#define EXCEPTION_LONG 3
#define EXCEPTION_ULONG 4

#define EXCEPTION_SHORT 5
#define EXCEPTION_USHORT 6

#define EXCEPTION_BOOL 7

#define EXCEPTION_CHAR 8
#define EXCEPTION_UCHAR 9

#define EXCEPTION_STRING 10

#define EXCEPTION_FLOAT 11
#define EXCEPTION_DOUBLE 12

#define EXCEPTION_OBJECT 13
#define EXCEPTION_POPC_STD 14


//bit FLAGS values customized marshalling/demarshalling procedure....
#define FLAG_MARSHAL  2
#define FLAG_INPUT  1


#define TYPE_REQUEST 0
#define TYPE_RESPONSE 1
#define TYPE_EXCEPTION 2


class paroc_interface;
class paroc_exception;

/**
 * @class paroc_message_header
 * @author Tuan Anh Nguyen
 */
class paroc_message_header
{
public:
	paroc_message_header(int classid, int methodid, int semantics, const char *methodname);
	paroc_message_header(const char *methodname);
	paroc_message_header(int exceptioncode, const char *methodname);

	paroc_message_header();
	void operator =(const  paroc_message_header &dat);

	inline int GetType() const { return type;};
	inline int GetClassID() const { return id[0];};
	inline int GetMethodID() const { return id[1];};
	inline int GetSemantics() const { return id[2];};

	inline int GetExceptionCode() const { return exception;};
	inline const char *GetMethodName() const { return methodname;};



	inline void SetType(int msgtype) { type=msgtype;};

	inline void SetClassID(int classid) { id[0]=classid;};
	inline void SetMethodID(int methodid) { id[1]=methodid;};
	inline void SetSemantics(int semantics) { id[2]=semantics;};
	inline void SetExceptionCode(int code) { exception=code;};

	inline void SetMethodName(const char* name) { methodname=name;};

private:
	int type;
	int id[3];
	const char *methodname;
	int exception;
};


/**
 * @class paroc_buffer
 * @brief Buffer abstract class used to pack/unpack data, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
class paroc_buffer
{
public:
	paroc_buffer();
protected:
	virtual ~paroc_buffer();

public:
	virtual void Reset()=0;

	virtual void SetHeader(const paroc_message_header &data);
	virtual const paroc_message_header & GetHeader() const;

	virtual void Push(const char *paramname, const char *paramtype, int nelem);
	virtual void Pop();

	virtual void Pack(const int *data, int n)=0;
	virtual void UnPack(int *data, int n)=0;

	virtual void Pack(const unsigned *data, int n)=0;
	virtual void UnPack(unsigned *data, int n)=0;

	virtual void Pack(const long *data, int n)=0;
	virtual void UnPack(long *data, int n)=0;

	virtual void Pack(const unsigned long *data, int n)=0;
	virtual void UnPack(unsigned long *data, int n)=0;

	virtual void Pack(const short *data, int n)=0;
	virtual void UnPack(short *data, int n)=0;

	virtual void Pack(const unsigned short *data, int n)=0;
	virtual void UnPack(unsigned short *data, int n)=0;

	virtual void Pack(const bool *data, int n)=0;
	virtual void UnPack(bool *data, int n)=0;

	virtual void Pack(const char *data, int n)=0;
	virtual void UnPack(char *data, int n)=0;

	virtual void Pack(const unsigned char *data, int n)=0;
	virtual void UnPack(unsigned char *data, int n)=0;

	virtual void Pack(const float *data, int n)=0;
	virtual void UnPack(float *data, int n)=0;

	virtual void Pack(const double *data, int n)=0;
	virtual void UnPack(double *data, int n)=0;

	virtual void Pack(const paroc_string *list, int n);
	virtual void UnPack(paroc_string *list, int n);

	virtual void Pack(const std::string *list, int n);
	virtual void UnPack(std::string *list, int n);

	// Added by lwk
	virtual void Pack(const signed char *data, int n)=0;
	virtual void UnPack(signed char *data, int n)=0;

	/*virtual void Pack(const long long *data, int n)=0;
	virtual void UnPack(long long *data, int n)=0;

	virtual void Pack(const long double *data, int n)=0;
	virtual void UnPack(long double *data, int n)=0;*/

	virtual bool Send(paroc_combox &s, paroc_connection *conn=0)=0;
	virtual bool Send(paroc_connection *conn);

	virtual bool Recv(paroc_combox &s, paroc_connection *conn=0)=0;

	virtual bool Recv(paroc_connection *conn);

#ifdef OD_DISCONNECT
	virtual bool RecvCtrl(paroc_combox &s, paroc_connection *conn=0)=0;
#endif
	//Exception stubs...
	static bool SendException(paroc_buffer &except, paroc_connection *s,int code);
	static bool SendException(paroc_buffer &except, paroc_connection *s,unsigned code);

	static bool SendException(paroc_buffer &except, paroc_connection *s,long code);
	static bool SendException(paroc_buffer &except, paroc_connection *s,unsigned long code);

	static bool SendException(paroc_buffer &except, paroc_connection *s,short code);
	static bool SendException(paroc_buffer &except, paroc_connection *s,unsigned short code);

	static bool SendException(paroc_buffer &except, paroc_connection *s,bool code);

	static bool SendException(paroc_buffer &except, paroc_connection *s,char code);
	static bool SendException(paroc_buffer &except, paroc_connection *s,unsigned char code);

	static bool SendException(paroc_buffer &except, paroc_connection *s,char* code);

	static bool SendException(paroc_buffer &except, paroc_connection *s,float code);
	static bool SendException(paroc_buffer &except, paroc_connection *s,double code);

	static bool SendException(paroc_buffer &except, paroc_connection *s, paroc_exception &code);
	static bool SendException(paroc_buffer &except, paroc_connection *s, paroc_interface &code);

	static void CheckAndThrow(paroc_buffer &except);

	virtual void Destroy();

	/* NOTE: The methods below are here for the user (not used in POPC yet)*/
	void Pack( std::vector<float> *a, int n);
	void UnPack( std::vector<float> *a, int n);
	void Pack( std::vector<double> *a, int n);
	void UnPack( std::vector<double> *a, int n);
	//void Pack( std::vector<bool> *a, int n);
	//void UnPack( std::vector<bool> *a, int n);
	void Pack( std::vector<char> *a, int n);
	void UnPack( std::vector<char> *a, int n);
	void Pack( std::vector<unsigned char> *a, int n);
	void UnPack( std::vector<unsigned char> *a, int n);
	void Pack( std::vector<short> *a, int n);
	void UnPack( std::vector<short> *a, int n);
	void Pack( std::vector<unsigned short> *a, int n);
	void UnPack( std::vector<unsigned short> *a, int n);
	void Pack( std::vector<int> *a, int n);
	void UnPack( std::vector<int> *a, int n);
	void Pack( std::vector<long> *a, int n);
	void UnPack( std::vector<long> *a, int n);
	void Pack( std::vector<std::string> *a, int n);
	void UnPack( std::vector<std::string> *a, int n);

protected:
	paroc_message_header header;
};


typedef paroc_buffer POPBuffer;
#endif
