#include "combox.h"

int main(int argc, char* argv[]) {
    popc_combox_uds server;
    if (!server.Create("uds_server01", true)) {
        printf("Server couldn't be created\n");
        return 1;
    }

    printf("Server created\n");

    server.set_timeout(-1);
    int message = 0;
    bool active = true;
    while (active) {
        printf("wait\n");
        popc_connection_uds* connection = server.Wait();

        if (connection != NULL) {
            char buffer[21];
            server.Recv(buffer, 21, connection);
            printf("Server: %s\n", buffer);
            server.Send(buffer, 21, connection);
        }
    }

    server.Close();
    return 0;
}