//#include "Subject.h"
//#include "GameObject.h"
//
//
//dae::Subject::~Subject()
//{
//
//}
//
//void dae::Subject::AddObserver(Observer* observer)
//{
//	m_pObservers.push_back(observer);
//}
//
//void dae::Subject::RemoveObserver(Observer* observer)
//{
//	for (size_t i = 0; i < m_pObservers.size(); ++i) {
//
//		if (m_pObservers[i] == observer) {
//			m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer));
//		}
//	}
//}
//
//void dae::Subject::Notify(Event eventType, GameObject* object)
//{
//	for (auto observer : m_pObservers) {
//		observer->OnNotify(eventType, object);
//	}
//}