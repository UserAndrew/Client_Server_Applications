#pragma once
#include <string>
//#include <windows.h>

class IObserver
{
public:
	virtual ~IObserver() {};
	virtual std::string Update(std::string message_from_subject) = 0;
};