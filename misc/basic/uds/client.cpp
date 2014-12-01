#include "combox.h"
#include <iostream>

int main(int argc, char* argv[]) {
    popc_combox_uds client;
    client.Create("uds_server01", false);
    popc_connection_uds* connection = client.combox_connect();

    char* buffer = new char[21];
    snprintf(buffer, sizeof(buffer), "01234567890123456789");

    client.Send(buffer, sizeof(buffer), connection);

    char rcvbuffer[21];
    client.Recv(rcvbuffer, sizeof(rcvbuffer), connection);

    rcvbuffer[21] = '\0';
    printf("Client recv %s\n", rcvbuffer);

    client.Close();



    return 0;
}
