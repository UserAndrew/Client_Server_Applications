#pragma once
#include <string>
#include <iostream>
//#include <windef.h>
#include <windows.h>

class IClient
{
public:
    virtual std::string messageProcessing(std::string) = 0;
    virtual ~IClient() {}
};