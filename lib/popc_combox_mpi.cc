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
  return combox->is_server();
}








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
const int popc_combox_mpi::POPC_COMBOX_MPI_NEW_CONNECTION_TAG = 1000;
const int popc_combox_mpi::POPC_COMBOX_MPI_KILL_TAG = 1001;
const int popc_combox_mpi::POPC_COMBOX_MPI_NEW_MESSAGE_TAG = 1002;


popc_combox_mpi::popc_combox_mpi() : peer(NULL), index(0), nready(0), isCanceled(false), _is_server(false), _current_tag(0)
{
}

popc_combox_mpi::~popc_combox_mpi()
{
  if(!is_server())
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
  _have_to_get_lock = false;
	_is_server = server;
	if(_is_server){
	  
	  // If MPI_Init was not called yet, we will call it now
	  if(!MPI::Is_initialized()) {
  	  // Init MPI for multithread support
	  	int required_support = MPI_THREAD_SERIALIZED; // Required multiple thread support to allow multiple connection to an object
		  int provided_support = MPI::Init_thread(required_support);
		}
    
    // Get the inter-communicator to communicate with the parent process (Interface)
    /*_parent = MPI::COMM_WORLD.Get_parent();  
	  // Duplicate the communicator for intra brokers communication
	  _broker_intracomm = MPI::COMM_WORLD.Dup();  
	  // Split COMM_WORLD to be able to make Accept on a single process. Otherwise this call must be collective
    _self = MPI::COMM_WORLD.Split(0, 0);
    //_self_for_die = _self.Dup();
    paroc_system::popc_self = _self;
    paroc_system::mpi_has_to_take_lock = false;
    
    // Open the port to receive new connection
    char* port_name = new char[MPI_MAX_PORT_NAME];
    MPI::Open_port(MPI_INFO_NULL, port_name);  
    _broker_port_name.clear();
    _broker_port_name.append(port_name);
    delete [] port_name;
  
    int length; 
    _broker_intracomm.Recv(&length, 1, MPI_INT, 1, 0);
    char* port_name_accept = new char[length+1];
    _broker_intracomm.Recv(port_name_accept, length, MPI_CHAR, 1, 1);
    port_name_accept[length] = '\0';
    _accept_port_name.clear();
    _accept_port_name.append(port_name_accept);
    delete [] port_name_accept;
  
    length = _broker_port_name.length();
    _parent.Send(&length, 1, MPI_INT, 0, 0);
    _parent.Send(_broker_port_name.c_str(), length, MPI_CHAR, 0, 1);  
  
    length = _accept_port_name.length();
    _parent.Send(&length, 1, MPI_INT, 0, 2);
    _parent.Send(_accept_port_name.c_str(), length, MPI_CHAR, 0, 3);  

    // Add accept connection broker to the map of connections
    //MPI::Comm* accept_broker = &_broker_intracomm;
    
    for (int i = 0; i < 10; i++)
      _connections[i] = MPI_COMM_NULL;

    
    // Create initialize requests array. With free space to avoid resizing at every connections
    //_pending_requests = new MPI::Request[POPC_COMBOX_MPI_INITIAL_RSIZE];
    // Create initialize requests header array. WIth free space to avoid resizing at every connections
    //_pending_data = new int[POPC_COMBOX_MPI_INITIAL_RSIZE];    
    for (int i = 0; i < 10; i++)
      _pending_data[i] = 0;
    
    // Initiate the first request. Waiting for message from the accept broker
    _pending_requests[_connection_counter] = _broker_intracomm.Irecv(&_pending_data[_connection_counter], 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG);
    _connection_counter++;   
    // Initiate request to be able to unlock the receive thread at the end
    _pending_requests[_connection_counter] = _self.Irecv(&_pending_data[_connection_counter], 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG);
    _connection_counter++;   
    _request_array_size = 2;
  } else {
    _self = paroc_system::popc_self;
  }*/
  }
  _node_id = MPI::COMM_WORLD.Get_rank();
	return true;
}


/**
 * Get the connection initiated by the Connected call
 * @return 
 */
paroc_connection* popc_combox_mpi::get_connection()
{
  if(peer != NULL)
    return peer;
  printf("return null connection\n");
  return NULL;
}

/**
 * Connect with the saved port name
 * @return TRUE if the connection succeed, FALSE in any other cases
 */
paroc_connection* popc_combox_mpi::reconnect()
{
  //LOG
  /*printf("MPI-COMBOX(%s): Want to reconnect to %s\n", is_server() ? "Server" : "client", _port_name.c_str());  
  if(_port_name.length() > 0){

    MPI::Intercomm broker = MPI::COMM_WORLD.Connect(_port_name.c_str(), MPI_INFO_NULL, 0);

    printf("MPI-COMBOX(%s): Connected to %s\n", is_server() ? "Server" : "client", _port_name.c_str());  
    POPC_MPIConnection* new_connection = new POPC_MPIConnection(this);
    new_connection->setCommunicator(broker);
    
    return new_connection;
  } else {
    printf("MPI-COMBOX(%s): reconnect doesn't have port name\n", is_server() ? "Server" : "client");
    return NULL;
  }*/
  return NULL;
}


bool popc_combox_mpi::Connect(const char *url)
{ 
  /*if (url == NULL) {
		errno=EDESTADDRREQ;
		return false;
	};
	
	// Substring the url to make the two phases connection
	std::string full_port_names(url);
	std::size_t found;
	found = full_port_names.find(POPC_COMBOX_MPI_PROTOCOL_PREFIX_WITH_SLASH);
	if(found != std::string::npos) {
	  full_port_names = full_port_names.substr(found+6);
	}
	found = full_port_names.find(POPC_COMBOX_MPI_ACCESSPOINT_DELIMITER);
	if(found == std::string::npos) {
    return false;
	}

	// Set the two port name for the two phases connection
	std::string accept_broker_port_name = full_port_names.substr(0, found);
	std::string broker_port_name = full_port_names.substr(found+2);
	
//  int size = _self.Get_size();
  
	//printf("MPI-COMBOX(Client): try to connect to accept broker %s // %d\n", accept_broker_port_name.c_str(), size);	
	// Connect to the accept broker 
	//printf("Will connect %d (%s)\n", _self.Get_size(), 	(paroc_system::is_remote_object_process) ? "true" : "false");
	
	// Unlock the local server to be able to to MPI calls
	if(paroc_system::is_remote_object_process){
    unlock_wait(true);
	}
	MPI::Intercomm connection_accept_broker = _self.Connect(accept_broker_port_name.c_str(), MPI_INFO_NULL, 0);
	//printf("Will connected\n");
  int data = 0;
  //printf("MPI-COMBOX(Client): connected to accept broker\n");	  
  connection_accept_broker.Send(&data, 1, MPI_INT, 0, POPC_COMBOX_MPI_NEW_CONNECTION_TAG);
  connection_accept_broker.Disconnect();
  
  // Connect to the real broker
  MPI::Intercomm connection_broker = _self.Connect(broker_port_name.c_str(), MPI_INFO_NULL, 0);
  int connection_index;
  connection_broker.Recv(&connection_index, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG); 
	
	peer = new POPC_MPIConnection(this);
	peer->set_communicator(connection_broker);
	peer->set_connection_index(connection_index);	
	printf("Connected\n");	
	// Let the local server to receive MPI calls again
	if(paroc_system::mpi_has_to_take_lock){	
    paroc_system::mpi_go_wait_cond.lock();
    paroc_system::mpi_go_wait_cond.broadcast();
    paroc_system::mpi_go_wait_cond.unlock();	
  	printf("Connected free receive thread\n");    
	}*/
	
	// Substring the url to make the two phases connection
	std::string full_accesspoint(url);
	std::size_t found;
	found = full_accesspoint.find(POPC_COMBOX_MPI_PROTOCOL_PREFIX_WITH_SLASH);
	if(found != std::string::npos) {
	  full_accesspoint = full_accesspoint.substr(found+6);
	}
	
	peer = new POPC_MPIConnection(this);
	peer->set_communicator(MPI::COMM_WORLD);	
  peer->set_connection_index(atoi(full_accesspoint.c_str()));	
  
	
  return true;
}

/**
 * Unlock the waitany MPI call in the Wait method
 */
bool popc_combox_mpi::unlock_wait(bool rewait)
{
  int data = 0;
  if(rewait){
    data = 1;
  }

  paroc_system::mpi_has_to_take_lock = true;
  MPI::Request req = _self.Isend(&data, 1, MPI_INT, 0, POPC_COMBOX_MPI_KILL_TAG);
  req.Wait();
  
  paroc_system::mpi_unlock_wait_cond.lock();
  paroc_system::mpi_unlock_wait_cond.wait();
  paroc_system::mpi_unlock_wait_cond.unlock();   
  printf("Unlock done\n");
}

void popc_combox_mpi::send_data_length(int length, paroc_connection *conn)
{
  int destination = ((POPC_MPIConnection*)conn)->get_connection_index();    
  if(((POPC_MPIConnection*)conn)->is_asynchronous()) {
    ((POPC_MPIConnection*)conn)->get_communicator().Isend(&length, 1, MPI_INT, destination, 1000);
  } else {
    ((POPC_MPIConnection*)conn)->get_communicator().Send(&length, 1, MPI_INT, destination, 1000);  
  }
}

int popc_combox_mpi::receive_data_length(paroc_connection *conn)
{
  int length = 0;
  MPI::Status status;
  ((POPC_MPIConnection*)conn)->get_communicator().Recv(&length, 1, MPI_INT, MPI_ANY_SOURCE, 1000);
  if(is_server())
    ((POPC_MPIConnection*)conn)->set_connection_index(status.Get_source());    
  return length;
}

/**
 *
 */
bool popc_combox_mpi::connect_and_die(std::string &url)
{ 
  std::string tmp(paroc_broker::accesspoint.GetAccessString());
  printf("Connect and die %s\n", url.c_str());
    
  // Substring the url to make the two phases connection
	std::string full_accesspoint(url);
	std::size_t found;
	found = full_accesspoint.find(POPC_COMBOX_MPI_PROTOCOL_PREFIX_WITH_SLASH);
	if(found != std::string::npos) {
	  full_accesspoint = full_accesspoint.substr(found+6);
	}
	
	int dest = atoi(full_accesspoint.c_str());

	paroc_message_header h(0, 7, INVOKE_SYNC, "DummyMethod");
	
	POPC_MPIConnection* connection = new POPC_MPIConnection(this);
	connection->set_communicator(MPI::COMM_WORLD);
	connection->set_connection_index(dest);
	connection->set_as_asynchronous();	
	
  paroc_buffer_factory* bufferFactory = connection->GetBufferFactory();
  paroc_buffer* tmp_buffer = bufferFactory->CreateBuffer();
  tmp_buffer->Reset();
  tmp_buffer->SetHeader(h);
  tmp_buffer->Send(connection, false);
	
  
  
  // Substring the url to make the two phases connection
  
	/*std::string full_port_names(url);
	std::size_t found;
	
	
	
	/*found = full_port_names.find(POPC_COMBOX_MPI_PROTOCOL_PREFIX_WITH_SLASH);
	if(found != std::string::npos) {
	  full_port_names = full_port_names.substr(found+6);
	}
	found = full_port_names.find(POPC_COMBOX_MPI_ACCESSPOINT_DELIMITER);
	if(found == std::string::npos) {
    return false;
	}*/

	// Set the two port name for the two phases connection
	/*std::string accept_broker_port_name = full_port_names.substr(0, found);

  // Connect to the access broker to terminate it
	MPI::Intercomm connection_accept_broker = _self.Connect(accept_broker_port_name.c_str(), MPI_INFO_NULL, 0);
	int data = 0;
  connection_accept_broker.Send(&data, 1, MPI_INT, 0, POPC_COMBOX_MPI_KILL_TAG);
  connection_accept_broker.Disconnect();  

  printf("Connect and die end %s\n", tmp.substr(tmp.length()-9).c_str());  
  paroc_system::mpi_go_wait_cond.lock();
  paroc_system::mpi_go_wait_cond.broadcast();
  paroc_system::mpi_go_wait_cond.unlock();*/
    

}

int popc_combox_mpi::init_send(paroc_connection *conn, bool unlock)
{
  printf("init_send(%s)\n", is_server() ? "Server" : "Client");
  
  
  MPI::Intercomm comm = ((POPC_MPIConnection*)conn)->get_communicator();
  int data = ((POPC_MPIConnection*)conn)->get_connection_index();
  //printf("MPI-COMBOX(%s) Send init %d\n", is_server() ? "Server" : "client", _current_tag);
  
  
  bool has_been_unlocked = false;
  // If the combox is running on a parallel object and need to contact another parallel object, need to serialize MPI Calls.   
	if(paroc_system::is_remote_object_process && unlock){
    std::string tmp(paroc_broker::accesspoint.GetAccessString());	
    printf("Send init will unlock receive thread\t %s\n", tmp.substr(tmp.length()-9).c_str());		
    unlock_wait(true);
    has_been_unlocked = true;
	}        
  comm.Send(&data, 1, MPI_INT, 0, POPC_COMBOX_MPI_NEW_MESSAGE_TAG);
  if(has_been_unlocked){	
    std::string tmp(paroc_broker::accesspoint.GetAccessString());			
    paroc_system::mpi_go_wait_cond.lock();
    paroc_system::mpi_go_wait_cond.broadcast();
    paroc_system::mpi_go_wait_cond.unlock(); 	
    printf("Send init free receive thread\t %s\n", tmp.substr(tmp.length()-9).c_str());		
	}
  
  _current_tag++;
}

int popc_combox_mpi::Send(const char *s, int length)
{
  if(peer == NULL) {
    return 0;
  }
  
  
    
	//MPI::Intercomm communicator = peer->get_communicator();  
  //communicator.Send(s, length, MPI_CHAR, _rank, 0);	
  // LOG
	//printf("MPI-COMBOX(%s): sent smth: %d\n", is_server() ? "Server" : "client", length);    
	return 0;
}

int popc_combox_mpi::Send(const char *s, int length, paroc_connection *conn, bool unlock)
{

  if(conn == NULL)
    return Send(s, length);
    
  int tag;
  
  // Client
  if(!is_server()){
    if(unlock){
      //printf("Client set tag\n");
      ((POPC_MPIConnection*)conn)->set_current_tag(((_node_id+1)*1000)+1);
      tag = 0;
    } else {
      //printf("Client get tag\n");
      tag = ((POPC_MPIConnection*)conn)->get_current_tag();      
    }
  } else {  // Server
    //printf("Server get tag\n");
    tag = ((((POPC_MPIConnection*)conn)->get_connection_index()+1)*1000)+2;      
  }

    
//  bool has_been_unlocked = false;
  // If the combox is running on a parallel object and need to contact another parallel object, need to serialize MPI Calls.   
	/*if(paroc_system::is_remote_object_process && unlock){
    std::string tmp(paroc_broker::accesspoint.GetAccessString());	
    printf("Send will unlock receive thread\t %s\n", tmp.substr(tmp.length()-9).c_str());		
    unlock_wait(true);
    has_been_unlocked = true;
	} */       
 
//	MPI::Intercomm communicator = ((POPC_MPIConnection*)conn)->get_communicator();
//	int tag = ((POPC_MPIConnection*)conn)->get_connection_index();
//	communicator.Send(s, length, MPI_CHAR, , tag);	


  int destination = ((POPC_MPIConnection*)conn)->get_connection_index();

  if(tag == 0 && is_server())
    tag = destination+10;

  if(((POPC_MPIConnection*)conn)->is_asynchronous()) {
    printf("asynchronous\n");
  	MPI::COMM_WORLD.Isend(s, length, MPI_CHAR, destination, tag);  
  //  ((POPC_MPIConnection*)conn)->get_communicator().Send(&length, 1, MPI_INT, destination, 1000);
  } else {
  	MPI::COMM_WORLD.Send(s, length, MPI_CHAR, destination, tag);  
  //  ((POPC_MPIConnection*)conn)->get_communicator().Isend(&length, 1, MPI_INT, destination, 1000);  
  }  
  //printf("Send(%s) from %d to %d[%d] size %d\n", is_server() ? "Server" : "Client", _node_id, destination, tag, length);  		
//	if(!unlock)
//    ((POPC_MPIConnection*)conn)->unset_current_tag();
	
	/*if(has_been_unlocked){	
    paroc_system::mpi_go_wait_cond.lock();
    paroc_system::mpi_go_wait_cond.broadcast();
    paroc_system::mpi_go_wait_cond.unlock();
    std::string tmp(paroc_broker::accesspoint.GetAccessString());	    
    printf("Send free receive thread\t %s\n", tmp.substr(tmp.length()-9).c_str());	    
	}	*/
	
	return 0;
}

int popc_combox_mpi::Recv(char *s, int length, bool unlock)
{

  if(peer == NULL) {
    return -1;
  }
  MPI::Status status;  
	MPI::Intercomm communicator = peer->get_communicator(); 

  bool has_been_unlocked = false;

  // If the combox is running on a parallel object and need to contact another parallel object, need to serialize MPI Calls.   
	/*if(paroc_system::is_remote_object_process && unlock){
	  std::string tmp(paroc_broker::accesspoint.GetAccessString());
    printf("Recv will unlock receive thread\t %s\n", tmp.substr(tmp.length()-9).c_str());		
    unlock_wait(true);
    has_been_unlocked = true;
	} */       	   
//  communicator.Recv(s, length, MPI_CHAR, 0, 0, status);   

  
  MPI::COMM_WORLD.Recv(s, length, MPI_CHAR, MPI_ANY_SOURCE, 0, status);    
  
/*	if(has_been_unlocked){	
    std::string tmp(paroc_broker::accesspoint.GetAccessString());			
    paroc_system::mpi_go_wait_cond.lock();
    paroc_system::mpi_go_wait_cond.broadcast();
    paroc_system::mpi_go_wait_cond.unlock(); 	
    printf("Recv free receive thread\t %s\n", tmp.substr(tmp.length()-9).c_str());		
	}	  */
	return 0;
}

int popc_combox_mpi::Recv(char *s, int length, paroc_connection *&iopeer, bool unlock)
{

	MPI::Intercomm communicator;
	POPC_MPIConnection *connection;  
	int tag = 0;
	/*
	bool has_been_unlocked = false;
	*/

	  
	  
/*	if(paroc_system::is_remote_object_process && unlock){
	  std::string tmp(paroc_broker::accesspoint.GetAccessString());
    printf("Recv will unlock receive thred\t %s\n", tmp.substr(tmp.length()-9).c_str());		
    unlock_wait(true);
    has_been_unlocked = true;
	}	  */
	// Receiving the data
  MPI::Status status;
  //printf("MPI-COMBOX(%s): Wanna receive (size:%d tag:%d)\n",is_server() ? "Server" : "client", length, tag);
//  communicator.Recv(s, length, MPI_CHAR, 0, tag, status);


  if(is_server() && unlock) {
    tag = 0;
  } else if(is_server()) {
    tag = ((((POPC_MPIConnection*)iopeer)->get_connection_index()+1)*1000)+1;
  } else {
    tag = ((_node_id+1)*1000)+2;
  }
  printf("Recv(%s/%d) %d tag:%d\n", is_server() ? "Server" : "Client", _node_id, length, tag);   
  MPI::COMM_WORLD.Recv(s, length, MPI_CHAR, MPI_ANY_SOURCE, tag, status);    
  
  /*if(tag == 0) {
    ((POPC_MPIConnection*)iopeer)->set_current_tag(status.Get_source()+10);  
  } */ 
 

  /*if(!unlock && ((POPC_MPIConnection*)iopeer)->is_tag_set()){
    tag = ((POPC_MPIConnection*)iopeer)->get_current_tag();
    printf("Recv(%s/%d) %d tag:%d\n", is_server() ? "Server" : "Client", _node_id, length, tag);    
    MPI::COMM_WORLD.Recv(s, length, MPI_CHAR, MPI_ANY_SOURCE, tag, status);      
    ((POPC_MPIConnection*)iopeer)->unset_current_tag();
  } else {
    MPI::COMM_WORLD.Recv(s, length, MPI_CHAR, MPI_ANY_SOURCE, 0, status);      
    tag = status.Get_tag();
    printf("Recv(%s/%d) %d tag:%d\n", is_server() ? "Server" : "Client", _node_id, length, tag);    
    if(unlock){
      ((POPC_MPIConnection*)iopeer)->set_current_tag(status.Get_source()+10);    
    }
  }*/

  printf("Recv(%s/%d) from  %d[%d] - size %d\n", is_server() ? "Server" : "Client", _node_id, status.Get_source(), status.Get_tag(), length);  
  ((POPC_MPIConnection*)iopeer)->set_connection_index(status.Get_source());
  
  //if(is_server() && tag != 0)
    //((POPC_MPIConnection*)iopeer)->set_current_tag(0);
/*
	if(has_been_unlocked){	
    paroc_system::mpi_go_wait_cond.lock();
    paroc_system::mpi_go_wait_cond.broadcast();
    paroc_system::mpi_go_wait_cond.unlock(); 	
	  std::string tmp(paroc_broker::accesspoint.GetAccessString());
    printf("Recv free receive thred\t %s\n", tmp.substr(tmp.length()-9).c_str());		    
	}	  */
	return 0;
}

/**
 * Waiting for a new connection from a client
 * @return A paroc_connection ojbect representing the connection between the client and the server
 */
paroc_connection* popc_combox_mpi::Wait()
{ 
  // Receive interface connection to the MPI Combox
	if(_is_server){	
	  POPC_MPIConnection* conn = new POPC_MPIConnection(this);
    conn->set_communicator(MPI::COMM_WORLD);  
    return conn; 
    /*MPI::Status status;
    std::string tmp(paroc_broker::accesspoint.GetAccessString());
    printf("MPI-COMBOX(Server): Waiting %d, %s\n", _request_array_size, tmp.substr(tmp.length()-9).c_str());      
    index = MPI::Request::Waitany(_request_array_size, _pending_requests, status); 
    
   
   
    printf("MPI-COMBOX(Server): msg %d, %s\n", _request_array_size, tmp.substr(tmp.length()-9).c_str());            
     // printf("MPI-COMBOX(server): Got message from connection[%d] tag %d\n", index, status.Get_tag());		
      if(index != MPI::UNDEFINED){
        // Asking for a new connection on the broker
        if(status.Get_tag() == POPC_COMBOX_MPI_NEW_CONNECTION_TAG){
          // Waiting for the new connection
          MPI::Intercomm new_connection = _self.Accept(_broker_port_name.c_str(), MPI_INFO_NULL, 0);
          // Send the connection ID to the client
          new_connection.Send(&_connection_counter, 1, MPI_INT, 0, 0);
          // Add the communicators to the map of connected communicators
          _connections[_connection_counter] = new_connection;       
          // Create a new request to be able to receive data from the new client
          _pending_requests[_connection_counter] =  _connections[_connection_counter].Irecv(&_pending_data[_connection_counter], 1, MPI_INT, MPI_ANY_SOURCE, POPC_COMBOX_MPI_NEW_MESSAGE_TAG);
          // Increment the connection ID counter and the size of the request array
          _connection_counter++;         
          _request_array_size++;
          // Create a dummy connection to pass
          POPC_MPIConnection* conn = new POPC_MPIConnection(this);
          conn->set_as_connection_init();    
          if(_connection_counter == 3)
            conn->set_as_wait_unlock();
          // Reactivate the request just receive to be able to receive new message  
          _pending_requests[index] = _broker_intracomm.Irecv(&_pending_data[index], 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG);                         
          
          return conn;
        } else if (status.Get_tag() == POPC_COMBOX_MPI_KILL_TAG) {
          paroc_system::mpi_unlock_wait_cond.lock();
          paroc_system::mpi_unlock_wait_cond.broadcast();
          paroc_system::mpi_unlock_wait_cond.unlock() ;                   
         	          	 	
          printf("Receive unlock %s\n", tmp.substr(tmp.length()-9).c_str());
          POPC_MPIConnection* conn = new POPC_MPIConnection(this);
          conn->set_as_connection_init();  
          conn->set_as_wait_unlock();                            
          if(_pending_data[index] == 1){
            printf("Rewait on unlock %s // %d\n", tmp.substr(tmp.length()-9).c_str(), index);
            _pending_requests[index] = _self.Irecv(&_pending_data[index], 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG);
          }         
          if(paroc_system::mpi_has_to_take_lock) {
            paroc_system::mpi_go_wait_cond.lock();
            paroc_system::mpi_go_wait_cond.wait();
            paroc_system::mpi_go_wait_cond.unlock();
            paroc_system::mpi_has_to_take_lock = false;              	       
            printf("Receive thread go again %s\n", tmp.substr(tmp.length()-9).c_str());
          }          
          return conn;          
        } else {
          int next_tag = status.Get_tag() + 1;
          //printf("MPI-COMM-WAIT: Got New message. Next tag %d\n", next_tag);            
          // Return the connection to receive the message
          POPC_MPIConnection* conn = new POPC_MPIConnection(this);
          conn->set_communicator(_connections[index]);
          conn->set_connection_index(_pending_data[index]);
          // Reactivate the request to receive new messages
          _pending_requests[index] = _connections[index].Irecv(&_pending_data[index], 1, MPI_INT, MPI_ANY_SOURCE, POPC_COMBOX_MPI_NEW_MESSAGE_TAG);      
          return conn;
        }
      }*/
      return NULL;
	} else {
	  return NULL;
	}
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
  /*if(is_server()){
    if(!MPI::Is_initialized() && _broker_port_name.length() > 0) {
      printf("MPI-COMBOX(%s): Port is free\n", is_server() ? "Server" : "client");
      if(_is_port_open){
        MPI::Close_port(_broker_port_name.c_str());
        _is_port_open = false;
        _broker_port_name.clear();
      }
    }
  } else {
    // DecRef on the other side
  }*/
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
  /*if(_broker_port_name.length() <= 0 || _accept_port_name.length() <= 0)
    return false;*/
  
  // Form the URL with protocol and port_name  
  POPString protocol;
  GetProtocol(protocol);
  char url[1024];
  sprintf(url, "%s://%d", (const char*)protocol, _node_id);
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
/*  if(connection != NULL) {
    ((POPC_MPIConnection*)connection)->reset();
  } else if (connection == NULL && peer != NULL) {
    peer->reset();
  }*/
  //_hasCommunicator = false;
}

/**
 * Check if the combox is instantiated as a server side combox (can receive connection)
 * @return TRUE if the combox is a server-side combox. 
 */
bool popc_combox_mpi::is_server()
{
  return _is_server;
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

