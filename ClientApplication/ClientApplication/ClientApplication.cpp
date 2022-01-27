#include <iostream>
//#include <thread>
#include "Client.h"

int main(int argc, char* argv[])
{
    SetConsoleTitle("Clien Application");
    Client client;

    client.startClient();
    
    StepsOfProcessing steps{};
    if (argc == 1)
    {
        std::cout << "Enter an argument!" << std::endl;
        return 1;
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "0") == 0)
        {
            steps = StepsOfProcessing::DEFINITION;
        }
        else if (strcmp(argv[1], "1") == 0)
        {
            steps = StepsOfProcessing::DEF_HASH;
        }
        else if (strcmp(argv[1], "2") == 0)
        {
            steps = StepsOfProcessing::COMPR_DEF_HASH;
        }
        else if (strcmp(argv[1], "3") == 0)
        {
            steps = StepsOfProcessing::DEF_ZIP_HASH;
        }
        else std::cout << "Incorrect argument." << std::endl;
    }
    else if (argc > 2)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return 1;
    }
    client.prepareDataForServer(steps);
    client.sendMessageToServer();

    return 0;
}
