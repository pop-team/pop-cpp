/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief Declaration of the base class POPC_AllocatorFactory. The allocator factory allows to provide the right allocator for 
 *        parallel object allocation depending the lower layer (SSH, MPI, POP-C++ MPI Interconnector ...). 
 *
 *
 */

#include "popc_allocator_tcpip.h"

#include "paroc_system.h"
#include "paroc_exception.h"
#include "paroc_combox.h"
#include "paroc_combox_factory.h"
#include "paroc_broker.h"

/**
 * Allocator over TCP/IP with local mechanism constructor
 */ 
POPC_Allocator_tcpip_local::POPC_Allocator_tcpip_local()
{
}

/**
 * Allocator over TCP/IP with local mechanism destrcutor
 */ 
POPC_Allocator_tcpip_local::~POPC_Allocator_tcpip_local()
{
}

/**
 * Allocate a single object by using the TCP/IP protocol with a local allocation mechanism
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @return A string representation of the access-point
 */
POPString POPC_Allocator_tcpip_local::allocate(POPString& objectname, paroc_od& od)
{
    
    POPString p;
    od.getProtocol(p);

    // Get object description important for this kind 
    int node = od.get_node(); // Defined the node on which the parallel object is allocated
    int core = od.get_core(); // Defined the core on which the parallel object is allocated

    /* 
     * If od local is set, the parallel object will be allocated on the local POP-C++ MPI Interconnector. If od.node is not defined,
     * the parallel object is also allocated on the local node 
     */
    if(od.IsLocal() || node == -1) {
      node = paroc_system::pop_current_local_address;
    }

    // Get the executable path name
    POPString codefile;
    od.getExecutable(codefile);

    // If od.executable is not defined, throw an exception as the parallel object couldn't be allocated
    if(codefile.Length() <= 0) {
      printf("POP-C++ Error: Code file executable path is NULL ! Abort !\n"); 	
      paroc_exception::paroc_throw(POPC_NO_PROTOCOL, objectname);	  
    }

    /**
     * POP-C++ for the K Computer
     * Create a combox to contact the MPI Communicator process to allocate the new parallel object.
     */
    paroc_combox_factory* combox_factory = paroc_combox_factory::GetInstance();
    if (combox_factory == NULL) 
      paroc_exception::paroc_throw(POPC_NO_PROTOCOL, objectname);

    paroc_combox* allocating_combox = combox_factory->Create("tcpip");
	
    if(allocating_combox == NULL)
      paroc_exception::paroc_throw(POPC_NO_PROTOCOL, objectname);

    paroc_buffer* allocating_buffer = allocating_combox->GetBufferFactory()->CreateBuffer();  
    const char ip_address[14] = "160.98.21.133";
    int port;
    
    //simulate
    port = 45315;
            
    char* local_address = new char[30];
    snprintf(local_address, 30, "%s.%d", ip_address, port);

    if(!allocating_combox->Create(local_address, false) || !allocating_combox->Connect(local_address))
      paroc_exception::paroc_throw(POPC_NO_PROTOCOL, objectname);

          paroc_message_header header(20, 200000, INVOKE_SYNC,"_allocate");
          allocating_buffer->Reset();
          allocating_buffer->SetHeader(header);

    allocating_buffer->Push("objectname", "POPString", 1);
    allocating_buffer->Pack(&objectname, 1);
    allocating_buffer->Pop();

    allocating_buffer->Push("codefile", "POPString", 1);
    allocating_buffer->Pack(&codefile, 1);
    allocating_buffer->Pop();

    allocating_buffer->Push("node", "int", 1);
    allocating_buffer->Pack(&node, 1);
    allocating_buffer->Pop();

    allocating_buffer->Push("core", "int", 1);
    allocating_buffer->Pack(&core, 1);
    allocating_buffer->Pop();

          paroc_connection* connection = allocating_combox->get_connection();	
    if (!allocating_buffer->Send((*allocating_combox), connection)) {
            paroc_exception::paroc_throw_errno();
          }   

          if (!allocating_buffer->Recv((*allocating_combox), connection)) {
      paroc_exception::paroc_throw_errno();	
          }
          paroc_buffer::CheckAndThrow(*allocating_buffer);

    POPString objectaddress;        		
          allocating_buffer->Push("objectaddress", "POPString", 1);
          allocating_buffer->UnPack(&objectaddress, 1);
          allocating_buffer->Pop();
          allocating_buffer->Destroy();
    allocating_combox->Close(); 

    return objectaddress;  
}

/**
 * Allocate a single object by using the TCP/IP protocol with a local allocation mechanism
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @param nb          The number of object to allocate in the group
 * @return A pointer to a single combox connected with the group
 */
paroc_combox* POPC_Allocator_tcpip_local::allocate_group(POPString& objectname, paroc_od& od, int nb)
{

  /* Allocation process here */  
  
  return NULL; 
}
