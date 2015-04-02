/**
 * POP-C++ MPI Interconnector: Acts as a communication layer for POP-C++ running over computer with only MPI suppport for
 * inter-node communication.
 * This process is able to:
 * - Launch the main of the POP-C++ application when it has the rank 0.
 * - Allocate object on itself or pass the allocation request to another MPI Communicator.
 * - Redirect request received by IPC to the right node.
 * - Redirect request received by MPI to the right object.
 *
 *
 * @author Valentin Clement
 * @date 2012/10/25
 * @file popc_mpi_interconnector.cpp
 */

// System include
#include <mpi.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdio.h>
#include <map>


// POP-C++ library include
#include "paroc_broker.h"
#include "pop_buffer_xdr.h"
#include "popc_combox_uds.h"
#include "paroc_utils.h"

using namespace std;

// Global variable
int rank, world;
int core, nbcore;
int allocation_id;


// Declaration of various map holding routing information
map<int, int> incomingtag;
map<int, pair<int, int> > incomingconnection;
map<int, pair<int, int> > outgoingconnection;
map<pair<int, int>, pop_combox*> connectionmap;
map<int, pop_connection*> allocation_return;
map<int, pair<MPI::Intercomm, int> > object_group;
map<int, int> object_group_single;

// Define the constant used in the program
static int MPI_COMMAND_TERMINATE = 10;
static int MPI_COMMAND_ALLOCATE = 11;
static int MPI_TAG_DUMMY = 0;
static int MPI_TAG_COMMAND = 0;

// Declaring MPI intra-communicator for the creation of XMP parallel object
MPI::Intracomm comm_world_dup;
MPI::Intracomm comm_self;
int nb_comm = 1;
MPI::Request mpirequest[10];
MPI::Intercomm extracomm[10];
int extrafd[10];
int mpidatain[10][2];


// Condition variable to serialize MPI Call
pthread_mutex_t mpi_mutex;
pthread_mutex_t incoming_tag_map_mutex;
pthread_mutex_t allocation_return_map_mutex;

// Keep the main pid to return its return value
pid_t popc_main_pid;
int main_return_value;

/**
 * Catch signal of exiting child
 */
void catch_child_exit(int signal_num) {
    int retval;
    char buf[256];
    bzero(buf, 256);
    pid_t pid = waitpid(0, &retval, WNOHANG);


    int w_exit = WEXITSTATUS(retval);
    int w_ifexited = WIFEXITED(retval);
    int w_ifsignal = WIFSIGNALED(retval);
    int w_signal = WTERMSIG(retval);

    // Keep the return value of the main
    if(pid == popc_main_pid) {
        main_return_value = w_exit;
    }


    //printf("On %d Child exists signal=%d, ret=%d, WEXITSTATUS=%d, %d, %d, %d\n", rank, signal_num, retval, w_exit, w_ifexited, w_ifsignal, w_signal);

}


/**
 * Receive new incoming MPI data and transmit them to the main thread
 */
void *mpireceivedthread(void *t) {
    int rank = MPI::COMM_WORLD.Get_rank();
    char* tmp = new char[20];
    snprintf(tmp,sizeof(tmp), "uds_%d.0", rank);
    std::string local_address(tmp);
    delete [] tmp;
    bool active = true;

    // Connect to main process by IPC
    popc_combox_uds ipcwaker;
    ipcwaker.Create(local_address.c_str(), false);
    if(!ipcwaker.Connect(local_address.c_str())) {
        perror("MPI received thread cannot connect to MPI interconnector");
        pthread_exit(NULL);
        return NULL;
    }

    pop_buffer* ipcwaker_buffer = ipcwaker.GetBufferFactory()->CreateBuffer();
    pop_connection* connection = ipcwaker.get_connection();
    if(connection == NULL) {
        perror("MPI received thread connection is NULL");
        pthread_exit(NULL);
        return NULL;
    }

    int index;

    // Waiting for MPI calls
    while(active) {
        MPI::Status status;

        if(index == 0) { // Activate or re-activate the request only in case it is not activated yet
            // Receive data
            pthread_mutex_lock(&mpi_mutex);
            mpirequest[0] = MPI::COMM_WORLD.Irecv(&mpidatain[0], 2, MPI_INT, MPI_ANY_SOURCE, 0);
            pthread_mutex_unlock(&mpi_mutex);
        }

        bool done = false;

        while(!done) {
            pthread_mutex_lock(&mpi_mutex);
            done = mpirequest[0].Testany(nb_comm, mpirequest, index, status);
            pthread_mutex_unlock(&mpi_mutex);
        }

        switch(mpidatain[index][0]) {

            // Receive ending command from the main MPI process.
        case 10: {
            active = false;

            if(rank != 0) {
                // signal the IPC process to stop
                paroc_message_header endheader(20, 200001, INVOKE_SYNC, "_terminate");
                ipcwaker_buffer->Reset();
                ipcwaker_buffer->SetHeader(endheader);
                ipcwaker_buffer->Send(ipcwaker, connection);
            }
        }
        break;
        // Allocation of new parallel object
        case 11: {
            // signal the IPC thread to be ready to receive data for allocation
            paroc_message_header endheader(20, 200004, INVOKE_SYNC, "_allocation");
            ipcwaker_buffer->Reset();
            ipcwaker_buffer->SetHeader(endheader);
            ipcwaker_buffer->Send(ipcwaker, connection);
        }
        break;
        // Wait for action to complete
        case 12: {

            break;
        }
        // Will receive a request from a redirection
        case 13: {
            //printf("MPI request %d %d\n", rank, status.Get_source());
            paroc_message_header reqheader(status.Get_source(), 200005, INVOKE_SYNC, "_request");
            ipcwaker_buffer->Reset();
            ipcwaker_buffer->SetHeader(reqheader);
            ipcwaker_buffer->Push("tag", "int", 1);
            ipcwaker_buffer->Pack(&mpidatain[index][1], 1);
            ipcwaker_buffer->Pop();
            ipcwaker_buffer->Send(ipcwaker, connection);
            break;
        }
        case 14: {
            //printf("Response from MPI\n");
            int source = status.Get_source();
            int tag = mpidatain[index][1];


            //printf("Redirect response back to IPC %d, %d\n", source, tag);
            MPI::Status status;
            int length;
            pthread_mutex_lock(&mpi_mutex);
            MPI::Request req = MPI::COMM_WORLD.Irecv(&length, 1, MPI_INT, source, tag);
            pthread_mutex_unlock(&mpi_mutex);



            bool done = false;
            while(!done) {
                pthread_mutex_lock(&mpi_mutex);
                done = req.Test(status);
                pthread_mutex_unlock(&mpi_mutex);
            }

            if(length <= 0) {
                printf("POP-C++ Error: MPI Interconnector - request MPI-IPC redirection, length is %d\n", length);
            }

            char *data = new char[length];
            pthread_mutex_lock(&mpi_mutex);
            req = MPI::COMM_WORLD.Irecv(data, length, MPI_CHAR, source, tag);
            pthread_mutex_unlock(&mpi_mutex);

            done = false;
            while(!done) {
                pthread_mutex_lock(&mpi_mutex);
                done = req.Test(status);
                pthread_mutex_unlock(&mpi_mutex);
            }

            pthread_mutex_lock(&incoming_tag_map_mutex);
            int fd = incomingtag[tag];
            pthread_mutex_unlock(&incoming_tag_map_mutex);

            //printf("Redirect response back to IPC %d, %d %d\n", source, tag, fd);
            popc_connection_uds* tmpconnection = new popc_connection_uds(fd, &ipcwaker);
            if(ipcwaker.Send(data, length, tmpconnection) < 0) {
                printf("Can't send response back to caller (fd=%d, source=%d, tag=%d)\n", fd, source, tag);
            }

            // Clean the entry in the map
            pthread_mutex_lock(&incoming_tag_map_mutex);
            incomingtag.erase(tag);
            pthread_mutex_unlock(&incoming_tag_map_mutex);

            delete [] data;

            break;
        }
        case 15: { // Allocation response from MPI
            int node = status.Get_source();
            int id = mpidatain[index][1];

            int objaccess_length;
            pthread_mutex_lock(&mpi_mutex);
            MPI::Request req = MPI::COMM_WORLD.Irecv(&objaccess_length, 1, MPI_INT, node, 14);
            pthread_mutex_unlock(&mpi_mutex);
            MPI::Status status;
            bool done = false;
            while(!done) {
                pthread_mutex_lock(&mpi_mutex);
                done = req.Test(status);
                pthread_mutex_unlock(&mpi_mutex);
            }

            char* objaccess = new char[objaccess_length+1];
            pthread_mutex_lock(&mpi_mutex);
            req = MPI::COMM_WORLD.Irecv(objaccess, objaccess_length, MPI_CHAR, node, 15);
            pthread_mutex_unlock(&mpi_mutex);

            done = false;
            while(!done) {
                pthread_mutex_lock(&mpi_mutex);
                done = req.Test(status);
                pthread_mutex_unlock(&mpi_mutex);
            }
            objaccess[objaccess_length] = '\0';

            // Return objaccess
            std::string objectaddress(objaccess);
            delete [] objaccess;

            ipcwaker_buffer->Reset();
            paroc_message_header h("_allocate");
            ipcwaker_buffer->SetHeader(h);
            ipcwaker_buffer->Push("objectaddress", "std::string", 1);
            ipcwaker_buffer->Pack(&objectaddress, 1);
            ipcwaker_buffer->Pop();
            ipcwaker_buffer->Send(allocation_return[id]);

            break;
        }

        case 16: {
            MPI::Request req;
            int length;
            int source = status.Get_source();
            pthread_mutex_lock(&mpi_mutex);
            req = extracomm[index].Irecv(&length, 1, MPI_INT, source, 1);
            pthread_mutex_unlock(&mpi_mutex);

            done = false;
            while(!done) {
                pthread_mutex_lock(&mpi_mutex);
                done = req.Test(status);
                pthread_mutex_unlock(&mpi_mutex);
            }

            char *data = new char[length];
            pthread_mutex_lock(&mpi_mutex);
            req = extracomm[index].Irecv(data, length, MPI_CHAR, source, 2);
            pthread_mutex_unlock(&mpi_mutex);

            done = false;
            while(!done) {
                pthread_mutex_lock(&mpi_mutex);
                done = req.Test(status);
                pthread_mutex_unlock(&mpi_mutex);
            }


            popc_connection_uds* tmpconnection = new popc_connection_uds(extrafd[index], &ipcwaker);
            if(ipcwaker.Send(data, length, tmpconnection) < 0) {
                printf("Can't send response back to caller (fd=%d, source=%d)\n", extrafd[index], source);
            }

            pthread_mutex_lock(&mpi_mutex);
            mpirequest[index] = extracomm[index].Irecv(&mpidatain[index], 2, MPI_INT, MPI_ANY_SOURCE, 0);
            pthread_mutex_unlock(&mpi_mutex);

            break;
        }
        // Unknown command ... do nothing
        default:
            printf("Unknown data received on %d = %d index=%d\n", rank, mpidatain[index][0], index);
        }
    }

    pthread_exit(NULL);
    return NULL;
}

/**
 * Main thread of the POP-C++ MPI Communicator. This thread is responsible for all IPC communication and MPI communication after
 * received command from the MPI receive thread.
 * Usage: popc_mpi_communicator -app=<popc_application_main> [args]
 */
int main(int argc, char* argv[]) {
    // Initialize the local variable of the communicator
    if(!MPI::Is_initialized()) {
        // Init MPI for multithread support
        int required_support = MPI_THREAD_SERIALIZED; // Maximum supported by the K Computer
        int provided_support = MPI::Init_thread(required_support);

    }



    core = 0;
    nbcore = 0;
    allocation_id = 0;

    // Catch signal when a child is exiting
    signal(SIGCHLD, catch_child_exit);
    signal(SIGPIPE, SIG_IGN);
    if(argc < 2) {
        printf("usage: %s -app=<popc_application_main> [args]\n", argv[0]);
        MPI::Finalize();
        return 1;
    }

    // Initialize local address
    rank = MPI::COMM_WORLD.Get_rank();
    world = MPI::COMM_WORLD.Get_size();

    // Duplicate the global communicator
    comm_world_dup = MPI::COMM_WORLD.Dup();
    // Create a self containing communicator for spawn creation task
    comm_self = comm_world_dup.Split(rank, 0);


#ifndef __APPLE__
    nbcore = sysconf(_SC_NPROCESSORS_ONLN);
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(core, &cpu_set);
    if(sched_setaffinity(0, sizeof(cpu_set), &cpu_set) == -1) {
        printf("POP-C++ Warning: Cannot set processor to %d (cpu_set %p)", core, (void *)&cpu_set);
    }
    core++;
    int cpu = sched_getcpu();
#endif

    pid_t mainpid;        // Save main pid to wait for it at the end
    pthread_t mpithread;  // MPI Receive thread


    char* tmp = new char[20];
    sprintf(tmp, "uds_%d.0", rank);
    std::string local_address(tmp);
    delete [] tmp;

    // Create local combox server to accept incoming request from interface
    popc_combox_uds local;
    if(!local.Create(local_address.c_str(), true)) {
        printf("POP-C++ Error: MPI Interconnector %d failed to initialize\n", rank);
        MPI::Finalize();
        return 1;
    }

    bool multiple_connection_enable = false;
    // Check if the multiple connection option is set
    if(paroc_utils::checkremove(&argc, &argv, "--multiple-connection") != NULL) {
        printf("Multiple connection: enable\n");
        multiple_connection_enable = true;
    }



    // Start main of the POP-C++ application on the MPI process with rank 0
    if(rank == 0) {
        std::string application_arg;
        char* capp = paroc_utils::checkremove(&argc, &argv, "-app=");
        // End application if app is not provided
        if(capp == NULL) {
            if(rank == 0) {
                printf("usage: %s -app=<app_exec>\n", argv[0]);
            }
            MPI::Finalize();
            return 1;
        } else {
            application_arg.append(capp);
        }

        // Create new process for the POP-C++ application main
        mainpid = fork();

        if(mainpid == 0) {
            // Execute the code of the main of the application
            argv[0] = const_cast<char*>(application_arg.c_str());
            execv(argv[0], argv);
            perror("Execv failed");
        } else if(mainpid == -1) {
            // If fork had a problem, terminate the application
            perror("start main process");
            MPI::Finalize();
            return 1;
        }

        popc_main_pid = mainpid;
    }

    // Initialize tag value to be used by this POP-C++ MPI Interconnector
    int next_tag = 1000;

    // Init object counter
    int next_object_id = 1;

    // Create MPI receive thread
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Initialize mutex lock
    if(pthread_mutex_init(&mpi_mutex, NULL) != 0) {
        perror("Mutex init");
    }

    if(pthread_mutex_init(&incoming_tag_map_mutex, NULL) != 0) {
        perror("Mutex init");
    }

    // Create the MPI receive thread
    pthread_create(&mpithread, &attr, mpireceivedthread, NULL);

    // Wait for IPC request
    bool active = true;

    // Start receiving request from the IPC server
    while(active) {
        // Create empty request object to receive request from IPC
        paroc_request request;
        request.data = NULL;
        // Wait for data on the UDS
        pop_connection* connection = local.Wait();

        if(connection == NULL) {
            // Connection is null. No data will come on this connection. Wait for another one.
            printf("Connection null\n");
        } else if(!connection->is_initial_connection()) {
            // Process incoming request
            pop_buffer_factory *buffer_factory = connection->GetBufferFactory();
            request.data = buffer_factory->CreateBuffer();

            if(request.data->Recv(connection)) {
                request.from = connection;
                const paroc_message_header &header = request.data->GetHeader();
                request.methodId[0] = header.GetClassID();
                if(header.GetType() == TYPE_EXCEPTION) {
                    request.methodId[1] = header.GetMethodID() - 100000;
                } else {
                    request.methodId[1] = header.GetMethodID();
                }
                // Killing the process, end of the higher-level application
                if(request.methodId[1] == 200001) {
                    active = false;
                    if(rank == 0) {
                        int data[2];
                        data[0] = MPI_COMMAND_TERMINATE; // DATA 10 = END OF THE APPLICATION
                        data[1] = MPI_TAG_DUMMY;
                        int tag = MPI_TAG_COMMAND;   // TAG 0 = COMMAND MESSAGE
                        if(world > 1) {
                            for(int i = 1; i < world; i++) {
                                // Inform other MPI communicator to end their process.
                                pthread_mutex_lock(&mpi_mutex);
                                MPI::COMM_WORLD.Issend(&data, 2, MPI_INT, i, tag);
                                pthread_mutex_unlock(&mpi_mutex);
                            }
                        }
                        pthread_mutex_lock(&mpi_mutex);
                        MPI::COMM_WORLD.Isend(&data, 2, MPI_INT, 0, tag);
                        pthread_mutex_unlock(&mpi_mutex);

                    }
                } else if(request.methodId[1] == 200002) {
                    // Connection to this process as a router process

                    int dest_node, dest_id;
                    request.data->Push("destnode", "int", 1);
                    request.data->UnPack(&dest_node, 1);
                    request.data->Pop();

                    request.data->Push("destid", "int", 1);
                    request.data->UnPack(&dest_id, 1);
                    request.data->Pop();

                    int current_fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();
                    incomingconnection.insert(pair<int, pair<int, int> >(current_fd, pair<int, int>(dest_node, dest_id)));

//          printf("Connection fd = %d, dest node = %d, dest id = %d\n", current_fd, dest_node, dest_id);

                } else if(request.methodId[1] == 200003) {
                    // Get information from the MPI received node
                    // None to get for the moment

                } else if(request.methodId[1] == 200004) {

                    // Allocation of a new parallel object from MPI
                    MPI::Status status;
                    int objectname_length, codefile_length, alloc_id;


                    pthread_mutex_lock(&mpi_mutex);
                    MPI::Request mreq = MPI::COMM_WORLD.Irecv(&alloc_id, 1, MPI_INT, MPI_ANY_SOURCE, 17);
                    pthread_mutex_unlock(&mpi_mutex);
                    bool done = false;
                    while(!done) {
                        pthread_mutex_lock(&mpi_mutex);
                        done = mreq.Test(status);
                        pthread_mutex_unlock(&mpi_mutex);
                    }

                    int source = status.Get_source();

                    pthread_mutex_lock(&mpi_mutex);
                    mreq = MPI::COMM_WORLD.Irecv(&objectname_length, 1, MPI_INT, source, 10);
                    pthread_mutex_unlock(&mpi_mutex);

                    done = false;
                    while(!done) {
                        pthread_mutex_lock(&mpi_mutex);
                        done = mreq.Test(status);
                        pthread_mutex_unlock(&mpi_mutex);
                    }



                    pthread_mutex_lock(&mpi_mutex);
                    mreq = MPI::COMM_WORLD.Irecv(&codefile_length, 1, MPI_INT, source, 12);
                    pthread_mutex_unlock(&mpi_mutex);

                    done = false;
                    while(!done) {
                        pthread_mutex_lock(&mpi_mutex);
                        done = mreq.Test(status);
                        pthread_mutex_unlock(&mpi_mutex);
                    }
                    char* objectname = new char[objectname_length+1];
                    char* codefile = new char[codefile_length+1];
                    pthread_mutex_lock(&mpi_mutex);
                    mreq = MPI::COMM_WORLD.Irecv(objectname, objectname_length, MPI_CHAR, source, 11);
                    pthread_mutex_unlock(&mpi_mutex);

                    done = false;
                    while(!done) {
                        pthread_mutex_lock(&mpi_mutex);
                        done = mreq.Test(status);
                        pthread_mutex_unlock(&mpi_mutex);
                    }
                    pthread_mutex_lock(&mpi_mutex);
                    mreq = MPI::COMM_WORLD.Irecv(codefile, codefile_length, MPI_CHAR, source, 13);
                    pthread_mutex_unlock(&mpi_mutex);

                    done = false;
                    while(!done) {
                        pthread_mutex_lock(&mpi_mutex);
                        done = mreq.Test(status);
                        pthread_mutex_unlock(&mpi_mutex);
                    }
                    objectname[objectname_length] = '\0';
                    codefile[codefile_length] = '\0';

                    int usercore;
                    pthread_mutex_lock(&mpi_mutex);
                    mreq = MPI::COMM_WORLD.Irecv(&usercore, 1, MPI_INT, source, 16);
                    pthread_mutex_unlock(&mpi_mutex);

                    done = false;
                    while(!done) {
                        pthread_mutex_lock(&mpi_mutex);
                        done = mreq.Test(status);
                        pthread_mutex_unlock(&mpi_mutex);
                    }

                    // Allocate on the local node
                    char* tmp = new char[15];
                    snprintf(tmp, 15, "uds_%d.%d", rank, next_object_id);
                    next_object_id++;

                    popc_combox_uds receiver;
                    std::string receiver_address(local_address);
                    receiver_address.append("_");
                    receiver_address.append(tmp);
                    receiver.Create(receiver_address.c_str(), true);

                    std::string _objectname("-object=");
                    _objectname.append(objectname);
                    std::string _objectaddress("-address=");
                    _objectaddress.append(tmp);
                    std::string objurl("uds://");
                    objurl.append(tmp);
                    delete [] tmp;
                    std::string objectaddress(objurl.c_str());
                    std::string _receiveraddress("-callback=");
                    _receiveraddress.append(receiver_address);
                    char *localrank = new char[20];
                    snprintf(localrank, 20, "-local_rank=%d", rank);
                    char *coreoption = new char[20];
                    if(usercore != -1) {
                        snprintf(coreoption, 20, "-core=%d", usercore);
                    } else {
                        snprintf(coreoption, 20, "-core=%d", core);
                        core++;
                        if(core == nbcore) {
                            core = 0;
                        }
                    }
//          printf("Exec object %s %s %s %s %s %s\n", codefile, _objectname.c_str(), _objectaddress.c_str(), _receiveraddress.c_str(), localrank, coreoption);
                    // Allocate the object
                    pid_t allocatepid = fork();
                    if(allocatepid == 0) {
                        char* argv1[7];
                        argv1[0] = codefile;                                    // Object executable
                        argv1[1] = const_cast<char*>(_objectname.c_str());      // Object name
                        argv1[2] = const_cast<char*>(_objectaddress.c_str());   // Object address
                        argv1[3] = const_cast<char*>(_receiveraddress.c_str()); // Address of ready call
                        argv1[4] = localrank;                                   // Rank of the creator process
                        argv1[5] = coreoption;                                  // Set the core to run the process
                        argv1[6] = (char*)0;
                        execv(argv1[0], argv1);
                    }
                    delete localrank;
                    delete objectname;
                    delete codefile;
                    paroc_request callback;
                    pop_connection* objectcallback = receiver.Wait();
                    pop_buffer_factory *buffer_factory = objectcallback->GetBufferFactory();
                    callback.data = buffer_factory->CreateBuffer();
                    if(callback.data->Recv(receiver, objectcallback)) {
                        callback.from = connection;
                        const paroc_message_header &callback_header = callback.data->GetHeader();
                        callback.methodId[0] = callback_header.GetClassID();
                        callback.methodId[1] = callback_header.GetMethodID();
                        if(callback.methodId[1] == 200002) {
                            int data[2];
                            data[0] = 15;
                            data[1] = alloc_id;

                            int length = objectaddress.size();
                            pthread_mutex_lock(&mpi_mutex);
                            MPI::COMM_WORLD.Issend(&data, 2, MPI_INT, status.Get_source(), 0);
                            MPI::COMM_WORLD.Issend(&length, 1, MPI_INT, status.Get_source(), 14);
                            MPI::Request sreq = MPI::COMM_WORLD.Issend(objectaddress.c_str(), length, MPI_CHAR, status.Get_source(), 15);
                            pthread_mutex_unlock(&mpi_mutex);

                            MPI::Status status;
                            bool done = false;
                            while(!done) {
                                pthread_mutex_lock(&mpi_mutex);
                                done = sreq.Test(status);
                                pthread_mutex_unlock(&mpi_mutex);
                            }

                        } else {
                            int length = 0;
                            pthread_mutex_lock(&mpi_mutex);
                            MPI::COMM_WORLD.Issend(&length, 1, MPI_INT, status.Get_source(), 14);
                            pthread_mutex_unlock(&mpi_mutex);
                        }
                    }
                    delete callback.data;
                    receiver.Close();
                } else if(request.methodId[1] == 200000) {
                    // Allocation a new parallel object from IPC

                    std::string objectname, codefile;
                    int node, usercore;
                    request.data->Push("objectname", "std::string", 1);
                    request.data->UnPack(&objectname, 1);
                    request.data->Pop();
                    request.data->Push("codefile", "std::string", 1);
                    request.data->UnPack(&codefile, 1);
                    request.data->Pop();
                    request.data->Push("node", "int", 1);
                    request.data->UnPack(&node, 1);
                    request.data->Pop();
                    request.data->Push("core", "int", 1);
                    request.data->UnPack(&usercore, 1);
                    request.data->Pop();


                    if(node != rank && node != -1 && node < world) {
                        // Unlock local MPI receive thread
                        int data[2];
                        data[0] = 12;
                        data[1] = 0;
                        pthread_mutex_lock(&mpi_mutex);
                        MPI::COMM_WORLD.Issend(&data, 2, MPI_INT, rank, 0);
                        pthread_mutex_unlock(&mpi_mutex);


                        // Send signal to the remote node
                        data[0] = 11;
                        int objectname_length = objectname.size();
                        int codefile_length = codefile.size();

                        MPI::Status status;
                        pthread_mutex_lock(&mpi_mutex);
                        MPI::COMM_WORLD.Issend(&data, 2, MPI_INT, node, 0);

                        // Send allocation information to the destination MPI Communicator

                        MPI::COMM_WORLD.Issend(&allocation_id, 1, MPI_INT, node, 17);
                        MPI::COMM_WORLD.Issend(&objectname_length, 1, MPI_INT, node, 10);
                        MPI::COMM_WORLD.Issend(objectname.c_str(), objectname_length, MPI_CHAR, node, 11);
                        MPI::COMM_WORLD.Issend(&codefile_length, 1, MPI_INT, node, 12);
                        MPI::COMM_WORLD.Issend(codefile.c_str(), codefile_length, MPI_CHAR, node, 13);
                        MPI::COMM_WORLD.Issend(&usercore, 1, MPI_INT, node, 16);
                        pthread_mutex_unlock(&mpi_mutex);

                        // Save the allocation identifier to return the object accesspoint
                        pthread_mutex_lock(&allocation_return_map_mutex);
                        allocation_return[allocation_id] = request.from;
                        pthread_mutex_unlock(&allocation_return_map_mutex);

                        // Increment the allocation identifier counter
                        allocation_id++;

                    } else {

                        // Allocate on the local node
                        char* tmp = new char[15];
                        snprintf(tmp, 15, "uds_%d.%d", rank, next_object_id);
                        next_object_id++;

                        popc_combox_uds receiver;
                        std::string receiver_address(local_address);
                        receiver_address.append("_");
                        receiver_address.append(tmp);
                        receiver.Create(receiver_address.c_str(), true);

                        std::string _objectname("-object=");
                        _objectname.append(objectname.c_str());
                        std::string _objectaddress("-address=");
                        _objectaddress.append(tmp);
                        std::string objurl("uds://");
                        objurl.append(tmp);
                        delete [] tmp;
                        std::string objectaddress(objurl.c_str());
                        std::string _receiveraddress("-callback=");
                        _receiveraddress.append(receiver_address);
                        char *localrank = new char[20];
                        snprintf(localrank, 20, "-local_rank=%d", rank);
                        char *coreoption = new char[20];
                        if(usercore != -1) {
                            // Use user defined core distribution
                            snprintf(coreoption, 20, "-core=%d", usercore);
                        } else {
                            // Use round robin distribution on core
                            snprintf(coreoption, 20, "-core=%d", core);
                            core++;
                            if(core == nbcore) {
                                core = 0;
                            }
                        }

                        // Allocate the object
                        pid_t allocatepid = fork();
                        if(allocatepid == 0) {
                            char* argv1[7];
                            // TODO LW: These casts are dangerous, use an array of std::string instead
                            argv1[0] = const_cast<char*>(codefile.c_str());         // Object executable
                            argv1[1] = const_cast<char*>(_objectname.c_str());      // Object name
                            argv1[2] = const_cast<char*>(_objectaddress.c_str());   // Object address
                            argv1[3] = const_cast<char*>(_receiveraddress.c_str()); // Address of ready call
                            argv1[4] = localrank;                                   // Rank of the creator process
                            argv1[5] = coreoption;                                  // Specify the core on which to execute the process
                            argv1[6] = (char*)0;
//            printf("Exec object %s %s %s %s %s %s\n", codefile.c_str(), _objectname.c_str(), _objectaddress.c_str(), _receiveraddress.c_str(), localrank, coreoption);
                            execv(argv1[0], argv1);
                        }
                        delete localrank;
                        delete coreoption;
                        paroc_request callback;
                        pop_connection* objectcallback = receiver.Wait();
                        pop_buffer_factory *buffer_factory = objectcallback->GetBufferFactory();
                        callback.data = buffer_factory->CreateBuffer();
                        if(callback.data->Recv(receiver, objectcallback)) {
                            callback.from = connection;
                            const paroc_message_header &callback_header = callback.data->GetHeader();
                            callback.methodId[0] = callback_header.GetClassID();
                            callback.methodId[1] = callback_header.GetMethodID();
                            if(callback.methodId[1] == 200002) {
                                request.data->Reset();
                                paroc_message_header h("_allocate");
                                request.data->SetHeader(h);
                                request.data->Push("objectaddress", "std::string", 1);
                                request.data->Pack(&objectaddress, 1);
                                request.data->Pop();
                                request.data->Send(request.from);
                            } else {
                                request.data->Reset();
                                paroc_message_header h("_allocate");
                                request.data->SetHeader(h);
                                request.data->Push("objectaddress", "std::string", 1);
                                std::string empty;
                                request.data->Pack(&empty, 1);
                                request.data->Pop();
                                request.data->Send(request.from);
                            }
                        }
                        delete callback.data;
                        receiver.Close();
                    }
                } else if(request.methodId[1] == 200007) {
                    int id, node;
                    request.data->Push("node", "int", 1);
                    request.data->UnPack(&node, 1);
                    request.data->Pop();
                    request.data->Push("id", "int", 1);
                    request.data->UnPack(&id, 1);
                    request.data->Pop();

                    // Receive objaccess from the allocator node
                    int objaccess_length;
                    pthread_mutex_lock(&mpi_mutex);
                    MPI::Request mreq = MPI::COMM_WORLD.Irecv(&objaccess_length, 1, MPI_INT, node, 14);
                    pthread_mutex_unlock(&mpi_mutex);
                    MPI::Status status;
                    bool done = false;
                    while(!done) {
                        pthread_mutex_lock(&mpi_mutex);
                        done = mreq.Test(status);
                        pthread_mutex_unlock(&mpi_mutex);
                    }

                    char* objaccess = new char[objaccess_length+1];
                    pthread_mutex_lock(&mpi_mutex);
                    mreq = MPI::COMM_WORLD.Irecv(objaccess, objaccess_length, MPI_CHAR, node, 15);
                    pthread_mutex_unlock(&mpi_mutex);

                    done = false;
                    while(!done) {
                        pthread_mutex_lock(&mpi_mutex);
                        done = mreq.Test(status);
                        pthread_mutex_unlock(&mpi_mutex);
                    }
                    objaccess[objaccess_length] = '\0';

                    // Return objaccess
                    std::string objectaddress(objaccess);
                    delete [] objaccess;

                    request.data->Reset();
                    paroc_message_header h("_allocate");
                    request.data->SetHeader(h);
                    request.data->Push("objectaddress", "std::string", 1);
                    request.data->Pack(&objectaddress, 1);
                    request.data->Pop();
                    request.data->Send(allocation_return[id]);

                    pthread_mutex_lock(&allocation_return_map_mutex);
                    allocation_return.erase(id);
                    pthread_mutex_unlock(&allocation_return_map_mutex);


                } else if(request.methodId[1] == 200005) {
                    /**
                     *
                     * Receive request from MPI and redirect to IPC object
                     *
                     */

                    int dest_id;
                    int source = request.methodId[0];

                    int tag;
                    request.data->Push("tag", "int", 1);
                    request.data->UnPack(&tag, 1);
                    request.data->Pop();

                    MPI::Status status;

                    pthread_mutex_lock(&mpi_mutex);
                    MPI::Request mreq = MPI::COMM_WORLD.Irecv(&dest_id, 1, MPI_INT, source, tag);
                    pthread_mutex_unlock(&mpi_mutex);

                    bool done = false;
                    while(!done) {
                        pthread_mutex_lock(&mpi_mutex);
                        done = mreq.Test(status);
                        pthread_mutex_unlock(&mpi_mutex);
                    }

                    // Receive the data length
                    int length;
                    pthread_mutex_lock(&mpi_mutex);
                    mreq = MPI::COMM_WORLD.Irecv(&length, 1, MPI_INT, source, tag);
                    pthread_mutex_unlock(&mpi_mutex);

                    done = false;
                    while(!done) {
                        pthread_mutex_lock(&mpi_mutex);
                        done = mreq.Test(status);
                        pthread_mutex_unlock(&mpi_mutex);
                    }

                    if(length <= 0) {
                        printf("POP-C++ Error: MPI Interconnector - request MPI-IPC redirection, length is %d\n", length);
                    }

                    pop_combox* client;
                    pop_connection* connection;

                    if(multiple_connection_enable || connectionmap[pair<int, int>(source, dest_id)] == NULL) {
                        // Need to establish a connection

                        // Connect to the remote object
                        pop_combox_factory* combox_factory = pop_combox_factory::GetInstance();
                        client = combox_factory->Create("uds");
                        char* address = new char[15];
                        snprintf(address, 15, "uds_%d.%d", rank, dest_id);

                        // Save the combox for further communication
                        connectionmap[pair<int, int>(source, dest_id)] = client;


                        client->Create(address, false);
                        if(client->Connect(address)) {
                            // Get the fd associated with the connection
                            connection = client->get_connection();
                            int fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();

                            // Store the tag and source rank to be able to redirect the response
                            outgoingconnection[fd] = pair<int, int>(tag, source);
                            local.add_fd_to_poll(fd);

                        } else {
                            printf("Can't connect\n");
                        }

                        delete address;
                    } else {
                        // Get old combox
                        client = connectionmap[pair<int, int>(source, dest_id)];
                        connection = client->get_connection();
                        int fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();
                        outgoingconnection[fd] = pair<int, int>(tag, source);
                    }

                    char* data = new char[length];
                    // Receive the data
                    pthread_mutex_lock(&mpi_mutex);
                    mreq = MPI::COMM_WORLD.Irecv(data, length, MPI_CHAR, source, tag);
                    pthread_mutex_unlock(&mpi_mutex);

                    done = false;
                    while(!done) {
                        pthread_mutex_lock(&mpi_mutex);
                        done = mreq.Test(status);
                        pthread_mutex_unlock(&mpi_mutex);
                    }



                    if(client->Send(data, length, connection) < 0) {
                        printf("Can't send to final object (rank= %d, tag=%d, source=%d, dest_id=%d, fd=%d)\n", rank, tag,
                               source, dest_id, dynamic_cast<popc_connection_uds*>(connection)->get_fd());
                    }

                    //printf("Request sent length=%d (rank= %d, tag=%d, source=%d, dest_id=%d, fd=%d)\n", length, rank, tag,
                    //  source, dest_id, dynamic_cast<popc_connection_uds*>(connection)->get_fd());
                    delete [] data;

                } else if(request.methodId[1] == 210000) { // Special allocation for XMP process parallel object
                    std::string objectname, codefile;
                    int nb_node;

                    request.data->Push("objectname", "std::string", 1);
                    request.data->UnPack(&objectname, 1);
                    request.data->Pop();

                    request.data->Push("codefile", "std::string", 1);
                    request.data->UnPack(&codefile, 1);
                    request.data->Pop();

                    request.data->Push("objectnb", "int", 1);
                    request.data->UnPack(&nb_node, 1);
                    request.data->Pop();

                    std::string object_option("-object=");
                    object_option.append(objectname.c_str());
                    const char* argv0[] = { object_option.c_str(), (char*)0 };

//          printf("SPAWN will create %d processes (COMM size = %d)\n", nb_node, comm_self.Get_size());
                    const char* commands[nb_node];
                    const char **aargv[nb_node];
                    int maxprocs[nb_node];
                    int errcodes[nb_node];
                    MPI::Info infos[nb_node];

                    for(int i = 0; i < nb_node; i++) {
                        commands[i] = codefile.c_str();
                        aargv[i] = argv0;
                        maxprocs[i] = 1;
                    }



                    pthread_mutex_lock(&mpi_mutex);
                    MPI::Intercomm comm_xmp = comm_self.Spawn_multiple(nb_node, commands, aargv, maxprocs, infos, rank);
                    pthread_mutex_unlock(&mpi_mutex);




                    int fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();
                    object_group[fd] = pair<MPI::Intercomm, int>(comm_xmp, nb_comm);
                    extracomm[nb_comm] = comm_xmp;
                    extrafd[nb_comm] = fd;
                    mpirequest[nb_comm] = comm_xmp.Irecv(&mpidatain[nb_comm], 2, MPI_INT, MPI_ANY_SOURCE, 0);
                    nb_comm++;


                    std::string objectaddress("uds://uds_10.0 uds://uds_11.0");
                    request.data->Reset();
                    paroc_message_header h("_allocate");
                    request.data->SetHeader(h);
                    request.data->Push("objectaddress", "std::string", 1);
                    request.data->Pack(&objectaddress, 1);
                    request.data->Pop();
                    request.data->Send(request.from);






                } else {


                    // Redirect request
                    int fd = dynamic_cast<popc_connection_uds*>(connection)->get_fd();

                    // Redirect response to caller
                    if(outgoingconnection[fd].first != 0) {

                        int dest = outgoingconnection[fd].second;
                        int tag = outgoingconnection[fd].first;
                        //printf("redirect response %d %d\n", dest, tag);
                        int data[2];
                        data[0] = 14;
                        data[1] = tag;

                        pthread_mutex_lock(&mpi_mutex);
                        MPI::COMM_WORLD.Issend(&data, 2, MPI_INT, dest, 0);

                        // Send length of the request
                        int length = request.data->get_size();
                        MPI::COMM_WORLD.Issend(&length, 1, MPI_INT, dest, tag);
                        char *load = request.data->get_load();
                        MPI::Request sreq = MPI::COMM_WORLD.Issend(load, length, MPI_CHAR, dest, tag);
                        pthread_mutex_unlock(&mpi_mutex);

                        MPI::Status status;
                        bool done = false;
                        while(!done) {
                            pthread_mutex_lock(&mpi_mutex);
                            done = sreq.Test(status);
                            pthread_mutex_unlock(&mpi_mutex);
                        }
                        //printf("redirect response done\n");
                        // Clean the entry in the outgoing map
                        outgoingconnection.erase(fd);

                    } else {
                        if(object_group.find(fd) != object_group.end()) {
                            //printf("In POPMPI Interconnector for Interface group redirection: %d\n", object_group[fd].Get_remote_size());

                            if(request.methodId[1] == 9) { // Set the single recipient of next call
                                int rank;
                                request.data->Push("rank", "int", 1);
                                request.data->UnPack(&rank, 1);
                                request.data->Pop();
                                object_group_single[fd] = rank;
                            } else {
                                if(object_group_single.find(fd) == object_group_single.end()) {


//                    printf("COLLECTIVE CALL %d\n", request.methodId[1]);
                                    int world_size = object_group[fd].first.Get_remote_size();
                                    int data[2];
                                    data[0] = 13;

                                    // Get the request message length
                                    int length = request.data->get_size();
                                    if(length <= 0) {
                                        printf("POP-C++ Error: MPI Interconnector - request IPC-MPI redirection, length is %d\n", length);
                                    }
                                    data[1] = length;

                                    // Get a pointer to the data buffer
                                    char *load = request.data->get_load();

                                    // Forward the request to all process
                                    // Improvements with MPI-3: Use Ibroadcast instead of a loop
                                    // Send a command to tell the broker side to call a broadcast
                                    // sreq = object_group[fd].first.Ibroadcast();
                                    for(int i = 0; i < world_size; i++) {
                                        MPI::Request sreq;
                                        MPI::Status status;

                                        pthread_mutex_lock(&mpi_mutex);
                                        sreq = object_group[fd].first.Isend(&data, 2, MPI_INT, i, 0);
                                        sreq = object_group[fd].first.Isend(load, length, MPI_CHAR, i, 2);
                                        pthread_mutex_unlock(&mpi_mutex);

                                        bool done = false;
                                        while(!done) {
                                            pthread_mutex_lock(&mpi_mutex);
                                            done = sreq.Test(status);
                                            pthread_mutex_unlock(&mpi_mutex);
                                        }
                                    }

                                    // Signal finalize() that object group were signaled for termination
                                    // TODO make signal by a process itself
                                    if(request.methodId[1] == 2) {
                                        request.data->Reset();
                                        paroc_message_header h("_finalize");
                                        request.data->SetHeader(h);
                                        request.data->Send(request.from);
                                    }

                                } else {
                                    //printf("NON-COLLECTIVE CALL TO %d\n", object_group_single[fd]);
                                    int data[2];
                                    data[0] = 13;

                                    // Get the request message length
                                    int length = request.data->get_size();
                                    if(length <= 0) {
                                        printf("POP-C++ Error: MPI Interconnector - request IPC-MPI redirection, length is %d\n", length);
                                    }

                                    data[1] = length;

                                    // Get a pointer to the data buffer
                                    char *load = request.data->get_load();

                                    MPI::Request sreq;
                                    MPI::Status status;

                                    pthread_mutex_lock(&mpi_mutex);
                                    sreq = object_group[fd].first.Isend(&data, 2, MPI_INT, object_group_single[fd], 0);
                                    sreq = object_group[fd].first.Isend(load, length, MPI_CHAR, object_group_single[fd], 2);
                                    pthread_mutex_unlock(&mpi_mutex);

                                    bool done = false;
                                    while(!done) {
                                        pthread_mutex_lock(&mpi_mutex);
                                        done = sreq.Test(status);
                                        pthread_mutex_unlock(&mpi_mutex);
                                    }

                                    object_group_single.erase(fd);
                                }
                            }
                        } else {
                            /**
                             * Redirect the request to the parallel object via MPI
                             * This part of the code redirect the message from this POP-C++ MPI Interconnector to the end POP-C++ MPI
                             * Interconnector
                             */

                            // Get the destination node and parallel object identifier from the incoming connection map.
                            int dest_node = incomingconnection[fd].first;
                            int dest_id = incomingconnection[fd].second;

                            pthread_mutex_lock(&incoming_tag_map_mutex);
                            incomingtag[next_tag] = fd;
                            pthread_mutex_unlock(&incoming_tag_map_mutex);

                            // Prepare command message's data
                            int data[2];
                            data[0] = 13;
                            data[1] = next_tag;

                            // Get the request message length
                            int length = request.data->get_size();
                            if(length <= 0) {
                                printf("POP-C++ Error: MPI Interconnector - request IPC-MPI redirection, length is %d\n", length);
                            }

                            // Get a pointer to the data buffer
                            char *load = request.data->get_load();

                            // Lock and send asynchronously the information about the message.
                            pthread_mutex_lock(&mpi_mutex);
                            MPI::COMM_WORLD.Issend(&data, 2, MPI_INT, dest_node, 0);
                            MPI::COMM_WORLD.Issend(&dest_id, 1, MPI_INT, dest_node, next_tag);
                            MPI::COMM_WORLD.Issend(&length, 1, MPI_INT, dest_node, next_tag);
                            MPI::Request sreq = MPI::COMM_WORLD.Issend(load, length, MPI_CHAR, dest_node, next_tag);
                            pthread_mutex_unlock(&mpi_mutex);
                            MPI::Status status;
                            bool done = false;
                            while(!done) {
                                pthread_mutex_lock(&mpi_mutex);
                                done = sreq.Test(status);
                                pthread_mutex_unlock(&mpi_mutex);
                            }

                            //printf("redirect request done\n");

                            // Save the fd corresponding to the tag included in the message. Will be used for redirection to the caller


                            // Increment the tag to differentiate messages
                            next_tag++;
                        }
                    }
                }
                // Delete the buffer
                delete request.data;
            }
        }
    }

    /**
     *
     * End of the POP-C++ MPI Interconnector
     *
     * Clean all the allocated maps and objects
     *
     */

    // Close the local UDS Server
    local.Close();

    // Clean the incoming connection map
    while(!incomingconnection.empty()) {
        incomingconnection.erase(incomingconnection.begin());
    }

    // Clean the incoming tag map
    while(!incomingtag.empty()) {
        incomingtag.erase(incomingtag.begin());
    }

    // Clean the outgoing connection map
    while(!outgoingconnection.empty()) {
        outgoingconnection.erase(outgoingconnection.begin());
    }

    // Delete connection to object
    map<pair<int, int>, pop_combox*>::iterator it;
    for(it = connectionmap.begin() ; it != connectionmap.end(); it++) {
        ((*it).second)->Close();
        delete dynamic_cast<popc_combox_uds*>((*it).second);
    }

    // Delete communicator for object group
    while(!object_group.empty()) {
        object_group.erase(object_group.begin());
    }


    // Wait for the MPI receive thread and destroy attribute and mutex lock
    pthread_join(mpithread, NULL);
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&mpi_mutex);



    // Free communicators
    comm_world_dup.Free();
    comm_self.Free();


    // Finalize the MPI process
    MPI::Finalize();
    exit(main_return_value);
}

