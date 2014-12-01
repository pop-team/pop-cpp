#include "combox.h"
#include <iostream>

int main(int argc, char* argv[]) {
    popc_combox_uds client;
    client.Create("uds_server01", false);
    popc_connection_uds* connection = client.combox_connect();

    char* buffer = new char[21];
    snprintf(buffer, 21, "01234567890123456789");

    client.Send(buffer, 21, connection);

    char rcvbuffer[21];
    client.Recv(rcvbuffer, 21, connection);

    rcvbuffer[21] = '\0';
    printf("Client recv %s\n", rcvbuffer);

    client.Close();



    return 0;
}