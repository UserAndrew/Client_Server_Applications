#pragma once
#include "IObserver.h"
#include "Server.h"

class Observer : public IObserver
{
private:
	std::string m_message_from_subject;
	Server& m_subject;

public:
    Observer(Server& subject) : m_subject(subject) {
        this->m_subject.Attach(this);
    }
    virtual ~Observer() {}

    void Update(const char* message_from_subject) override;
    void RemoveMeFromTheList();
    void fillDataCompressed(const char*, BYTE*);
    void printResultUncompressing(int);
};

