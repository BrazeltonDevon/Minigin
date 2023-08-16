#pragma once

namespace dae
{
	template<typename... Args>
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;
		Observer(const Observer&) = delete;
		Observer(Observer&&) = delete;
		Observer& operator=(const Observer&) = delete;
		Observer& operator=(Observer&&) = delete;

		virtual void OnNotify(Args... args) = 0;
		virtual void OnSubjectDestroy() = 0;
	};
}

//#pragma once
//#include "GameObject.h"
//
//namespace dae
//{
//	enum class Event
//	{
//		PlayerDied,
//		PlayerStart,
//		AddPoints
//	};
//
//	class Observer
//	{
//	public:
//		Observer() = default;
//		virtual ~Observer() = default;
//		virtual void OnNotify(Event event, GameObject* gameObject) = 0;
//	private:
//	};
//}

