#pragma once
#include <string>
//#include <windows.h>

class IObserver
{
public:
	virtual ~IObserver() {};
	virtual void Update(const char* message_from_subject) = 0;
};