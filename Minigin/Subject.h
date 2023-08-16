//#pragma once
//#include <vector>
//#include "Observer.h"
//
//namespace dae
//{
//	class Observer;
//	class GameObject;
//
//	class Subject
//	{
//	public:
//		Subject() = default;
//		~Subject();
//		void AddObserver(Observer* observer);
//		void RemoveObserver(Observer* observer);
//		void Notify(Event eventType, GameObject* object);
//
//		std::vector<Observer*> GetObservers() const {
//			return m_pObservers;
//		};
//
//	private:
//		std::vector<Observer*> m_pObservers;
//	};
//}

#pragma once
#include <vector>
#include "Observer.h"

namespace dae
{
	template<typename... Args>
	class Subject final
	{
	public:
		void AddObserver(Observer<Args...>* pObserver)
		{
			m_pObservers.push_back(pObserver);
		}

		void RemoveObserver(Observer<Args...>* pObserver)
		{
			m_pObservers.erase(std::remove(
				m_pObservers.begin(),
				m_pObservers.end(), pObserver),
				m_pObservers.end());
		}

		~Subject()
		{
			for (auto& observer : m_pObservers)
			{
				observer->OnSubjectDestroy();
			}
		}

		void Notify(Args... args)
		{
			for (auto& pObserver : m_pObservers)
			{
				pObserver->OnNotify(args...);
			}
		}

	private:
		std::vector<Observer<Args ...>*> m_pObservers;
	};
}

