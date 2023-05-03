#pragma once

// remove xinput here
#include <XInput.h>
#include "Controller.h"

namespace dae
{
	class Xbox360Controller final : public Controller
	{
		class Xbox360ControllerImpl;
		Xbox360ControllerImpl* m_pImpl = nullptr;
	public:
		enum class Button
		{
			// just copy values manually from xinput, don't include macros
			DPADUp = XINPUT_GAMEPAD_DPAD_UP,
			DPADDown = XINPUT_GAMEPAD_DPAD_DOWN,
			DPADLeft = XINPUT_GAMEPAD_DPAD_LEFT,
			DPADRight = XINPUT_GAMEPAD_DPAD_RIGHT,
			Start = XINPUT_GAMEPAD_START,
			Back = XINPUT_GAMEPAD_BACK,
			LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
			RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
			LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
			RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
			ButtonA = XINPUT_GAMEPAD_A,
			ButtonB = XINPUT_GAMEPAD_B,
			ButtonX = XINPUT_GAMEPAD_X,
			ButtonY = XINPUT_GAMEPAD_Y,
		};
		void Update() const override;

		bool IsDownThisFrame(Button button) const;
		bool IsUpThisFrame(Button button) const;
		bool IsPressedThisFrame(Button button) const;

		Xbox360Controller(int controllerNr);
		~Xbox360Controller() override;

	};
}
