/**
 * Copyright 2012 GRID & Cloud Computing Group, University of applied Sciences of western Switzerland
 * @author	Valentin Clement
 * @date 	2012/09/25
 * @brief	Declaration of the special combox using MPI as communication layer
 *
 * Modification
 * Date         Author      Description
 * 2012/10/01   clementval  XXX
 */

#ifndef INCLUDE_POPC_COMBOX_MPI_H_
#define INCLUDE_POPC_COMBOX_MPI_H_

#include <mpi.h>
#include <string>
//#include <map>

#include "include/paroc_combox.h"


/**
 *
 */
class POPC_MPIConnection : public paroc_connection {
public:
  explicit POPC_MPIConnection(paroc_combox *cb);
  explicit POPC_MPIConnection(POPC_MPIConnection &me);
  ~POPC_MPIConnection();
  
  virtual paroc_connection *Clone();
  
  
  void setCommunicator(MPI::Intercomm communicator);
  MPI::Intercomm getCommunicator(); 
  bool hasCommunicator();
  void setCommunicatorIndex(int value);
  void reset();
  bool is_server();
  
private:
  MPI::Intercomm _communicator;
  bool _hasCommunicator;
  int _comm_index;
};



/**
 * @class paroc_combox_socket
 * @brief Socket declaration of combox, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class popc_combox_mpi: public paroc_combox {
 public:
	popc_combox_mpi();
	virtual ~popc_combox_mpi();


  static const char* POPC_COMBOX_MPI_PROTOCOL_PREFIX;

	virtual bool Create(char* host, int port, bool server = false);
	virtual bool Connect(const char *url);
	
	virtual paroc_connection* get_connection();
	virtual paroc_connection* reconnect();	
	
	virtual int Send(const char *s, int len);
	virtual int Send(const char *s, int len, paroc_connection *conn);
	virtual int Recv(char *s, int len);
	virtual int Recv(char *s, int len, paroc_connection *&iopeer);

	virtual paroc_connection *Wait();
	virtual void Close();
	
	virtual bool disconnect(paroc_connection *connection);
	virtual bool is_server();

	/**
	 * @brief Returns URL of object
	 * @param accesspoint Returned URL (protocol://host:port)
	 * @return true if success
	 */
	virtual bool GetUrl(paroc_string & accesspoint);
	virtual bool GetProtocol(paroc_string & protocolName);
  virtual void Destroy();
	
	//bool hasCommunicator();
	//void setCommunicator(MPI::Intercomm comm);
	//MPI::Intercomm getCommunicator();



 protected:
	virtual paroc_connection* CreateConnection(int fd);
	bool Connect(const char *host, int port);
	int GetPort();
	int GetOpt(int level, int opt, char *buf, socklen_t &len);
	int SetOpt(int level, int opt, char *buf, socklen_t len);

	bool _isServer;
	bool isCanceled;

	POPC_MPIConnection *peer;

	// Only used by combox server 
	int index;
	int nready;

 private:
   std::string _port_name;
   //MPI::Intercomm _communicator;
   //bool _hasCommunicator;
   bool _is_port_open;
   int _rank;
   int _comm_counter;
//   std::map<int, MPI::Intercomm> _communicators;
   

};
#endif  // INCLUDE_POPC_COMBOX_MPI_H_