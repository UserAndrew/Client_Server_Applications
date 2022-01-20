#pragma once
#include <string>
#include <iostream>

class IClient
{
public:
    virtual std::string messageProcessing(std::string) = 0;
    virtual ~IClient() {}
};