#pragma once
//#pragma comment (lib, "Ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
//#include <hashlibpp.h>
#include "Decorator.h"
#include <winsock2.h>
#include <stdlib.h>
#include <ws2tcpip.h>



enum class ParseResult
{
    SUCCESS,
    MY_INVALID_SOCKET,
    MY_SOCKET_ERROR,
    NOT_ZERO_ERROR
};

class Client : public IClient
{
private:
    std::string myName{ "I am a Client" };
    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult = nullptr;
    std::string sendBuffer;
    char recvBuffer[512];

public:
    SOCKET connectSocket = INVALID_SOCKET;
    
    std::string command_string{""};
    std::string getMyname() { return myName; }
    void printCurrentProcessId();
    int initWinsock();
    int setConnectionParameters();
    ParseResult createConnectSocket();
    ParseResult createConnectToServer();
    std::string convertedPidToString(DWORD);
    void writeInSendBuffer(std::string);
    virtual std::string messageProcessing(std::string, std::string&) override;
    int sendMessageToServer();
    std::string getMinimumMessage();
    int startClient();
    void choiceMethodProcessing(StepsOfProcessing);
    void shutdownSocket();
};

