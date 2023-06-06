#pragma once

// This is a finite state machine

// More info on state machines specifically finite state machines
// https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/

namespace dae
{
	class State;
	class GameObject;

	class StateMachine final
	{
	public:
		StateMachine(State* initState);
		~StateMachine();

		void Initialize(GameObject* gameObject);
		void Update(GameObject* gameobject);

		void SetState(GameObject* gameobject, State* pState);
	private:
		// https://cplusplus.com/forum/beginner/236974/
		// attempted using unique_ptr but cannot use make_unique
		// on an abstract class

		State* m_pState;
	};

}


