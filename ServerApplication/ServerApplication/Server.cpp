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

ParseResult Server::createClientSocket(SOCKET clientSocket)
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

int Server::startServer()
{
    int result;
    result = initWinsock();
    if (result != 0)
    {
        std::cout << "WSAStartup failed, result = " << result << std::endl;
        return 1;
    }
    else
    {
        std::cout << "WSAStartup succes." << std::endl;
    }

    result = setConnectionParameters();
    if (result != 0)
    {
        std::cout << "getaddrinfo failed with error #" << result << std::endl;
        WSACleanup();
        return 1;
    }

    createListenSocket();
    serverSocketBinding();
    setListenSocket();
    //createClientSocket();
    return 0;
}

int Server::receiveFromClient(SOCKET clientSocket)
{
    int result;
    ZeroMemory(recvBuffer, sizeof(recvBuffer));
    result = recv(clientSocket, recvBuffer, 512, 0);
    if (result > 0)
    {
        std::cout << "Received " << result << " bytes." << std::endl;
        std::cout << "Received data: " << recvBuffer << std::endl;

    }
    else if (result == 0)
    {
        std::cout << "Connection closing..." << std::endl;
    }
    else
    {
        std::cout << "receive failed with error#" << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }
    return 0;
}

void Server::Attach(IObserver* observer)
{
    m_list_observer.push_back(observer);
}

void Server::Detach(IObserver* observer)
{
    m_list_observer.remove(observer);
}

void Server::Notify()
{
    std::list<IObserver*>::iterator iterator = m_list_observer.begin();
    while (iterator != m_list_observer.end()) {
        (*iterator)->Update(m_message);
        ++iterator;
    }
}

void Server::fillMessage()
{
    std::string &message = m_message;
    int i = 0;
    while (recvBuffer[i] != '\0')
    {
        message[i] = recvBuffer[i];
        i++;
    }
}

void Server::printResult()
{
    std::cout << m_message;
}

void Server::shutdownClientSocket(SOCKET clientSocket)
{
    int result = shutdown(clientSocket, SD_BOTH);
    if (result == SOCKET_ERROR)
    {
        std::cout << "Shutdown client socket failed." << std::endl;
        closesocket(clientSocket);
        freeaddrinfo(addrResult);
        WSACleanup();

    }

    std::cout << "Shutdown client socket succes." << std::endl;
    closesocket(clientSocket);
    //freeaddrinfo(addrResult);
    //WSACleanup();
}

void Server::recieveAndProcessDataOnTheServer(SOCKET clientSocket)
{
    //createClientSocket();
    receiveFromClient(clientSocket);
    shutdownClientSocket(clientSocket);
    addDataToContainer();
}

void Server::addDataToContainer()
{
    std::string data;
    std::stringstream ss;
    ss << recvBuffer;
    data = ss.str();
    my_data.push_back(data);
}

Server::~Server()
{
    std::ofstream fout("DataServer.txt"); 
    for (auto &i : my_data)
    {
        fout << i;
    }
    fout.close();
}