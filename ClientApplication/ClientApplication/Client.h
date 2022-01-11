#pragma once
//#pragma comment (lib, "Ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

enum class ParseResult
{
    SUCCESS,
    MY_INVALID_SOCKET,
    MY_SOCKET_ERROR,
    NOT_ZERO_ERROR
};

class Client
{
private:
    std::string myName{ "Name's Client" };
    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult = nullptr;

public:
    SOCKET connectSocket = INVALID_SOCKET;

    void printCurrentProcessId();
    int initWinsock();
    int setConnectionParameters();
    ParseResult createConnectSocket();
    ParseResult createConnectToServer();
};

