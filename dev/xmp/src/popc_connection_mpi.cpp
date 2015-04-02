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

#include <signal.h>

pop_mpi_connection::pop_mpi_connection() : pop_connection(NULL), _is_connected(false),  _has_communicator(false), _connection_index(0), _is_asynchronous(false), _tag_set(false) {

}

pop_mpi_connection::pop_mpi_connection(pop_combox *cb): pop_connection(cb), _is_connected(false), _has_communicator(false),  _connection_index(0), _is_asynchronous(false), _tag_set(false) {
    signal(SIGPIPE, SIG_IGN);
}

pop_mpi_connection::pop_mpi_connection(pop_mpi_connection &me): pop_connection(me.GetCombox(), me.GetBufferFactory()), _is_connected(false), _has_communicator(false), _connection_index(0), _is_asynchronous(false), _tag_set(false) {
    set_communicator(me.get_communicator());
    set_connection_index(me.get_connection_index());
}

/**
 * MPI Connection destructor. Free the communicator if it has been set.
 */
pop_mpi_connection::~pop_mpi_connection() {
}

/**
 * Return a new connection based on this connection
 * @return A pointer to the new connection
 */
pop_connection* pop_mpi_connection::Clone() {
    return new pop_mpi_connection(*this);
}

/**
 * Get the inter-communicator for the connection
 * @return A MPI inter-communicator
 */
void pop_mpi_connection::set_communicator(MPI::Intercomm communicator) {
    _has_communicator = true;
    _is_connected = true;
    _communicator = communicator;
}

/**
 * Get the inter-communicator for the connection
 * @return A MPI inter-communicator
 */
MPI::Intercomm pop_mpi_connection::get_communicator() {
    return _communicator;
}

/**
 * Check if the communicator has been set
 * @return TRUE if the communicator is set. FALSE in any other cases.
 */
bool pop_mpi_connection::has_communicator() {
    return _has_communicator;
}

/**
 *
 */
void pop_mpi_connection::set_connection_index(int value) {
    _connection_index = value;
}

/**
 *
 */
int pop_mpi_connection::get_connection_index() {
    return _connection_index;
}

/**
 *
 */
void pop_mpi_connection::set_as_asynchronous() {
    _is_asynchronous = true;
}

bool pop_mpi_connection::is_asynchronous() {
    return _is_asynchronous;
}

void pop_mpi_connection::set_current_tag(int value) {
    _tag_set = true;
    _current_tag = value;
}

int pop_mpi_connection::get_current_tag() {
    return _current_tag;
}

bool pop_mpi_connection::is_tag_set() {
    return _tag_set;
}

void pop_mpi_connection::unset_current_tag() {
    _tag_set = false;
}


/**
 * Reset the connection. Disconnect the communicator and free it.
 */
void pop_mpi_connection::reset() {
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
bool pop_mpi_connection::is_server() {
    return false;
}
