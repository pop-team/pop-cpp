#ifndef INCLUDE_POPC_CONNECTION_MPI_H_
#define INCLUDE_POPC_CONNECTION_MPI_H_

#include "paroc_combox.h"
#include <mpi.h>


/**
 * @class POPC_MPIConnection
 * @breif Declaration of MPI Connection (POP-C++ abstraction of connection). Just hold the destination rank of the communication.
 * @author Valentin Clément
 * 
 */
class POPC_MPIConnection : public paroc_connection {
public:
  POPC_MPIConnection();
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

#endif // INCLUDE_POPC_CONNECTION_MPI_H_