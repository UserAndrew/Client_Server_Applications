//#include <iostream>
#include "Client.h"

int main(int argc, char* argv[])
{
    SetConsoleTitle("Clien Application");
    
    Client client;
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
            std::cout << "Entered 0" << std::endl;

            steps = StepsOfProcessing::DEFINITION;
        }
        else if (strcmp(argv[1], "1") == 0)
        {
            std::cout << "Entered 1" << std::endl;
            steps = StepsOfProcessing::COMPR_DEF;
        }
        else if (strcmp(argv[1], "2") == 0)
        {
            std::cout << "Entered 2" << std::endl;
            steps = StepsOfProcessing::DEF_HASH;
        }
        else if (strcmp(argv[1], "3") == 0)
        {
            std::cout << "Entered 3" << std::endl;
            steps = StepsOfProcessing::COMPR_DEF_HASH;
        }
        else if (strcmp(argv[1], "4") == 0)
        {
            std::cout << "Entered 4" << std::endl;
            steps = StepsOfProcessing::DEF_ZIP_HASH;
        }
        else
        {
            std::cout << "Incorrect argument." << std::endl;
            return 0;
        }
    }
    else if (argc > 2)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return 1;
    }

    //Client client;

    client.startClient();
    client.choiceMethodProcessing(steps);
    client.sendMessageToServer();
    //client.recvMessageFromServer();
    client.shutdownSocket();

    return 0;
}
