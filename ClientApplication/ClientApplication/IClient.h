#pragma once
#include <string>
class IClient
{
public:
    virtual std::string messageProcessing(std::string) = 0;
    virtual ~IClient() {}
};