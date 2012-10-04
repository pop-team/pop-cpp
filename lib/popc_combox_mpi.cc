/**
 * @author 	Valentin Clement
 * @date		2012/09/25
 * @brief	Implementation of the combox using MPI Communication layer
 */


#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>


#include "popc_combox_mpi.h"




POPC_MPIConnection::POPC_MPIConnection(paroc_combox *cb): _hasCommunicator(false), paroc_connection(cb), _comm_index(0)
{
	signal(SIGPIPE, SIG_IGN);
}

POPC_MPIConnection::POPC_MPIConnection(POPC_MPIConnection &me): _hasCommunicator(false), paroc_connection(me.GetCombox(), me.GetBufferFactory())
{
  setCommunicator(me.getCommunicator());
}

/**
 * MPI Connection destructor. Free the communicator if it has been set. 
 */
POPC_MPIConnection::~POPC_MPIConnection(){
  if(hasCommunicator())
    _communicator.Free();
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
void POPC_MPIConnection::setCommunicator(MPI::Intercomm communicator)
{
  _hasCommunicator = true;
  _communicator = communicator;
}

/**
 * Get the inter-communicator for the connection
 * @return A MPI inter-communicator
 */
MPI::Intercomm POPC_MPIConnection::getCommunicator()
{
  return _communicator;
}

/**
 * Check if the communicator has been set
 * @return TRUE if the communicator is set. FALSE in any other cases. 
 */
bool POPC_MPIConnection::hasCommunicator()
{
  return _hasCommunicator;
}

/**
 * Set the index associated with this connection inside a combox
 * @param value Integer value representing the index of the connection in the combox
 */
void POPC_MPIConnection::setCommunicatorIndex(int value)
{
  _comm_index = value;
}

/**
 * Reset the connection. Disconnect the communicator and free it.
 */
void POPC_MPIConnection::reset()
{
  if(_hasCommunicator){
   // printf("MPI-COMBOX(%s): before MPI.Disconnect() %d\n", (is_server())?"Server":"Client", _comm_index);  
    //_communicator.Disconnect();
    //printf("MPI-COMBOX(%s): after MPI.Disconnect() %d\n", (is_server())?"Server":"Client", _comm_index);
  } else {
    printf("MPI-COMBOX(%s): reset() connection as no communicator\n", (is_server())?"Server":"Client");
  }
  _hasCommunicator = false; 
}

/**
 * Check if the associated combox is a server or client combox
 * @return TRUE if the associated combox is a server. FALSE if the associated combox is a client
 */
bool POPC_MPIConnection::is_server()
{
  return combox->is_server();
}



/**
 * 
 * POPC_COMBOX_MPI IMPLEMENTATION
 * 
 */
 
 
// Constant declaration
const char* popc_combox_mpi::POPC_COMBOX_MPI_PROTOCOL_PREFIX = "mpi://"; 

popc_combox_mpi::popc_combox_mpi() : peer(NULL), index(0), nready(0), isCanceled(false), _isServer(false), _rank(-1), _comm_counter(1)
{
}

popc_combox_mpi::~popc_combox_mpi()
{
	Close();
}

/*bool popc_combox_mpi::hasCommunicator()
{
  return _hasCommunicator;
}

void popc_combox_mpi::setCommunicator(MPI::Intercomm comm)
{     
  _communicator = comm;
  _hasCommunicator = true;
}

MPI::Intercomm popc_combox_mpi::getCommunicator()
{
  return _communicator;
}
*/


/**
 * Create a new MPI Combox. Server combox will open a MPI port to receive new connection. 
 */
bool popc_combox_mpi::Create(char* host, int port, bool server)
{
	
	Close(); 
	_isServer = server;

//	printf("MPI-COMBOX(%s): Creation\n", (server)?"Server":"Client");

	if(_isServer){
	  // If MPI_Init was not called yet, we will call it now
	  if(!MPI::Is_initialized()) {
	  
  	  // Init MPI for multithread support
	  	int required_support = MPI_THREAD_MULTIPLE; // Required multiple thread support to allow multiple connection to an object
		  int provided_support = MPI::Init_thread(required_support);

		  // Get the inter-communicator to communicate with the parent process (Interface)
	  	//static MPI::Intercomm parent = MPI::COMM_WORLD.Get_parent();  
		}
			  
		if(host != NULL){
  		_port_name.append(host);			
		} else {
      // Open a port to be able to be contacted by interfaces
		  char port_name[MPI_MAX_PORT_NAME]; 		
		  MPI::Open_port(MPI_INFO_NULL, port_name);
		  _is_port_open = true;
		  _port_name.append(port_name);
		  int length = _port_name.length();
		  printf("MPI-COMBOX(Server): MPI port open\n"); 
		}
	}
	
	// Get the rank of the current process
	_rank = MPI::COMM_WORLD.Get_rank();
		
	return true;
}


/**
 * Get a connection to the port saved during the Create call
 * @return A new MPI connection, connected to the end point through a new communicator. 
 */
paroc_connection* popc_combox_mpi::get_connection()
{
  //LOG
  printf("MPI-COMBOX(%s): Want to get a connection to %s\n", is_server() ? "Server" : "client", _port_name.c_str());  
  if(_port_name.length() > 0){
    // Try to connect to the end point
    MPI::Intercomm broker = MPI::COMM_WORLD.Connect(_port_name.c_str(), MPI_INFO_NULL, 0);

    printf("MPI-COMBOX(%s): Connected to %s\n", is_server() ? "Server" : "client", _port_name.c_str());  
    POPC_MPIConnection* new_connection = new POPC_MPIConnection(this);
    new_connection->setCommunicator(broker);
    
    return new_connection;
  } else {
    printf("MPI-COMBOX(%s): reconnect doesn't have port name\n", is_server() ? "Server" : "client");
    return NULL;
  }  
}
/**
 * Connect with the saved port name
 * @return TRUE if the connection succeed, FALSE in any other cases
 */
paroc_connection* popc_combox_mpi::reconnect()
{
  //LOG
  printf("MPI-COMBOX(%s): Want to reconnect to %s\n", is_server() ? "Server" : "client", _port_name.c_str());  
  if(_port_name.length() > 0){

    MPI::Intercomm broker = MPI::COMM_WORLD.Connect(_port_name.c_str(), MPI_INFO_NULL, 0);

    printf("MPI-COMBOX(%s): Connected to %s\n", is_server() ? "Server" : "client", _port_name.c_str());  
    POPC_MPIConnection* new_connection = new POPC_MPIConnection(this);
    new_connection->setCommunicator(broker);
    
    return new_connection;
  } else {
    printf("MPI-COMBOX(%s): reconnect doesn't have port name\n", is_server() ? "Server" : "client");
    return NULL;
  }
}


bool popc_combox_mpi::Connect(const char *url)
{
  if (url == NULL) {
		errno=EDESTADDRREQ;
		return false;
	}
  
 	char *host;
	while (isspace(*url)) url++;

	const char searchPattern[] = "mpi://";
	char * searchResult;
	if (strncmp(url, "mpi://", 6) == 0){
		host = strdup(url+6);
	} else {
	  host = strdup(url);
	}

  //MPI::Intercomm broker = MPI::COMM_WORLD.Connect(host, MPI_INFO_NULL, 0);
  //printf("Connected to %s\n", host);
  _port_name.clear();
  _port_name.append(host);
  
  if(peer == NULL)
    peer = new POPC_MPIConnection(this);
  //peer->setCommunicator(broker);
  //setCommunicator(broker);
  
  delete [] host;

  return true;


	/*

	*s=0;
	bool ret= Connect(host,port);
	free(host);
	if (ret) peer->sockfd=sockfd;
	return ret;*/
}

int popc_combox_mpi::Send(const char *s, int length)
{
  if(peer == NULL) {
    return 0;
  }
  
  
    
	MPI::Intercomm communicator = peer->getCommunicator();  
  communicator.Send(s, length, MPI_CHAR, _rank, 0);	
  // LOG
	//printf("MPI-COMBOX(%s): sent smth: %d\n", is_server() ? "Server" : "client", length);    
	return 0;
}

int popc_combox_mpi::Send(const char *s, int length, paroc_connection *conn)
{
  if(conn == NULL)
    return Send(s, length);

  //printf("MPI-COMBOX(%s) - Send conn has comm ? %s\n", is_server() ? "Server" : "client", ((POPC_MPIConnection*)conn)->hasCommunicator() ? "true" : "false");
    

	MPI::Intercomm communicator = ((POPC_MPIConnection*)conn)->getCommunicator();
//  communicator.Send(s, length, MPI_CHAR, _rank, 0);	
  MPI::Request mpi_reuqest = communicator.Isend(s, length, MPI_CHAR, _rank, 0);
  // LOG
	//printf("MPI-COMBOX(%s): sent smth: %d\n", is_server() ? "Server" : "client", length);  

	return 0;
}

int popc_combox_mpi::Recv(char *s, int length)
{
  if(peer == NULL) {
    return -1;
  }
  
  MPI::Status status;  
	MPI::Intercomm communicator = peer->getCommunicator();    
  communicator.Recv(s, length, MPI_CHAR, 0, 0, status);    
  
	return 0;
}

int popc_combox_mpi::Recv(char *s, int length, paroc_connection *&iopeer)
{
	MPI::Intercomm communicator;
	POPC_MPIConnection *connection;  
	
	// Get a new connection from a client if connection is null or has no communicator
  if(iopeer == NULL || !((POPC_MPIConnection*)iopeer)->hasCommunicator()){
    // Wait for the new connection
    connection = (POPC_MPIConnection*)Wait();  
    if(connection == NULL)
      return -1;
    // Get the MPI Communicator from the new connection. It will be used to receive the data and disconnect the connection later. 
    communicator = connection->getCommunicator();
    ((POPC_MPIConnection*)iopeer)->setCommunicator(communicator);
  } else if(iopeer != NULL) {
    // Use the previous communicator
    communicator = ((POPC_MPIConnection*)iopeer)->getCommunicator();
  }
	  
	// Receiving the data
  MPI::Status status;
  communicator.Recv(s, length, MPI_CHAR, 0, 0, status);

	return 0;
}

/**
 * Waiting for a new connection from a client
 * @return A paroc_connection ojbect representing the connection between the client and the server
 */
paroc_connection* popc_combox_mpi::Wait()
{
  // If the MPI port is not open already, no connection cat be accepted
  if(_port_name.length() <= 0) {
    return NULL;
  }
  
  // Receive interface connection to the MPI Combox
	if(_isServer){
		printf("MPI-COMBOX(Server): Waiting for client connection on %s. Connection %d\n", _port_name.c_str(), _comm_counter);
		
    // Wait for new connection
    MPI::Intercomm client = MPI::COMM_WORLD.Accept(_port_name.c_str(), MPI_INFO_NULL, 0);

		printf("MPI-COMBOX(Server): New client connected. Connection %d\n", _comm_counter);

    // Create a new connection and set its communicator   
    POPC_MPIConnection* new_conn = new POPC_MPIConnection(this);
    new_conn->setCommunicator(client);
    new_conn->setCommunicatorIndex(_comm_counter);    
    _comm_counter++;
    return new_conn;
    
	} else {
	  return NULL;
	}
	return NULL;
}

/**
 * Close and delete the combox
 */
void popc_combox_mpi::Destroy()
{
  Close();
  delete this;  
}

/** 
 * Close the MPI port and 
 */
void popc_combox_mpi::Close()
{
  if(!MPI::Is_initialized() && _port_name.length() > 0) {
  
    printf("MPI-COMBOX(%s): Port is free\n", is_server() ? "Server" : "client");
    if(_is_port_open){
      MPI::Close_port(_port_name.c_str());
      _is_port_open = false;
      _port_name.clear();
    }
  }
}

/**
 * Get the protocol name for the MPI combox
 * @param Return "mpi" as the protocol name
 * @return TRUE in any cases
 */
bool popc_combox_mpi::GetProtocol(POPString& protocolName)
{
	protocolName="mpi";
	return true;
}


/**
 * Return the URL to access this combox. URL is formed like mpi://<port_name>
 * @param accesspoint Formed URL to access this combox under the form mpi://<port_name>
 * @return TRUE if the URL can be formed, FALSE in any other cases. 
 */
bool popc_combox_mpi::GetUrl(POPString& accesspoint)
{
  if(_port_name.length() <= 0)
    return false;
  
  // Form the URL with protocol and port_name  
  POPString protocol;
  GetProtocol(protocol);
  char url[1024];
  sprintf(url, "%s://%s", (const char*)protocol, _port_name.c_str());
  accesspoint = url;
	return true;
}

/**
 * 
 */
bool popc_combox_mpi::Connect(const char *host, int port)
{
  
}

/**
 *
 */
bool popc_combox_mpi::disconnect(paroc_connection *connection)
{ 
  if(connection != NULL) {
    ((POPC_MPIConnection*)connection)->reset();
  } else if (connection == NULL && peer != NULL) {
    peer->reset();
  }
  //_hasCommunicator = false;
}

/**
 * Check if the combox is instantiated as a server side combox (can receive connection)
 * @return TRUE if the combox is a server-side combox. 
 */
bool popc_combox_mpi::is_server()
{
  return _isServer;
}

/**
 * Create a new connection associated with this combox
 * @param fd  Not used in this combox
 * @return  A pointer to the newly created connection
 */
paroc_connection* popc_combox_mpi::CreateConnection(int fd)
{
	return new POPC_MPIConnection(this);
}

