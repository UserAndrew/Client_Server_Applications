//#include <iostream>
#include "Server.h"

int main()
{
    SetConsoleTitle("Server Application");
    int result;
    SOCKET socket = INVALID_SOCKET;
    Server server;

    server.startServer();
    server.receiveFromClient();
}
