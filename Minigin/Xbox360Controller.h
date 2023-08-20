#pragma once
#include "Controller.h"

namespace dae
{
	class Xbox360Controller final : public Controller
	{
		class Xbox360ControllerImpl;
		Xbox360ControllerImpl* m_pImpl = nullptr;

		unsigned int m_ControllerNr{};
	public:
		enum class Button
		{
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftThumbPress = 0x0040,
			RightThumbPress = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000,
			LeftThumbStick
		};
		void Update() const override;

		bool IsDownThisFrame(Button button) const;
		bool IsUpThisFrame(Button button) const;
		bool IsPressedThisFrame(Button button) const;

		unsigned int GetControllerNr() const { return m_ControllerNr; }

		explicit Xbox360Controller(int controllerNr);
		~Xbox360Controller() override;

	};
}
