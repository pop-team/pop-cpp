/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/11/29
 * @brief Entry point of POP-C++ parallel object integrating XMP support.
 *
 *
 */

#include <mpi.h>
#include <stdlib.h>

#include "pop_utils.h"
#include "pop_system.h"
#include "popc_buffer_xdr_mpi.h"
#include "pop_broker.h"
#include "popc_group_broker.h"
#include "popc_group_broker_factory.h"
#include "popc_connection_mpi.h"
#include "pop_combox.h"

/**
 * Initialize a parallel object with XMP support
 * @param argc Number of arguments passed to main
 * @param argv Array of char pointer representing the arguments passed to main
 * @return 0 if success.
 */
int main(int argc, char* argv[]) {
    MPI::Intercomm communicator;
    int rank;
    if (pop_utils::checkremove(&argc, &argv, "-listlong") != NULL) {
        printf("This kind of parallel object doesn't support this option.\n");
        return 1;
    }

    if (!MPI::Is_initialized()) {
        int required_support = MPI_THREAD_SERIALIZED;
        int provided_support = MPI::Init_thread(required_support);

        communicator = MPI::COMM_WORLD.Get_parent();
        rank = MPI::COMM_WORLD.Get_rank();

        if (provided_support < required_support) {
            printf(
                "POP-C++ Warning: Support of multithread in MPI is lower than required. Deadlock can block your "
                "application\n");
        } else {
            printf("POP-C++ XMP process started %d\n", rank);
        }
    }

    char* objectname = pop_utils::checkremove(&argc, &argv, "-object=");
    if (objectname == NULL) {
        printf("POP-C++ Error: Object name has not been specified in the arguments!\n");
        if (!MPI::Is_finalized()) {
            MPI::Finalize();
        }
        return 1;
    }

    // Create a broker with the specified Object
    POPC_GroupBroker* broker = POPC_GroupBrokerFactory::create(objectname);
    pop_mpi_connection* mpi_connection = new pop_mpi_connection();
    mpi_connection->set_communicator(communicator);

    bool active = true;
    MPI::Status status;

    // Start listening for new requests
    while (active) {
        // Receive command and data length
        int data[2];
        MPI::Request req = communicator.Irecv(&data, 2, MPI_INT, 0, 0);
        bool done = false;
        while (!done) {
            done = req.Test(status);
        }

        // Receive data
        char* load = new char[data[1]];
        req = communicator.Irecv(load, data[1], MPI_CHAR, 0, 2);
        done = false;
        while (!done) {
            done = req.Test(status);
        }

        // Load data into a popc_buffer to be able to process them
        pop_request request;
        request.data = new popc_buffer_xdr_mpi();
        request.data->load(load, data[1]);

        // Get information about the header
        const pop_message_header& header = request.data->GetHeader();
        request.methodId[0] = header.GetClassID();
        request.methodId[1] = header.GetMethodID();
        request.from = mpi_connection;
        // printf("BROKER %d: Class ID = %d, Type = %d, Method ID = %d, Semantics = %d\n", rank, header.GetClassID(),
        // header.GetType(), header.GetMethodID(), header.GetSemantics());

        // Receive DecRef - Means end of the process for a parallel object group.
        if (header.GetMethodID() == 2) {
            active = false;
        } else {
            // Invoke the method
            broker->invoke(request.methodId, *request.data, request.from);
        }

        // Delete the buffer
        delete request.data;
    }

    // Delete created object
    delete mpi_connection;
    delete broker;

    // Finalize the MPI execution
    if (!MPI::Is_finalized()) {
        MPI::Finalize();
    }
    return 0;
}
