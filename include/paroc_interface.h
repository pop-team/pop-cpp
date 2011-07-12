/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: interface base declaration for parclass objects
*/

#ifndef _POPC_INTERFACE_CORE_H
#define _POPC_INTERFACE_CORE_H

#include <stdio.h>
#include <paroc_base.h>

#include <paroc_accesspoint.h>
#include <paroc_od.h>
#include <paroc_buffer.h>
#include <paroc_list.h>
#include <paroc_allocobj.h>


#define BIND_OK 0
#define BIND_FORWARD_SESSION 1
#define BIND_FORWARD_PERMANENT 2

#define POPC_ALLOC_RETRY 3

/*! \brief Run a command using fork
 * This method simply calls a command by creating a fork.
 * @param argv Command and arguments
 * @param env
 * @return Zero */
int RunCmd(char **argv, char *env[], int *status=NULL);


/**
 * @class paroc_interface
 * @brief Interface base declaration for parclass objects, used by POP-C++ runtime.
 *
 *
 * @author Tuan Anh Nguyen
 *
 */
class paroc_interface: paroc_base
{
public:
	paroc_interface();
	paroc_interface(const paroc_accesspoint &p);
	paroc_interface(const paroc_interface &inf);
	paroc_interface(paroc_combox *combox, paroc_buffer *buffer);

	virtual ~paroc_interface();

	//Assign an interface from the others.....
	paroc_interface & operator = (const paroc_interface &obj);

	virtual void SetOD(const paroc_od &myod);
	virtual const paroc_od &GetOD() const;

	//  virtual const char * GetResource() const;

	const paroc_accesspoint & GetAccessPoint() const;

	virtual void Serialize(paroc_buffer &buf, bool pack);

	//Find the resource that satisfies the OD, output the resource name or the jobcontact..
	bool TryLocal(paroc_accesspoint &objaccess);

	//Connect the interface to the existed object located at resource dest...
	void Bind(const paroc_accesspoint &dest);
	void Bind(const char *dest);

	//Disconnect the interface from its object
	void Release();
	//Get Binding status...
	void BindStatus(int &code, paroc_string &platform, paroc_string &info);

	//Add the object reference counter...return the new counter value...Use with care
	int AddRef();

	//Release the reference counter...and destroy the object if the counter equals 0...Use with care
	int DecRef();

	//Ask the server to use specific encoding method
	bool Encoding(paroc_string encoding);

	// Force the remote object to be terminated...
	void Kill();

	//Ask the server its state (active or inactive)
	bool ObjectActive();

#ifdef OD_DISCONNECT	
	//Make a receive with a check connection alive ping during the calculation
	bool RecvCtrl();
#endif

	/*! \brief Create a POPC object locally (JobMgr not involved)
	 * This method creates a commands to run the .obj file and execute it with method paroc_interface::Exec
	 * @param *hostname Host address or IP. If set the .obj is run via rsh/ssh on this host.
	 * @param codefile Name of the .obj executable file
	 * @param classname Name of the POPC++ parclass
	 * @param rport Socket port
	 * @param jobserv
	 * @param appserv
	 * @param objaccess
	 * @param howmany
	 * @param ruser Specify a user name for the ssh command
	 * @param rcore Specify a core number
	 * @return Zero */

	static int LocalExec(const char *hostname, const char *codefile, const char *classname, const paroc_accesspoint &jobservice, const paroc_accesspoint &appservice, paroc_accesspoint *objaccess, int howmany, const paroc_od &od);// const char* ruser=NULL, const char* rcore=NULL, bool isManual=false, bool checkConnection=0);

	static paroc_accesspoint _paroc_nobind;
	static int paroc_bind_timeout;
protected:

	virtual const char *ClassName() { return "paroc_interface"; };
	//Find a resource that satisfies the Qos and allocate an object on it

	virtual void paroc_Dispatch(paroc_buffer *buf);
	virtual void paroc_Response(paroc_buffer *buf);

	void Allocate();

	paroc_combox *__paroc_combox;
	paroc_buffer *__paroc_buf;

	paroc_accesspoint accesspoint;

	paroc_od od;

	paroc_mutex _paroc_imutex;

private:
	void NegotiateEncoding(paroc_string &enclist, paroc_string &peerplatform);

	void Tokenize(paroc_string &s, paroc_list<char *> &tokens);
	void ApplyCommPattern(const char *pattern, paroc_list<char *> &accesslist);


	//used for batch object allocation only
public:
	static int batchindex;
	static int batchsize;

private:
	static paroc_accesspoint *batchaccesspoint;

};


#endif

