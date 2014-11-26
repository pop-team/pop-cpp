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
 * Authors      Date            Comment
 */

#include "popc_intface.h"

#ifndef __APPLE__
#include <sched.h>
#endif

#include "paroc_utils.h"
#include "paroc_system.h"
#include "paroc_broker.h"
#include "paroc_broker_factory.h"
#include "paroc_buffer_factory_finder.h"

bool CheckIfPacked(const char *objname);

int main(int argc, char **argv)
{
    char *rcore=paroc_utils::checkremove(&argc,&argv,"-core=");
    if (rcore) {
        paroc_system::processor_set(atoi(rcore));
    }

#ifdef UC_LINUX
    else paroc_system::processor_set(0);
#endif

    paroc_system sys;
    char *local_rank = paroc_utils::checkremove(&argc, &argv, "-local_rank=");

    if(local_rank != NULL) {
        paroc_system::popc_local_mpi_communicator_rank = atoi(local_rank);
    }

    // Connect to callback
    char *address = paroc_utils::checkremove(&argc, &argv, "-callback=");
    paroc_combox *callback = NULL;
    int status=0;
    if (address != NULL) {
        paroc_combox_factory *combox_factory = paroc_combox_factory::GetInstance();
#ifdef DEFINE_UDS_SUPPORT
        callback = combox_factory->Create("uds");

        if(!callback->Create(address, false) || !callback->Connect(address)) {
#else
        callback = combox_factory->Create("socket");

        if(!callback->Create(0, false) || !callback->Connect(address)) {
#endif
            callback->Close();
            callback->Destroy();
            printf("POP-C++ Error: fail to connect to callback. Check that the URL %s belongs to a node.\n", address);
            return 1;
        }
    }

    paroc_broker_factory::CheckIfPacked = &CheckIfPacked; // transmit the address of the check function to broker factory
    paroc_broker *broker = paroc_broker_factory::Create(&argc, &argv);

    if (!broker) {
        status = 1;
    } else if (!broker->Initialize(&argc, &argv)) {
        printf("Fail to initialize the broker for class %s\n",(const char *)paroc_broker::classname);
        status = 1;
    }

    // Send ack via callback
    if (callback != NULL) {
        paroc_buffer *buffer = callback->GetBufferFactory()->CreateBuffer();
        paroc_message_header h(0, 200002, INVOKE_SYNC, "_callback");
        buffer->SetHeader(h);

        buffer->Push("status", "int", 1);
        buffer->Pack(&status, 1);
        buffer->Pop();

        buffer->Push("address", "paroc_accesspoint", 1);
        paroc_broker::accesspoint.Serialize(*buffer, true);
        buffer->Pop();

        paroc_connection* connection = callback->get_connection();
        bool ret = buffer->Send((*callback), connection);
        buffer->Destroy();
        callback->Destroy();

        if (!ret) {
            printf("POP-C++ Error: fail to send accesspoint via callback\n");
            delete broker;
            return 1;
        }
    } else if (status == 0) {
        fprintf(stdout, "%s\n", (const char *)paroc_broker::accesspoint.GetAccessString());
    }

    // set the current working directory
    char *cwd = paroc_utils::checkremove(&argc,&argv,"-cwd=");
    if (cwd!=NULL) {
        if (popc_chdir(cwd) != 0) {
            printf("POP-C++ Error: [CORE] - current working dir cannot be set set to %s",cwd);
        }
    }

    // Start the broker
    if (status == 0) {
        broker->Run();
        delete broker;
    } else if (broker != NULL) {
        delete broker;
    }

    return status;
}
