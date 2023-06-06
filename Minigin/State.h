#pragma once
#include "GameObject.h"

// This is a pure abstract class in order to create states for state machines

// For more info on states and state machines refer to class material
//https://gameprogrammingpatterns.com/state.html

// also more info on state machines specifically finite state machines
// https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/

namespace dae 
{
	class State
	{
	 public:
		 // What should happen as we enter this state?
		 virtual void Enter(GameObject* object) = 0;

		// What should happen when we’re in this state ?
		 virtual State* Update(GameObject* object) = 0;

		// What should happen as we’re exiting this state?
		virtual void Exit(GameObject* object) = 0;

		virtual ~State() = default;
	};
}


