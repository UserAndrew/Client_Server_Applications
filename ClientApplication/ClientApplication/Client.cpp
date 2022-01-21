#include "Client.h"
#include "getSymbol.h"
#include <sstream>


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
        closesocket(connectSocket);
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

std::string Client::getMinimumMessage()
{
    DWORD pid = GetCurrentProcessId();
    std::string result = convertedPidToString(pid);
    return result;
}

std::string Client::messageProcessing(std::string my_string)
{
    std::string result, separator;
    getSymbol(separator);
    
    result = my_string + separator;
    return result;
}

std::string Client::convertedPidToString(DWORD dword)
{
    std::stringstream string_for_dword;
    string_for_dword << dword;
    std::string target_string = string_for_dword.str();
    return target_string;
}

void Client::writeInSendBuffer(std::string my_string)
{
    sendBuffer.append(my_string);
}

int Client::sendMessageToServer()
{
    const char* my_sendBuffer_in_char = sendBuffer.c_str();
    int result = send(connectSocket, my_sendBuffer_in_char, \
        (int)strlen(my_sendBuffer_in_char), 0);
    if (result == SOCKET_ERROR)
    {
        std::cout << "send failed, error: " << result << std::endl;
        closesocket(connectSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }
    return result;
}

int Client::startClient()
{
    int result;
    printCurrentProcessId();
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

    createConnectSocket();
    createConnectToServer();
    CompressDecorator obj(std::make_shared<HashSumDecorator>(std::make_shared<Client>()));
    writeInSendBuffer(obj.messageProcessing(getMinimumMessage()));
}
