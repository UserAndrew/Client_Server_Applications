//#include <iostream>
#include "Observer.h"
#include <thread>

void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";

    exit(0);
} 

int main()
{
    SetConsoleTitle("Server Application");

    Server server;

    server.startServer();

    SOCKET new_connection{};
    //for (int i = 0; i < 5; i++)
    signal(SIGINT, signalHandler);
    //std::string my_key;
    int i = 0;
    for(;;)
    {
        
        std::cout << "Iteration # " << i + 1 << std::endl;
        new_connection = accept(server.listenSocket, NULL, NULL);
        if (new_connection == 0) {
            std::cout << "Error #2\n";
        }
        else {
            std::cout << "Client Connected!\n";

            //server.clientSocket[i] = new_connection;
            SOCKET clientSocket = new_connection;
            std::thread new_thread(&Server::recieveAndProcessDataOnTheServer, &server, clientSocket);
            new_thread.join();
        }
        i++;
        //std::cout << "Press q to quit or another any key to continue." << std::endl;
        //std::cin >> my_key;
        //if (my_key == "q") break;
        //else continue;
    }
    
    
    /*Observer* observer_decompr = new Observer(server);
    server.fillMessage();
    server.Notify();
    server.printResult();*/

    return 0;
}
