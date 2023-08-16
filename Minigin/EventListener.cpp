#include "EventListener.h"

using namespace dae;
int EventListener::m_CurrentID{ 0 };

EventListener::EventListener()
{
	m_ID = m_CurrentID;
	++m_CurrentID;
}