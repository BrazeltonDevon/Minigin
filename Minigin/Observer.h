#pragma once
#include "GameObject.h"

namespace dae
{
	enum class Event
	{
		PlayerDied,
		PlayerStart,
		AddPoints
	};

	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;
		virtual void OnNotify(Event event, GameObject* gameObject) = 0;
	private:
	};
}