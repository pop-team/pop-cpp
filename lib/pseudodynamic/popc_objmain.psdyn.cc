/**
 * File : paroc_objmain.std.cc
 * Author : Tuan Anh Nguyen
 * Description : "main" entry for the object executable
 * Initialization of parallel objects
 * The Job service can pass to a parallel object environment by:
 * 1- Specify the argument -jobservice=<code services...> when launching the object binary code (not used by the Interface)
 * 2- Set environment variable "POPC_JOBSERVICE to the job service point
 * 3- <localhost>:2711 ( if 1/ and 2/ are not specified )
 * Creation date : -
 *
 * Modifications :
 * Authors      Date              Comment
 * P.Kuonen   2012/09/18  Add "POP-C++ error" in error messages (PEKA)
 * clementval 2012/09/27  Code cleaning (indent, convention ...)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "paroc_broker.h"
#include "paroc_utils.h"
#include "paroc_system_mpi.h"
#include "paroc_broker_factory.h"
#include "pop_buffer_factory_finder.h"



bool CheckIfPacked(const char *objname);

//extern paroc_broker *InitBroker(char *objname);
//extern void QueryObjectList(char *str, int n);


int main(int argc, char **argv) {



    // If the application is using MPI Communication support
    if(paroc_utils::checkremove(&argc, &argv, "-mpi") != NULL) {
        LOG_DEBUG("-mpi found");
        // Init MPI for multithread support
        if(!MPI::Is_initialized()) {
            LOG_DEBUG("init");
            // Init MPI for multithread support
            int required_support = MPI_THREAD_SERIALIZED; // Required multiple thread support to allow multiple connection to an object
            int provided_support = MPI::Init_thread(required_support);
            LOG_DEBUG("init end");
        }
        paroc_system_mpi::is_remote_object_process = true;
        int node_id = MPI::COMM_WORLD.Get_rank();

        LOG_DEBUG("Broker main %d", node_id);
        MPI::Status status;
        int dummy;
        MPI::COMM_WORLD.Recv(&dummy, 1, MPI_INT, MPI_ANY_SOURCE, 15, status);
        int source = status.Get_source();
        LOG_DEBUG("recv %d", dummy);
        // Send my rank for confirmation

        MPI::COMM_WORLD.Send(&node_id, 1, MPI_INT, source, 16);
        LOG_DEBUG("send %d rank", node_id);
    }




    char *rcore = paroc_utils::checkremove(&argc,&argv,"-core=");
    if(rcore != NULL) {
        paroc_system::processor_set(atoi(rcore));
    }
#ifdef UC_LINUX
    else {
        paroc_system::processor_set(0);
    }
#endif

    paroc_system sys;
    int status = 0;
    paroc_combox *callback = NULL;
    // Connect to callback
    // No need in MPI version, connection is already active and can exchange data
    /*char *addr = paroc_utils::checkremove(&argc, &argv, "-callback=");
    if (addr != NULL) {
        paroc_combox_factory *combox_factory = paroc_combox_factory::GetInstance();

        char *tmp = strstr(addr, "://");
        if (tmp == NULL) {
          callback = combox_factory->Create("socket");
        } else {
            *tmp = 0;
            callback = combox_factory->Create(addr);
            *tmp = ':';
        }

        if (!callback->Create(NULL, 0, false) || !callback->Connect(addr)) {
            delete callback;
            return 1;
        }
    }*/

    paroc_broker_factory::CheckIfPacked = &CheckIfPacked; // transmit the address of the check function to broker factory
    paroc_broker *broker_factory = paroc_broker_factory::Create(&argc, &argv);

    if(broker_factory == NULL) {
        status = 1;
    } else if(!broker_factory->Initialize(&argc, &argv)) {
        // Initialize broker
        LOG_ERROR("Fail to initialize the broker for class %s", paroc_broker::classname.c_str());
        status = 1;
    }
    LOG_DEBUG("broker: init");


    // Send accesspoint via callback
    if(callback != NULL) {
        LOG_DEBUG("BROKER: Sending status and accesspoint");
        char url[1024];
        int len;

        // Connect to the end point
        paroc_connection* connection = callback->get_connection();

        pop_buffer *buf = callback->GetBufferFactory()->CreateBuffer();

        paroc_message_header h("Callback");
        buf->SetHeader(h);

        buf->Push("status", "int", 1);
        buf->Pack(&status, 1);
        buf->Pop();

        LOG_DEBUG("BROKER: status sent %d", status);

        buf->Push("address", "paroc_accesspoint", 1);
        paroc_broker::accesspoint.Serialize(*buf,true);
        buf->Pop();


        bool ret = buf->Send((*callback), connection);

        delete buf;

        connection->reset();
        delete callback;

        if(!ret) {
            LOG_ERROR("fail to send accesspoint via callback");
            delete broker_factory;
            MPI::Finalize();
            return 1;
        }
    } /* else if (status == 0) {
        //LOG_INFO("%s", (const char *)paroc_broker::accesspoint.GetAccessString());
    }*/

    // Set the current working directory
    char *cwd = paroc_utils::checkremove(&argc,&argv,"-cwd=");
    if(cwd != NULL) {
        if(chdir(cwd) != 0) {
            LOG_DEBUG("current working dir cannot be set set to %s",cwd);
        }
    }

    // Start the broker
    if(status == 0) {
        broker_factory->Run();
        LOG_DEBUG("Broker started");
        delete broker_factory;
    } else if(broker_factory != NULL) {
        delete broker_factory;
        MPI::Finalize();
    }



    return status;
}
