#pragma once
#include "Singleton.h"
#include "Event.h"
#include "EventListener.h"
#include <queue>

namespace dae
{
	class EventQueue final : public Singleton<EventQueue>
	{
	public:
		// Add an event to the queue
		void AddEvent(const Event& event);

		// Execute all events frame per frame
		void NotifyListeners();

		// Add a listener for events
		void AddListener(EventListener* listener);
		// Remove a listener at ID
		void RemoveListener(int listenerIDx);
	private:
		bool PollEvent(Event& e);

		std::queue<Event> m_EventQueue{};
		std::vector<EventListener*> m_pListeners;
	};
}

