/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/10/15
 * @brief Declaration of MPI Connection (POP-C++ abstraction of connection).
 *        Just hold the destination rank of the MPI communicator.
 *
 *
 */

#ifndef INCLUDE_POPC_CONNECTION_MPI_H_
#define INCLUDE_POPC_CONNECTION_MPI_H_

#include "pop_combox.h"
#include <mpi.h>

class pop_mpi_connection : public pop_connection {
public:
    pop_mpi_connection();
    explicit pop_mpi_connection(pop_combox* cb);
    explicit pop_mpi_connection(pop_mpi_connection& me);
    ~pop_mpi_connection();

    virtual pop_connection* Clone();

    void set_communicator(MPI::Intercomm communicator);
    MPI::Intercomm get_communicator();

    void set_connection_index(int value);
    int get_connection_index();

    void set_as_asynchronous();
    bool is_asynchronous();

    void set_current_tag(int value);
    void unset_current_tag();
    int get_current_tag();
    bool is_tag_set();

    bool has_communicator();
    void reset();
    bool is_server();

private:
    MPI::Intercomm _communicator;
    bool _is_connected;
    bool _has_communicator;
    int _connection_index;
    bool _is_asynchronous;
    int _current_tag;
    bool _tag_set;
};

#endif  // INCLUDE_POPC_CONNECTION_MPI_H_