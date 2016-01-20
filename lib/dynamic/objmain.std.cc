/**
 * File : objmain.std.cc
 * Author : Tuan Anh Nguyen
 * Description : "main" entry for the object executable
 * Initialization of parallel objects
 * The Job service can pass to a parallel object environment by:
 * 1- Specify the argument -jobservice=<code services...> when launching the object binary code (not used by the
 *Interface)
 * 2- Set environment variable "POPC_JOBSERVICE to the job service point
 * 3- <localhost>:2711 ( if 1/ and 2/ are not specified )
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 */

#include "pop_intface.h"

#ifndef __APPLE__
#include <sched.h>
#endif

#include "pop_utils.h"
#include "pop_system.h"
#include "pop_broker.h"
#include "pop_broker_factory.h"
#include "pop_buffer_factory_finder.h"

bool CheckIfPacked(const char* objname);

std::string get_proto_name(const char* address) {
    std::string address_str(address);

    if (address_str.find("uds://") == 0) {
        return "uds";
    } else {
        return "socket";
    }
}

int main(int argc, char** argv) {
    char* rcore = pop_utils::checkremove(&argc, &argv, "-core=");
    if (rcore) {
        pop_system::processor_set(atoi(rcore));
    }
#ifdef UC_LINUX
    else {
        pop_system::processor_set(0);
    }
#endif

    pop_system sys;
    char* local_rank = pop_utils::checkremove(&argc, &argv, "-local_rank=");

    if (local_rank) {
        pop_system::popc_local_mpi_communicator_rank = atoi(local_rank);
    }

    // Connect to callback
    char* address = pop_utils::checkremove(&argc, &argv, "-callback=");
    pop_combox* callback_combox = nullptr;
    int status = 0;
    if (address != NULL) {
        auto& combox_factory = pop_combox_factory::get_instance();

        auto protocol = get_proto_name(address);
        callback_combox = combox_factory.Create(protocol.c_str());

        bool connected;
        if (callback_combox->need_address()) {
            connected = callback_combox->Create(address, false) && callback_combox->Connect(address);
        } else {
            connected = callback_combox->Create(0, false) && callback_combox->Connect(address);
        }

        if (!connected) {
            callback_combox->Close();
            delete callback_combox;
            LOG_INFO("POP-C++ Error: fail to connect to callback. Check that the URL %s belongs to a node.", address);
            return 1;
        }
    }

    pop_broker_factory::CheckIfPacked = &CheckIfPacked;  // transmit the address of the check function to broker factory
    pop_broker* broker = pop_broker_factory::Create(&argc, &argv);

    if (!broker) {
        status = 1;
    } else if (!broker->Initialize(&argc, &argv)) {
        LOG_INFO("Fail to initialize the broker for class %s", pop_broker::classname.c_str());
        status = 1;
    }

    // Send ack via callback
    if (callback_combox != NULL) {
        pop_buffer* buffer = callback_combox->GetBufferFactory()->CreateBuffer();
        pop_message_header h(-1, 0, 200002, INVOKE_SYNC, "_callback");
        buffer->SetHeader(h);

        buffer->Push("status", "int", 1);
        buffer->Pack(&status, 1);
        buffer->Pop();

        buffer->Push("address", "pop_accesspoint", 1);
        pop_broker::accesspoint.Serialize(*buffer, true);
        buffer->Pop();

        pop_connection* connection = callback_combox->get_connection();
        bool ret = buffer->Send((*callback_combox), connection);
        delete buffer;
        delete callback_combox;

        if (!ret) {
            LOG_ERROR("POP-C++ Error: fail to send accesspoint via callback");
            delete broker;
            return 1;
        }
    } else if (status == 0) {
        LOG_INFO("%s", pop_broker::accesspoint.GetAccessString().c_str());
    }

    // set the current working directory
    char* cwd = pop_utils::checkremove(&argc, &argv, "-cwd=");
    if (cwd != NULL) {
        if (popc_chdir(cwd) != 0) {
            LOG_ERROR("POP-C++ Error: [CORE] - current working dir cannot be set set to %s", cwd);
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
