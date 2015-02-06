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

#include "popc_allocator_uds_interconnector.h"

#include "paroc_system.h"
#include "paroc_exception.h"
#include "paroc_combox.h"
#include "paroc_combox_factory.h"
#include "paroc_broker.h"
#include "popc_logger.h"


/**
 * Allocator constructor
 */
POPC_Allocator_uds_interconnector::POPC_Allocator_uds_interconnector() {
}

/**
 * Allocator destructor
 */
POPC_Allocator_uds_interconnector::~POPC_Allocator_uds_interconnector() {
}

/**
 * Allocate a single object by using the UDS protocol with the POP-C++ MPI Interconnector
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @return A string representation of the access-point
 */
POPString POPC_Allocator_uds_interconnector::allocate(POPString& objectname, paroc_od& od) {
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
        node = paroc_system::popc_local_mpi_communicator_rank;
    }

    // Get the executable path name
    POPString codefile;
    od.getExecutable(codefile);

    // If od.executable is not defined, throw an exception as the parallel object couldn't be allocated
    if(codefile.Length() <= 0) {
        LOG_ERROR("Code file executable path is NULL ! Abort !");
        paroc_exception::paroc_throw(POPC_NO_PROTOCOL, objectname, "Code file executable path is NULL ! Abort !");
    }

    /**
     * POP-C++ for the K Computer
     * Create a combox to contact the MPI Communicator process to allocate the new parallel object.
     */
    paroc_combox_factory* combox_factory = paroc_combox_factory::GetInstance();
    if(combox_factory == NULL) {
        paroc_exception::paroc_throw(POPC_NO_PROTOCOL, objectname, "No combox factory");
    }

    paroc_combox* allocating_combox = combox_factory->Create("uds");

    if(allocating_combox == NULL) {
        paroc_exception::paroc_throw(POPC_NO_PROTOCOL, objectname, "allocating_combox == NULL");
    }

    paroc_buffer* allocating_buffer = allocating_combox->GetBufferFactory()->CreateBuffer();

    char* local_address = new char[15];
    snprintf(local_address, 15, "uds_%d.0", paroc_system::popc_local_mpi_communicator_rank);
    if(!allocating_combox->Create(local_address, false) || !allocating_combox->Connect(local_address)) {
        paroc_exception::paroc_throw(POPC_NO_PROTOCOL, objectname, "Create or Connect failed");
    }

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
    if(!allocating_buffer->Send((*allocating_combox), connection)) {
        paroc_exception::paroc_throw("allocating_buffer->Send failed");
    }

    if(!allocating_buffer->Recv((*allocating_combox), connection)) {
        paroc_exception::paroc_throw_errno("allocating_buffer->Recv failed");
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
 * Allocate a group of objects by using the UDS protocol with the POP-C++ MPI Interconnector
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @param nb          The number of object to allocate in the group
 * @return A pointer to a single combox connected with the group
 */
paroc_combox* POPC_Allocator_uds_interconnector::allocate_group(POPString& objectname, paroc_od& od, int nb) {

    POPString codefile;
    od.getExecutable(codefile);

    if(codefile.Length() <= 0) {
        std::cerr << "POP-C++ Error [Core]" << "Cannot allocate group of objects because executbale is not specified" << std::endl;
        return NULL;
    }

    // Contact the local POP-C++ MPI Interconnector to create XMP process
    int rank = paroc_system::popc_local_mpi_communicator_rank;

    char* local_interconnector_address = new char[15];
    snprintf(local_interconnector_address, 15, "uds_%d.0", rank);

    paroc_combox_factory* combox_factory = paroc_combox_factory::GetInstance();
    if(combox_factory == NULL) {
        paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "ComboxFactory NULL");
    }

    paroc_combox* _popc_combox = combox_factory->Create("uds");
    if(_popc_combox == NULL) {
        paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "Combox NULL");
    }

    paroc_buffer* _popc_buffer = _popc_combox->GetBufferFactory()->CreateBuffer();

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


    if(!_popc_buffer->Send((*_popc_combox), _popc_connection)) {
        LOG_ERROR("[Core] Problem while sending request");
        paroc_exception::paroc_throw("Problem while sending request");
    }

    if(!_popc_buffer->Recv((*_popc_combox), _popc_connection)) {
        paroc_exception::paroc_throw("_popc_buffer->Recv failed");
    }
    paroc_buffer::CheckAndThrow(*_popc_buffer);


    POPString objectaddress;
    _popc_buffer->Push("objectaddress", "POPString", 1);
    _popc_buffer->UnPack(&objectaddress, 1);
    _popc_buffer->Pop();

    return _popc_combox;
}
