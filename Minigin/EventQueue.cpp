#include "EventQueue.h"
using namespace dae;

void EventQueue::AddEvent(const Event& event)
{
	m_EventQueue.push(event);
}

void EventQueue::NotifyListeners()
{
	Event e{};
	while (PollEvent(e))
	{
		for (auto listener : m_pListeners)
		{
			listener->OnEvent(e);
		}
	}
}

bool EventQueue::PollEvent(Event& e)
{
	if (m_EventQueue.empty())
		return false;

	e = m_EventQueue.front();
	m_EventQueue.pop();

	return true;
}

void EventQueue::AddListener(EventListener* listener)
{
	m_pListeners.push_back(listener);
}

void EventQueue::RemoveListener(int listenerId)
{
	std::vector<EventListener*> newListeners;

	for (auto* listener : m_pListeners)
	{
		if (listener && listener->GetID() != listenerId)
		{
			newListeners.push_back(listener);
		}
	}
	m_pListeners = newListeners;
}