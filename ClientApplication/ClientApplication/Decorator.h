#pragma once
#include <memory>
#include "hashlibpp.h"
#include "zlib/zlib.h"
#include "gzip.h"
#include "IClient.h"

class Decorator : public IClient
{
protected:
	std::shared_ptr<IClient> m_iclient;

public:
	Decorator(std::shared_ptr<IClient> iclient) : m_iclient(iclient) {}

	virtual std::string messageProcessing(std::string, std::string&) override;
};

class HashSumDecorator : public Decorator
{
public:
	HashSumDecorator(std::shared_ptr<IClient> iclient) : Decorator(iclient) {}

	virtual std::string messageProcessing(std::string, std::string&) override;
};

class CompressDecorator : public Decorator
{
public:
	CompressDecorator(std::shared_ptr<IClient> iclient) : Decorator(iclient) {}

	virtual std::string messageProcessing(std::string, std::string&) override;
	void fillDataOriginal(BYTE*, std::string);
	void printResultCompressing(int);
};

class SizeDataDecorator : public Decorator
{
public:
	SizeDataDecorator(std::shared_ptr<IClient> iclient) : Decorator(iclient) {}

	virtual std::string messageProcessing(std::string, std::string&) override;
};

class CommandMessageProcessingDecorator : public Decorator
{
public:
	CommandMessageProcessingDecorator(std::shared_ptr<IClient> iclient) : Decorator(iclient) {}

	virtual std::string messageProcessing(std::string, std::string&) override;
};