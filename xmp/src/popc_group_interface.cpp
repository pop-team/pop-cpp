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
#include "popc_group_exception.h"
#include "popc_allocator_factory.h"

/**
 * Base constructor
 * A POPC_GroupInterface object is always created empty.
 */
POPC_GroupInterface::POPC_GroupInterface() : _popc_default_rank_for_single_call(0), _popc_is_initialized(false), _popc_is_finalized(false), _popc_nb_parallel_object(0)
     {
}


/**
 * Base destructor. Will finalized the object if finalize() was not called before.
 */
POPC_GroupInterface::~POPC_GroupInterface() {
    if(!is_finalized()) {
        finalize();
    }
}

/**
 * Initialized the parallel object managed by this interface
 * @param nb  Number of parallel object to be managed by this interface
 * @return TRUE if the initialization is done successfully. FALSE if already initialized or in any other cases.
 */
bool POPC_GroupInterface::initialize(int nb) {
    if(is_initialized()) {
        return false;
    }

    if(nb <= 0) {
        return false;
    }

    POPString objectname = get_class_name();

    POPC_AllocatorFactory* alloc_factory = POPC_AllocatorFactory::get_instance();
    POPC_Allocator* allocator = alloc_factory->get_allocator(POPC_Allocator::UDS, POPC_Allocator::INTERCONNECTOR);
    if(allocator == NULL) {
        std::cerr << "POP-C++ Error [Core]: " << "Allocator is NULL" << std::endl;
        // TODO lwk security: is this all ? Should we not exit ?
    }

    _popc_combox = allocator->allocate_group(objectname, od, nb);
    _popc_buffer = _popc_combox->GetBufferFactory()->CreateBuffer();

    _popc_is_initialized = true;

    construct_remote_object();

    return true;
}

/**
 * Merge two parallel object group. This group and the other group will be similar after merging.
 * @param other Reference to another parallel object group of the same type.
 * @return Reference to the merged group.
 */
POPC_GroupInterface& POPC_GroupInterface::merge(POPC_GroupInterface& other) {
    if(!is_initialized() || !other.is_initialized()) {
        throw new POPC_GroupException(POPC_GroupException::NOTINITIALIZED);
    }

    // To be removed when implemented
    throw new POPC_GroupException(POPC_GroupException::NOTIMPLEMENTED);
}

/**
 * Split this group in two separate group by indicating the rank that split group in two. All members with rank below the given
 * parameter are placed in group 1. All remaining members are place in group 2.
 * @param rank  Rank of the object that split the group in two.
 * @return Reference to the parallel object group 2
 */
POPC_GroupInterface& POPC_GroupInterface::split(const int rank) {
    if(!is_initialized()) {
        throw new POPC_GroupException(POPC_GroupException::NOTINITIALIZED);
    }

    if(rank >= get_group_size()) {
        throw new POPC_GroupException(POPC_GroupException::OUTOFGROUP);
    }

    // To be removed when implemented
    throw new POPC_GroupException(POPC_GroupException::NOTIMPLEMENTED);
}

/**
 * Split this group in two separate group by indicating members of each group. This group will be group 1.
 * @param group1      Rank of the members to be placed in group 1.
 * @param group1_size Size of the array group1.
 * @return Reference to the parallel object group 2.
 */
POPC_GroupInterface& POPC_GroupInterface::split(const int group1[], const int group1_size) {
    if(!is_initialized()) {
        throw new POPC_GroupException(POPC_GroupException::NOTINITIALIZED);
    }

    // Check if group1 are members of this group
    for(int i = 0; i < group1_size; i++) {
        if(group1[i] >= get_group_size()) {
            throw new POPC_GroupException(POPC_GroupException::OUTOFGROUP);
        }
    }

    throw new POPC_GroupException(POPC_GroupException::NOTIMPLEMENTED);
}

/**
 * Split this group in two separate group by indicating members left in the original group (group1).
 * @param group1      vector holding the object rank to be left in the original group
 * @return Reference to the parallel object group 2.
 */
POPC_GroupInterface& POPC_GroupInterface::split(const std::vector<int> group1) {
    if(!is_initialized()) {
        throw new POPC_GroupException(POPC_GroupException::NOTINITIALIZED);
    }

    // Check if group1
    if(group1.empty()) {
        throw new POPC_GroupException(POPC_GroupException::EMPTYGROUP);
    }

    throw new POPC_GroupException(POPC_GroupException::NOTIMPLEMENTED);
}



/**
 * Remove a single object from this parallel object group
 * @param rank  Rank of the object to be removed
 * @return TRUE if the object has been successfully removed. FALSE in any other cases.
 */
bool POPC_GroupInterface::remove(const int rank) {
    if(!is_initialized()) {
        throw new POPC_GroupException(POPC_GroupException::NOTINITIALIZED);
    }

    if(rank >= get_group_size()) {
        throw new POPC_GroupException(POPC_GroupException::OUTOFGROUP);
    }

    // To be removed when implemented
    throw new POPC_GroupException(POPC_GroupException::NOTIMPLEMENTED);

    return false;
}

/**
 * Finalize the parallel object managed by this interface
 * @return TRUE if the finalization is done successfully. FALSE if already finalized, not initialized or in any other cases.
 */
bool POPC_GroupInterface::finalize() {
    // Finalize only of not finalized yet and
    if(is_finalized() || !is_initialized()) {
        return false;
    }

    // Terminate the processes
    paroc_message_header h(0, 2, INVOKE_SYNC, "DecRef");
    _popc_buffer->Reset();
    _popc_buffer->SetHeader(h);

    // Get the connection to the communication layer
    paroc_connection* connection = _popc_combox->get_connection();

    // Send the request for finalization
    popc_send_request(_popc_buffer, connection);
    // Wait for finalization to be performed
    popc_recv_response(_popc_buffer, connection);

    // Clean buffer and combox
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
void POPC_GroupInterface::popc_send_request(paroc_buffer* buffer, paroc_connection* connection) {
    if(!buffer->Send((*_popc_combox), connection)) {
        printf("ERROR: Problem while sending request\n");
        paroc_exception::paroc_throw_errno();
    }
}

/**
 * Receive a response from the end point
 * @param buffer      Empty buffer to receive the request header and its data load
 * @param connection  Connection used to receive the response.
 */
void POPC_GroupInterface::popc_recv_response(paroc_buffer* buffer, paroc_connection* connection) {
    if(!buffer->Recv((*_popc_combox), connection)) {
        paroc_exception::paroc_throw_errno();
    }
    paroc_buffer::CheckAndThrow(*buffer);
}

/**
 * Set the default rank for non-collective call. This rank is used for all non-collective calls and can be changed at any time.
 * @param rank  Rank between 0 and (group size - 1)
 */
void POPC_GroupInterface::set_default_rank(int rank) {
    _popc_default_rank_for_single_call = rank;
}

/**
 * Get the current default rank for non-collective calls
 * @return Integer value representing the rank between 0 and (group size - 1)
 */
int POPC_GroupInterface::get_default_rank() {
    return _popc_default_rank_for_single_call;
}

/**
 * Return the class name of the current interface. Overloaded by child class.
 * @return Pointer to a string containing the class name.
 */
char* POPC_GroupInterface::get_class_name() {
    return (char*)"";
}

/**
 * Get the number of parallel object managed by this interface.
 * @return Integer value representing the number of parallel object managed by this interface.
 */
int POPC_GroupInterface::get_group_size() {
    return _popc_nb_parallel_object;
}

/**
 * Check if the parallel objects managed by this interface have been initialized.
 * @return TRUE if the initialization was done. FALSE if not initialized.
 */
bool POPC_GroupInterface::is_initialized() {
    return _popc_is_initialized;
}

/**
 * Check if the parallel objects managed by this interface have been finalized.
 * @return TRUE if the finalization was done. FALSE if not finalized.
 */
bool POPC_GroupInterface::is_finalized() {
    return _popc_is_finalized;
}
