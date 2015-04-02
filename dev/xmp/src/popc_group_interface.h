/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/11/30
 * @brief Declaration of base POPC_Group_interface class. This class is the base class for interface-side of a group
 *        parallel object. A group parallel object is a set of parallel object that can be called in a single or collective way.
 *
 *
 */

#ifndef POPC_GROUP_INTERFACE_H_
#define POPC_GROUP_INTERFACE_H_

#include "pop_od.h"
#include "pop_combox.h"
#include "pop_buffer.h"
#include <vector>


class POPC_GroupInterface {
public:
    POPC_GroupInterface();
    virtual ~POPC_GroupInterface();

    // Group control methods
    bool initialize(int nb);
    bool finalize();

    void set_default_rank(int rank);
    int get_default_rank();

    // Utility method to access useful information
    int get_group_size();
    bool is_initialized();
    bool is_finalized();


    // Group management operations
    POPC_GroupInterface& merge(POPC_GroupInterface& other);
    POPC_GroupInterface& split(const int rank);
    POPC_GroupInterface& split(const int group1[], const int group1_size);
    POPC_GroupInterface& split(const std::vector<int> group1);
    bool remove(const int rank);


    //
    virtual POPC_GroupInterface& operator[](const int index)=0;

protected:
    void allocate_multiple(int nb); // Allocate a number of parallel object that will be managed by the group interface
    virtual void construct_remote_object() = 0;

    virtual char* get_class_name();

    // Object description as standard interface
    pop_od od;

    // Combox and buffer used for every communication of this interface group
    pop_combox* _popc_combox;
    pop_buffer* _popc_buffer;

    // Method used to send and receive message from/to internal buffer
    void popc_send_request(pop_buffer* buffer, pop_connection* connection);
    void popc_recv_response(pop_buffer* buffer, pop_connection* connection);

    // Default object for single call
    int _popc_default_rank_for_single_call;

    // Save the constructor to be used to initialize the group
    int _popc_selected_constructor_id;

private:
    // Internal variable to manage the group parallel objects
    bool _popc_is_initialized;
    bool _popc_is_finalized;

    // Number of parallel object belonging to this group
    int _popc_nb_parallel_object;



    // Internal method controlling the live of XMP parallel object
    bool _popc_allocate_parallel_object(int nb);
    bool _popc_terminate_parallel_object(int nb);





};

#endif /* POPC_GROUP_INTERFACE_H_ */