/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/10/15
 * @brief Implementation of MPI Connection (POP-C++ abstraction of connection). 
 *        Just hold the destination rank of the MPI communicator.
 *
 *
 */

#include "popc_connection_mpi.h"

POPC_MPIConnection::POPC_MPIConnection() : _has_communicator(false), _is_connected(false), paroc_connection(NULL), _connection_index(0), _is_asynchronous(false), _tag_set(false)
{
  
}

POPC_MPIConnection::POPC_MPIConnection(paroc_combox *cb): _has_communicator(false), _is_connected(false), paroc_connection(cb), _connection_index(0), _is_asynchronous(false), _tag_set(false)
{
	signal(SIGPIPE, SIG_IGN);
}

POPC_MPIConnection::POPC_MPIConnection(POPC_MPIConnection &me): _has_communicator(false), _is_connected(false), _connection_index(0), _is_asynchronous(false), _tag_set(false), paroc_connection(me.GetCombox(), me.GetBufferFactory())
{
  set_communicator(me.get_communicator());
  set_connection_index(me.get_connection_index());
}

/**
 * MPI Connection destructor. Free the communicator if it has been set. 
 */
POPC_MPIConnection::~POPC_MPIConnection(){
}

/**
 * Return a new connection based on this connection
 * @return A pointer to the new connection
 */
paroc_connection* POPC_MPIConnection::Clone()
{
	return new POPC_MPIConnection(*this);
}

/**
 * Get the inter-communicator for the connection
 * @return A MPI inter-communicator
 */
void POPC_MPIConnection::set_communicator(MPI::Intercomm communicator)
{
  _has_communicator = true;
  _is_connected = true;
  _communicator = communicator;
}

/**
 * Get the inter-communicator for the connection
 * @return A MPI inter-communicator
 */
MPI::Intercomm POPC_MPIConnection::get_communicator()
{
  return _communicator;
}

/**
 * Check if the communicator has been set
 * @return TRUE if the communicator is set. FALSE in any other cases. 
 */
bool POPC_MPIConnection::has_communicator()
{
  return _has_communicator;
}

/**
 *
 */
void POPC_MPIConnection::set_connection_index(int value)
{
  _connection_index = value;
}

/**
 *
 */
int POPC_MPIConnection::get_connection_index()
{
  return _connection_index;
}

/**
 *
 */
void POPC_MPIConnection::set_as_asynchronous()
{
  _is_asynchronous = true;  
}

bool POPC_MPIConnection::is_asynchronous()
{
  return _is_asynchronous;
}

void POPC_MPIConnection::set_current_tag(int value)
{
  _tag_set = true;
  _current_tag = value;
}

int POPC_MPIConnection::get_current_tag()
{
  return _current_tag;
}

bool POPC_MPIConnection::is_tag_set()
{
  return _tag_set;
}

void POPC_MPIConnection::unset_current_tag()
{
  _tag_set = false;
}


/**
 * Reset the connection. Disconnect the communicator and free it.
 */
void POPC_MPIConnection::reset()
{
  /*if(_has_communicator){
    printf("MPI-COMBOX(%s): before MPI.Disconnect()\n", (is_server())?"Server":"Client");  
    _communicator.Disconnect();
    printf("MPI-COMBOX(%s): after MPI.Disconnect()\n", (is_server())?"Server":"Client");
  } else {
    printf("MPI-COMBOX(%s): reset() connection as no communicator\n", (is_server())?"Server":"Client");
  }
  _has_communicator = false; */
}

/**
 * Check if the associated combox is a server or client combox
 * @return TRUE if the associated combox is a server. FALSE if the associated combox is a client
 */
bool POPC_MPIConnection::is_server()
{
  return false; 
}