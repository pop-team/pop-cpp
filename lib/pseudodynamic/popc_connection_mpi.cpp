#include "popc_connection_mpi.h"

#include <signal.h>

POPC_MPIConnection::POPC_MPIConnection(paroc_combox *cb): paroc_connection(cb), _is_connected(false), _has_communicator(false), _connection_index(0), _is_asynchronous(false), _tag_set(false) {
    signal(SIGPIPE, SIG_IGN);
}

POPC_MPIConnection::POPC_MPIConnection(POPC_MPIConnection &me): paroc_connection(me.GetCombox(), me.GetBufferFactory()), _is_connected(false), _has_communicator(false), _connection_index(0), _is_asynchronous(false), _tag_set(false) {
    set_communicator(me.get_communicator());
    set_connection_index(me.get_connection_index());
}

/**
 * MPI Connection destructor. Free the communicator if it has been set.
 */
POPC_MPIConnection::~POPC_MPIConnection() {
}

/**
 * Return a new connection based on this connection
 * @return A pointer to the new connection
 */
paroc_connection* POPC_MPIConnection::Clone() {
    return new POPC_MPIConnection(*this);
}

/**
 * Get the inter-communicator for the connection
 * @return A MPI inter-communicator
 */
void POPC_MPIConnection::set_communicator(MPI::Intercomm communicator) {
    _has_communicator = true;
    _is_connected = true;
    _communicator = communicator;
}

/**
 * Get the inter-communicator for the connection
 * @return A MPI inter-communicator
 */
MPI::Intercomm POPC_MPIConnection::get_communicator() {
    return _communicator;
}

/**
 * Check if the communicator has been set
 * @return TRUE if the communicator is set. FALSE in any other cases.
 */
bool POPC_MPIConnection::has_communicator() {
    return _has_communicator;
}

/**
 *
 */
void POPC_MPIConnection::set_connection_index(int value) {
    _connection_index = value;
}

/**
 *
 */
int POPC_MPIConnection::get_connection_index() {
    return _connection_index;
}

/**
 *
 */
void POPC_MPIConnection::set_as_asynchronous() {
    _is_asynchronous = true;
}

bool POPC_MPIConnection::is_asynchronous() {
    return _is_asynchronous;
}

void POPC_MPIConnection::set_current_tag(int value) {
    _tag_set = true;
    _current_tag = value;
}

int POPC_MPIConnection::get_current_tag() {
    return _current_tag;
}

bool POPC_MPIConnection::is_tag_set() {
    return _tag_set;
}

void POPC_MPIConnection::unset_current_tag() {
    _tag_set = false;
}


/**
 * Reset the connection. Disconnect the communicator and free it.
 */
void POPC_MPIConnection::reset() {
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
bool POPC_MPIConnection::is_server() {
    return combox->is_server();
}
