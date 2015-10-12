/**
 * @author  Valentin Clement
 * @date        2012/09/25
 * @brief   Implementation of the combox using MPI Communication layer
 */

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#include "pop_combox_mpi.h"
#include "pop_broker.h"

/**
 *
 * POPC_COMBOX_MPI IMPLEMENTATION
 *
 */

// Constant declaration
const char* popc_combox_mpi::POPC_COMBOX_MPI_PROTOCOL_PREFIX = "mpi";
const char* popc_combox_mpi::POPC_COMBOX_MPI_PROTOCOL_PREFIX_WITH_SLASH = "mpi://";
const char* popc_combox_mpi::POPC_COMBOX_MPI_ACCESSPOINT_DELIMITER = "__";
const int popc_combox_mpi::POPC_COMBOX_MPI_INITIAL_RSIZE = 10;
const int popc_combox_mpi::POPC_COMBOX_MPI_HEADER_SIZE = 20;

popc_combox_mpi::popc_combox_mpi()
    : _is_server(false), isCanceled(false), peer(NULL), index(0), nready(0), _current_tag(0) {
}

popc_combox_mpi::~popc_combox_mpi() {
    if (!is_server()) {
        Close();
    }
}

/**
 * Create a new MPI Combox. Server combox will open a MPI port to receive new connection.
 */
bool popc_combox_mpi::Create(char* /*host*/, int /*port*/, bool server) {
    _have_to_get_lock = false;
    _is_server = server;
    if (_is_server) {
        // If MPI_Init was not called yet, we will call it now
        if (!MPI::Is_initialized()) {
            // Init MPI for multithread support
            MPI::Init();
        }
    }
    _node_id = MPI::COMM_WORLD.Get_rank();
    return true;
}

/**
 * Get the connection initiated by the Connected call
 * @return
 */
pop_connection* popc_combox_mpi::get_connection() {
    if (peer != NULL) {
        return peer;
    }
    return NULL;
}

/**
 * Connect to MPI destination
 * @param url
 * @return
 */
bool popc_combox_mpi::Connect(const char* url) {
    // Substring the url to make the two phases connection
    std::string full_accesspoint(url);
    std::size_t found;
    found = full_accesspoint.find(POPC_COMBOX_MPI_PROTOCOL_PREFIX_WITH_SLASH);
    if (found != std::string::npos) {
        full_accesspoint = full_accesspoint.substr(found + 6);
    } else {
        return false;
    }

    peer = new pop_mpi_connection(this);
    peer->set_communicator(MPI::COMM_WORLD);
    peer->set_connection_index(atoi(full_accesspoint.c_str()));

    return true;
}

/**
 *
 */
bool popc_combox_mpi::connect_and_die(std::string& url) {
    std::string tmp(pop_broker::accesspoint.GetAccessString());

    // Substring the url to make the two phases connection
    std::string full_accesspoint(url);
    std::size_t found;
    found = full_accesspoint.find(POPC_COMBOX_MPI_PROTOCOL_PREFIX_WITH_SLASH);
    if (found != std::string::npos) {
        full_accesspoint = full_accesspoint.substr(found + 6);
    }

    int dest = atoi(full_accesspoint.c_str());

    // Create a dummy message to unlock the receive thread
    pop_message_header h(0, 7, INVOKE_SYNC, "DummyMethod");

    pop_mpi_connection* connection = new pop_mpi_connection(this);
    connection->set_communicator(MPI::COMM_WORLD);
    connection->set_connection_index(dest);
    connection->set_as_asynchronous();

    pop_buffer_factory* bufferFactory = connection->GetBufferFactory();
    pop_buffer* tmp_buffer = bufferFactory->CreateBuffer();
    tmp_buffer->Reset();
    tmp_buffer->SetHeader(h);
    tmp_buffer->Send(connection);
    return true;
}

int popc_combox_mpi::Send(const char* /*s*/, int /*length*/) {
    if (peer == NULL) {
        return 0;
    }
    return 0;
}

int popc_combox_mpi::Send(const char* s, int length, pop_connection* conn, bool unlock) {
    if (conn == NULL) {
        return Send(s, length);
    }

    int tag;

    if (!is_server()) {
        if (unlock) {
            // Set the send tag if the combox is a client combox and it header message
            dynamic_cast<pop_mpi_connection*>(conn)->set_current_tag(((_node_id + 1) * 1000) + 1);
            tag = 0;
        } else {
            // Set the send tag if the combox is a client combox and it data message
            tag = dynamic_cast<pop_mpi_connection*>(conn)->get_current_tag();
        }
    } else {
        // Set the send tag if the combox is a server combox
        tag = ((dynamic_cast<pop_mpi_connection*>(conn)->get_connection_index() + 1) * 1000) + 2;
    }

    // Get the destination of the message from the connection
    int destination = dynamic_cast<pop_mpi_connection*>(conn)->get_connection_index();

    if (((pop_mpi_connection*)conn)->is_asynchronous()) {
        MPI::COMM_WORLD.Isend(s, length, MPI_CHAR, destination, tag);
    } else {
        MPI::COMM_WORLD.Send(s, length, MPI_CHAR, destination, tag);
    }

    return 0;
}

int popc_combox_mpi::Recv(char* s, int length, bool /*unlock*/) {
    if (peer == NULL) {
        LOG_ERROR("peer==NULL");
        return -1;
    }
    MPI::Status status;
    MPI::COMM_WORLD.Recv(s, length, MPI_CHAR, MPI_ANY_SOURCE, 0, status);
    return 0;
}

int popc_combox_mpi::Recv(char* s, int length, pop_connection*& iopeer, bool unlock) {
    MPI::Intercomm communicator;
    int tag = 0;

    // Receiving the data
    MPI::Status status;

    if (is_server() && unlock) {
        tag = 0;
    } else if (is_server()) {
        tag = ((dynamic_cast<pop_mpi_connection*>(iopeer)->get_connection_index() + 1) * 1000) + 1;
    } else {
        tag = ((_node_id + 1) * 1000) + 2;
    }
    MPI::COMM_WORLD.Recv(s, length, MPI_CHAR, MPI_ANY_SOURCE, tag, status);
    dynamic_cast<pop_mpi_connection*>(iopeer)->set_connection_index(status.Get_source());
    return 0;
}

/**
 * Waiting for a new connection from a client
 * @return A pop_connection ojbect representing the connection between the client and the server
 */
pop_connection* popc_combox_mpi::Wait() {
    // Receive interface connection to the MPI Combox
    if (_is_server) {
        pop_mpi_connection* conn = new pop_mpi_connection(this);
        conn->set_communicator(MPI::COMM_WORLD);
        return conn;
    } else {
        return NULL;
    }
}

/**
 * Close the MPI port and
 */
void popc_combox_mpi::Close() {
}

/**
 * Get the protocol name for the MPI combox
 * @param Return "mpi" as the protocol name
 * @return TRUE in any cases
 */
std::string popc_combox_mpi::GetProtocol() {
    return "mpi";
}

/**
 * Return the URL to access this combox. URL is formed like mpi://<port_name>
 * @param accesspoint Formed URL to access this combox under the form mpi://<port_name>
 * @return TRUE if the URL can be formed, FALSE in any other cases.
 */
std::string popc_combox_mpi::GetUrl() {
    return "mpi://" + std::to_string(_node_id);
}

/**
 * Not used in MPI connection
 */
bool popc_combox_mpi::Connect(const char* /*host*/, int /*port*/) {
    return true;
}

/**
 *
 */
bool popc_combox_mpi::disconnect(pop_connection* /*connection*/) {
    return true;
}

/**
 * Check if the combox is instantiated as a server side combox (can receive connection)
 * @return TRUE if the combox is a server-side combox.
 */
bool popc_combox_mpi::is_server() {
    return _is_server;
}

/**
 * Create a new connection associated with this combox
 * @param fd  Not used in this combox
 * @return  A pointer to the newly created connection
 */
pop_connection* popc_combox_mpi::CreateConnection(int /*fd*/) {
    return new pop_mpi_connection(this);
}
