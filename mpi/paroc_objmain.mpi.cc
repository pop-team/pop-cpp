/*Initialization of parallel objects
The Job service can pass to a parallel object environment by:
1- Specify the argument -jobservice=<code services...> when launching the object binary code (not used by the Interface)
2- Set environment variable "POPC_JOBSERVICE to the job service point
3- <localhost>:2711 ( if 1/ and 2/ are not specified )
*/
#include "mpi.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "pop_broker.h"
#include "pop_broker_factory.h"

#include "appservice.ph"
#include "pop_buffer_factory_finder.h"

bool CheckIfPacked(const char* objname);

int main(int argc, char** argv) {
    pop_system sys;

    // Init MPI first....
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
        printf("MPI_Init error\n");
        return 1;
    }

    // Connect to callback ....
    char* addr = pop_utils::checkremove(&argc, &argv, "-callback=");
    pop_combox* callback = NULL;
    int status = 0;
    if (addr != NULL) {
        char* tmp = strstr(addr, "://");
        pop_combox_factory* fact = pop_combox_factory::GetInstance();

        if (tmp == NULL) {
            callback = fact->Create("socket");
        } else {
            *tmp = 0;
            callback = fact->Create(addr);
            *tmp = ':';
        }

        if (!callback->Create(0, false) || !callback->Connect(addr)) {
            delete callback;
            printf("Error: fail to connect to callback. Check that the URL %s belongs to a node.\n", addr);
            return 1;
        }
    }
    pop_broker_factory::CheckIfPacked = &CheckIfPacked;  // transmit the address of the check function to broker factory
    pop_broker* br = pop_broker_factory::Create(&argc, &argv);
    if (br == NULL) {
        status = 1;
    } else if (!br->Initialize(&argc, &argv)) {
        // Initialize broker...
        printf("Fail to initialize the broker for class %s\n", (const char*)pop_broker::classname);
        status = 1;
    }

    // Send accesspoint via callback

    int rank = 0;
    int size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank > 0) {
        MPI_Status status;
        int t;
        MPI_Recv(&t, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
    }

    if (callback != NULL) {
        char url[1024];
        int len;
        pop_buffer* buf = callback->GetBufferFactory()->CreateBuffer();
        pop_message_header h("Callback");
        buf->SetHeader(h);

        buf->Push("status", "int", 1);
        buf->Pack(&status, 1);
        buf->Pop();

        buf->Push("address", "pop_accesspoint", 1);
        pop_broker::accesspoint.Serialize(*buf, true);
        buf->Pop();

        bool ret = buf->Send(*callback);
        delete buf;
        delete callback;
        if (!ret) {
            rprintf("Error: fail to send accesspoint via callback\n");
            delete br;
            MPI_Finalize();
            return 1;
        }
    } else if (status == 0) {
        fprintf(stdout, "%s\n", (const char*)pop_broker::accesspoint.GetAccessString());
    }
    char* cwd = pop_utils::checkremove(&argc, &argv, "-cwd=");
    if (cwd != NULL) {
        if (chdir(cwd) != 0) {
            LOG_WARNING("current working dir cannot be set set to %s", cwd);
        }
    }  // else DEBUG("cwd not set");

    if (rank < size - 1) {
        MPI_Send(&rank, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

#ifdef OD_DISCONNECT
    bool checkConnect = (pop_utils::checkremove(&argc, &argv, "-checkConnection")) != NULL;
    if (br != NULL) {
        br->checkConnection = checkConnect;
    }
#endif

    // Now ....start broker....
    if (status == 0) {
        br->Run();
        delete br;
    } else if (br != NULL) {
        delete br;
    }

    MPI_Finalize();
    return status;
}
