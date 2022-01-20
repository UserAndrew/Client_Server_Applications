#include <iostream>
#include "Client.h"

int main()
{
    SetConsoleTitle("Clien Application");
    int result;
    Client client;

    client.startClient();
    client.sendMessageToServer();
}

