#pragma once
//#pragma comment (lib, "Ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <ws2tcpip.h>
#include <iostream>
#include <list>
#include "ISubject.h"

enum class ParseResult
{
    SUCCESS,
    MY_INVALID_SOCKET,
    MY_SOCKET_ERROR,
    NOT_ZERO_ERROR
};

class Server : public ISubject
{
private:
    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult = nullptr;
    std::list<IObserver*> m_list_observer;
    std::string m_message;
    char recvBuffer[1024];

public:
    SOCKET clientSocket = INVALID_SOCKET;
    SOCKET listenSocket = INVALID_SOCKET;
    virtual ~Server(){};
    void Attach(IObserver* observer) override;
    void Detach(IObserver* observer) override;
    void Notify() override;
    int initWinsock();
    int setConnectionParameters();
    ParseResult createListenSocket();
    ParseResult serverSocketBinding();
    ParseResult setListenSocket();
    ParseResult createClientSocket();
    int startServer();
    int receiveFromClient();
};
