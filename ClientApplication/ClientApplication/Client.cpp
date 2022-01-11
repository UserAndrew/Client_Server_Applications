#include "Client.h"

void Client::printCurrentProcessId()
{
    std::cout << "Process id of this program is: " << GetCurrentProcessId() << std::endl;
}
int Client::initWinsock()
{
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

int Client::setConnectionParameters()
{
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    return getaddrinfo("localhost", "2000", &hints, &addrResult);
}

ParseResult Client::createConnectSocket()
{
    connectSocket = socket(addrResult->ai_family, addrResult->ai_socktype, \
        addrResult->ai_protocol);
    if (connectSocket == INVALID_SOCKET)
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

ParseResult Client::createConnectToServer()
{
    int result;
    result = connect(connectSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if (result == SOCKET_ERROR)
    {
        std::cout << "Unable connect to server." << std::endl;
        closesocket(connectSocket);//�.�. ���������� �� ����������, ����� ���������� �������
        connectSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);
        WSACleanup();
        return ParseResult::MY_SOCKET_ERROR;
    }
    else
    {
        std::cout << "Client connected!" << std::endl;
        return ParseResult::SUCCESS;
    }
}