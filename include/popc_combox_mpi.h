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
#include <map>

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
  
  void set_communicator(MPI::Intercomm communicator);
  MPI::Intercomm get_communicator(); 
  
  void set_connection_index(int value);
  int get_connection_index();
  
  void set_as_asynchronous();
  bool is_asynchronous();
  
  void set_current_tag(int value);
  void unset_current_tag();
  int get_current_tag();
  bool is_tag_set();
  
  bool has_communicator();
  void reset();
  bool is_server();
  
private:
  MPI::Intercomm _communicator;
  bool _is_connected;
  bool _has_communicator;
  int _connection_index;
  bool _is_asynchronous;
  int _current_tag;
  bool _tag_set;
  
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
  static const char* POPC_COMBOX_MPI_PROTOCOL_PREFIX_WITH_SLASH;
  static const char* POPC_COMBOX_MPI_ACCESSPOINT_DELIMITER;
  static const int POPC_COMBOX_MPI_INITIAL_RSIZE;
  static const int POPC_COMBOX_MPI_HEADER_SIZE; 
  static const int POPC_COMBOX_MPI_NEW_CONNECTION_TAG; 
  static const int POPC_COMBOX_MPI_KILL_TAG;    
  static const int POPC_COMBOX_MPI_NEW_MESSAGE_TAG;   
  
	virtual bool Create(char* host, int port, bool server = false);
	virtual bool Connect(const char *url);
	virtual bool connect_and_die(std::string &url);		
	virtual bool unlock_wait(bool rewait);
	
	virtual paroc_connection* get_connection();
	virtual paroc_connection* reconnect();	
	
	virtual int Send(const char *s, int len);
	virtual int Send(const char *s, int len, paroc_connection *conn, bool unlock);
	virtual int init_send(paroc_connection *conn, bool unlock);
	virtual int Recv(char *s, int len, bool unlock);
	virtual int Recv(char *s, int len, paroc_connection *&iopeer, bool unlock);
	
	virtual void send_data_length(int length, paroc_connection *conn);
  virtual int receive_data_length(paroc_connection *conn);	

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

	bool _is_server;
	bool isCanceled;

	POPC_MPIConnection *peer;

	// Only used by combox server 
	int index;
	int nready;

 private:
  // Only useful for server combox
  MPI::Intracomm _self;
  MPI::Intracomm _self_for_die;
  MPI::Intercomm _parent;
  MPI::Intracomm _broker_intracomm;
  std::string _broker_port_name;
  std::string _accept_port_name;  
  
  int _node_id;
  
  int _connection_counter;
  int _request_array_size;
  bool _is_port_open;
  
  // To manage multiple connections
  //std::map<int, MPI::Comm*> _connections;  
  MPI::Intercomm _connections[10];
  MPI::Request _pending_requests[10];  
  int _pending_data[10];
  int _current_tag;
  bool _have_to_get_lock;
  
  
  paroc_condition mpicond;
  int data;   

};
#endif  // INCLUDE_POPC_COMBOX_MPI_H_