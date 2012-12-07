/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/11/30
 * @brief Implementation of base POPC_Group_interface class. This class is the base class for interface-side of a group 
 *        parallel object. A group parallel object is a set of parallel object that can be called in a single or collective way.
 *
 *
 */

#include <mpi.h>
#include <string.h>

#include "popc_group_interface.h"
#include "paroc_combox_factory.h"
#include "paroc_exception.h"
#include "paroc_broker.h"
#include "popc_combox_uds.h"
#include "paroc_system.h"

/**
 * Base constructor
 */
POPC_GroupInterface::POPC_GroupInterface() : _popc_is_initialized(false), _popc_is_finalized(false), _popc_nb_parallel_object(0), 
  _popc_default_rank_for_single_call(0)
{
}


/**
 * Base destructor. Will finalized the object if finalize() was not called before.
 */
POPC_GroupInterface::~POPC_GroupInterface()
{
  if(!is_finalized()) {
    finalize();
  }
}
  
/**
 * Initialized the parallel object managed by this interface
 * @param nb  Number of parallel object to be managed by this interface
 * @return TRUE if the initialization is done successfully. FALSE if already initialized or in any other cases.
 */
bool POPC_GroupInterface::initialize(int nb)
{
  if(is_initialized()) {
    return false;
  }

  if(nb <= 0) {
    return false;
  }

  std::string class_name = get_class_name();
  
  POPString codefile; 
  od.getExecutable(codefile); 
  
  if(codefile.Length() <= 0) {
    printf("POP-C++ Error: Cannot allocate group of objects because executbale is not specified\n"); 
    return false;
  }

  // Contact the local POP-C++ MPI Interconnector to create XMP process
  int rank = paroc_system::popc_local_mpi_communicator_rank;

  char* local_interconnector_address = new char[15];
  snprintf(local_interconnector_address, 15, "uds_%d.0", rank);  

  paroc_combox_factory* combox_factory = paroc_combox_factory::GetInstance();
  if(combox_factory == NULL) {
    paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "ComboxFactory NULL"); 
  }

  _popc_combox = combox_factory->Create("uds"); 
  if(_popc_combox == NULL) {
    paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "Combox NULL"); 
  }

  _popc_buffer = _popc_combox->GetBufferFactory()->CreateBuffer();
  
  if(!_popc_combox->Create(local_interconnector_address, false)) {
    paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "Can't connect to local interconnector"); 
  }

  if(!_popc_combox->Connect(local_interconnector_address)) {
    paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "Can't connect to local interconnector"); 
  }

  delete local_interconnector_address; 

  paroc_message_header header(0, 210000, INVOKE_SYNC, "_allocation"); 
  _popc_buffer->Reset();
  _popc_buffer->SetHeader(header); 

  // Prepare information for the allocation
  POPString objectname(class_name); 
  _popc_buffer->Push("objectname", "POPString", 1);
  _popc_buffer->Pack(&objectname, 1); 
  _popc_buffer->Pop();

  POPString ps_codefile(codefile.c_str()); 
  _popc_buffer->Push("codefile", "POPString", 1);
  _popc_buffer->Pack(&ps_codefile, 1); 
  _popc_buffer->Pop();

  _popc_buffer->Push("objectnb", "int", 1);
  _popc_buffer->Pack(&nb, 1); 
  _popc_buffer->Pop();

  paroc_connection* _popc_connection = _popc_combox->get_connection();
  
  popc_send_request(_popc_buffer, _popc_connection); 
  popc_recv_response(_popc_buffer, _popc_connection); 

  POPString objectaddress;
  _popc_buffer->Push("objectaddress", "POPString", 1);
  _popc_buffer->UnPack(&objectaddress, 1); 
  _popc_buffer->Pop();

  _popc_is_initialized = true;
  
  construct_remote_object();
  
  return true; 
}

POPC_GroupInterface& POPC_GroupInterface::merge(POPC_GroupInterface& other)
{
  printf("POP-C++ Error: GROUP MERGING IS NOT IMPLEMENTED YET\n"); 
}

/**
 * Finalize the parallel object managed by this interface
 * @return TRUE if the finalization is done successfully. FALSE if already finalized or in any other cases.
 */
bool POPC_GroupInterface::finalize()
{
  if(is_finalized()) {
    return false;
  }
  
  // Terminate the processes
  paroc_message_header h(0, 2, INVOKE_SYNC, "DecRef");
	_popc_buffer->Reset();
	_popc_buffer->SetHeader(h);


	paroc_connection* connection = _popc_combox->get_connection();

	popc_send_request(_popc_buffer, connection);  
	popc_recv_response(_popc_buffer, connection); 
  
  _popc_buffer->Destroy();
  _popc_combox->Close(); 
  _popc_is_finalized = true; 
  return true;
}

/**
 * Send a request to the end point
 * @param buffer      Buffer filled with the request header and data load
 * @param connection  Connection used to send the request. 
 */
void POPC_GroupInterface::popc_send_request(paroc_buffer* buffer, paroc_connection* connection)
{
  if (!buffer->Send((*_popc_combox), connection)) {
    printf("ERROR: Problem while sending request\n"); 
	  paroc_exception::paroc_throw_errno();
	}  	
}

/**
 * Receive a response from the end point
 * @param buffer      Empty buffer to receive the request header and its data load
 * @param connection  Connection used to receive the response. 
 */
void POPC_GroupInterface::popc_recv_response(paroc_buffer* buffer, paroc_connection* connection)
{
	if (!buffer->Recv((*_popc_combox), connection)) {
    paroc_exception::paroc_throw_errno();	
	}
	paroc_buffer::CheckAndThrow(*buffer);  
}

/**
 * Set the default rank for non-collective call. This rank is used for all non-collective calls and can be changed at any time. 
 * @param rank  Rank between 0 and (group size - 1)
 */
void POPC_GroupInterface::set_default_rank(int rank)
{
  _popc_default_rank_for_single_call = rank;
}

/**
 * Get the current default rank for non-collective calls
 * @return Integer value representing the rank between 0 and (group size - 1)
 */
int POPC_GroupInterface::get_default_rank()
{
  return _popc_default_rank_for_single_call; 
}

/**
 * Return the class name of the current interface. Overloaded by child class. 
 * @return Pointer to a string containing the class name.
 */
char* POPC_GroupInterface::get_class_name() 
{
  return (char*)"";
}
  
/**
 * Get the number of parallel object managed by this interface. 
 * @return Integer value representing the number of parallel object managed by this interface. 
 */
int POPC_GroupInterface::get_group_size()
{
  return _popc_nb_parallel_object;
}

/**
 * Check if the parallel objects managed by this interface have been initialized. 
 * @return TRUE if the initialization was done. FALSE if not initialized. 
 */
bool POPC_GroupInterface::is_initialized()
{
  return _popc_is_initialized;
}

/**
 * Check if the parallel objects managed by this interface have been finalized. 
 * @return TRUE if the finalization was done. FALSE if not finalized. 
 */
bool POPC_GroupInterface::is_finalized()
{
  return _popc_is_finalized;
}