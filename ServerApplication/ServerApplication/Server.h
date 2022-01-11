#pragma once
//#pragma comment (lib, "Ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <ws2tcpip.h>
#include <iostream>

enum class ParseResult
{
    SUCCESS,
    MY_INVALID_SOCKET,
    MY_SOCKET_ERROR,
    NOT_ZERO_ERROR
};

class Server
{
private:
    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult = nullptr;

public:
    SOCKET clientSocket = INVALID_SOCKET;
    SOCKET listenSocket = INVALID_SOCKET;
    int initWinsock();
    int setConnectionParameters();
    ParseResult createListenSocket();
    ParseResult serverSocketBinding();
    ParseResult setListenSocket();
    ParseResult createClientSocket();
};

