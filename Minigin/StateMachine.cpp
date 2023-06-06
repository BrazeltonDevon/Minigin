#include "StateMachine.h"
#include "StateMachine.h"
#include "GameObject.h"
#include "State.h"

dae::StateMachine::StateMachine(State* initState) : m_pState(initState)
{
	
}

dae::StateMachine::~StateMachine()
{
	delete m_pState;
	m_pState = nullptr;
}

void dae::StateMachine::Initialize(GameObject* gameObject)
{
	// Do entry code for new state
	m_pState->Enter(gameObject);
}

void dae::StateMachine::Update(GameObject* gameobject)
{
	// Allows the update method of a state to optionally return a new state
	// this allows transitions from one state to another
	State* state = m_pState->Update(gameobject);

	// if the update has returned a state, change states
	// otherwise stay in same state
	if (state != nullptr)
	{
		// Do code for exit
		m_pState->Exit(gameobject);
		// Delete current state
		delete m_pState;

		// New state is now the current state
		m_pState = state;
		// Do entry code for new state
		m_pState->Enter(gameobject);
	}
}

void dae::StateMachine::SetState(GameObject* gameobject, State* pState)
{
	// Do code for exit
	m_pState->Exit(gameobject);
	// Delete current state
	delete m_pState;

	// New state is now the current state
	m_pState = pState;
	// Do entry code for new state
	pState->Enter(gameobject);
}
