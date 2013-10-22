/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief system stuffs and declarations used by the runtime
 *
 *
 */

#ifndef _POPC_SYSTEM_H
#define _POPC_SYSTEM_H
#include <paroc_accesspoint.h>

#ifndef __WIN32__
#include <net/if.h>
#include <ifaddrs.h>
#endif
#define DEFAULTPORT  2711

// For set processor
#include <sched.h>

//Added by clementval for COUT support
#include <iostream>
#include <sstream>
//End of add

class AppCoreService;

/**
 * @class paroc_system
 * @brief System information, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
class paroc_system
{
public:
	paroc_system();
	~paroc_system();

	static bool Initialize(int *argc,char ***argv);//only for the main...
	static void Finalize(bool normalExit); //only for the main...

	/**
	 * @brief Returns host of node in string format
	 */
	static paroc_string GetHost();

	/**
	 * @brief Returns IP of node in string format
	 * Note: checks POPC_IP, then ip from POPC_IFACE, then ip from GetDefaultInterface()
	 */
	static paroc_string GetIP();

	/**
	 * @brief Returns IP of node
	 * @param hostname
	 * @param iplist
	 * @param listsize
	 */
	static int GetIP(const char *hostname, int *iplist, int listsize);

	/**
	 * @brief Returns IP of node
	 * @param iplist returned IP in integer format
	 * @param listsize Max nb of IPs returned
	 * Note : calls GetIP()
	 */
	static int GetIP(int *iplist, int listsize);

	/**
	 * @brief Returns local IP on interface
	 * @param iface interface
	 * @param str_ip returned IP
	 * @return true if success
	 */
	static bool GetIPFromInterface(paroc_string& iface, paroc_string& str_ip);

	/**
	 * @brief Returns the default interface
	 * @return interface
	 * Note: Returned value is based on default gateway
	 */
	static paroc_string GetDefaultInterface();

	static void perror(const char *msg);
	static void perror(const paroc_exception *e);
	
	/**
	 * @brief Sets object execution on a given CPU
	 */
	static void processor_set(int cpu);

public:
  static paroc_accesspoint appservice;
  static paroc_accesspoint jobservice;
  static int pop_current_local_address;
  static int popc_local_mpi_communicator_rank;
  static paroc_string platform;
  static std::ostringstream _popc_cout;

private:
  static const char *paroc_errstr[17];
  static paroc_string POPC_HostName;  //V1.3m

  static AppCoreService *CreateAppCoreService(char *codelocation);
  static AppCoreService *mgr;
  static paroc_string challenge;

};
typedef paroc_system POPSystem;

#endif
