#include "Observer.h"

void Observer::Update(const std::string& message_from_subject)
{
	m_message_from_subject = message_from_subject;
}

void Observer::RemoveMeFromTheList()
{
	m_subject.Detach(this);
}