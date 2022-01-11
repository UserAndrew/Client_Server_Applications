#include "Server.h"

int Server::initWinsock()
{
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

int Server::setConnectionParameters()
{
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    
    return getaddrinfo(NULL, "2000", &hints, &addrResult);
}

ParseResult Server::createListenSocket()
{
    listenSocket = socket(addrResult->ai_family, addrResult->ai_socktype,\
        addrResult->ai_protocol);
    if (listenSocket == INVALID_SOCKET)
    {
        std::cout << "Socket created failed." << std::endl;
        freeaddrinfo(addrResult);
        WSACleanup();
        return ParseResult::MY_INVALID_SOCKET;
    }
    else
    {
        std::cout << "Socket created success." << std::endl;
        return ParseResult::SUCCESS;
    }
}

ParseResult Server::serverSocketBinding()
{
    int binding = bind(listenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if (binding == SOCKET_ERROR)
    {
        std::cout << "Binding socket failed." << std::endl;
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);
        WSACleanup();
        return ParseResult::MY_SOCKET_ERROR;
    }
    else
    {
        std::cout << "Binding socket succes!" << std::endl;
    }
    return ParseResult::SUCCESS;
}

ParseResult Server::setListenSocket()
{
    int listening = listen(listenSocket, SOMAXCONN);
    if (listening == SOCKET_ERROR)
    {
        std::cout << "Listenig socket failed." << std::endl;
        closesocket(listenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return ParseResult::MY_SOCKET_ERROR;
    }
    else
    {
        std::cout << "Listening socket succes!" << std::endl;
    }

    return ParseResult::SUCCESS;
}

ParseResult Server::createClientSocket()
{
    clientSocket = accept(listenSocket, NULL, NULL);
                                               
    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "Accepting socket failed." << std::endl;
        closesocket(listenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return ParseResult::MY_INVALID_SOCKET;
    }
    else
    {
        std::cout << "Accepting socket succes!" << std::endl;
        closesocket(listenSocket);
        return ParseResult::SUCCESS;
    }
}