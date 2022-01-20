#include <iostream>
#include "Client.h"

int main()
{
    SetConsoleTitle("Clien Application");
    Client client;

    client.startClient();
    client.sendMessageToServer();

    return 0;
}
