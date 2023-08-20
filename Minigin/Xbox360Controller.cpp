#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

#include "Xbox360Controller.h"

using namespace dae;

// XBOX Controller Implementation

class Xbox360Controller::Xbox360ControllerImpl final
{
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};

	int m_ControllerNr{};
	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

public:

	Xbox360ControllerImpl(int controllerNr)
		:m_ControllerNr(controllerNr)
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
	}

	void Update()
	{
		m_PreviousState = m_CurrentState;
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerNr, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsPressedThisFrame(Xbox360Controller::Button button) const
	{
		return m_CurrentState.Gamepad.wButtons & static_cast<unsigned>(button);
	}

	bool IsDownThisFrame(Xbox360Controller::Button button) const
	{
		return m_ButtonsPressedThisFrame & static_cast<unsigned>(button);
	}

	bool IsUpThisFrame(Xbox360Controller::Button button) const
	{
		return m_ButtonsReleasedThisFrame & static_cast<unsigned>(button);
	}

};

// XBOX Controller

void dae::Xbox360Controller::Update() const
{
	m_pImpl->Update();
}

bool dae::Xbox360Controller::IsDownThisFrame(Xbox360Controller::Button button) const
{
	return m_pImpl->IsDownThisFrame(button);
}

bool dae::Xbox360Controller::IsUpThisFrame(Xbox360Controller::Button button) const
{
	return m_pImpl->IsUpThisFrame(button);
}

bool dae::Xbox360Controller::IsPressedThisFrame(Xbox360Controller::Button button) const
{
	return m_pImpl->IsPressedThisFrame(button);
}

dae::Xbox360Controller::Xbox360Controller(int controllerNr)
	:Controller(),
	m_pImpl{ new Xbox360ControllerImpl(controllerNr) }
{
}

dae::Xbox360Controller::~Xbox360Controller()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}
