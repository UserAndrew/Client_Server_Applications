#pragma once
#include <string>
#include <iostream>
//#include <windef.h>
#include <windows.h>
#include "StepsOfProcessing.h"

class IClient
{
public:
    virtual std::string messageProcessing(std::string) = 0;
    virtual ~IClient() {}
};