#pragma once
#include "getSymbol.h"
#include <iostream>
//#include <windef.h>
#include <windows.h>
#include "StepsOfProcessing.h"

class IClient
{
public:
    virtual ~IClient() {}
    virtual std::string messageProcessing(std::string, std::string&) = 0;
};