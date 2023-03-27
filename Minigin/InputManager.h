#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <map>
#include <memory>

#include "Command.h"
#include "Xbox360Controller.h"


namespace dae
{

	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class MouseButton
		{
			Left, Middle, Right
		};

		enum class KeyState
		{
			Down,
			Pressed,
			Up
		};

		struct KeyAction
		{
			KeyState state{};
			std::shared_ptr<Command> command{};
			int playerIdx{};

			Xbox360Controller::Button controllerButton{};
			SDL_Scancode key{};
		};


		InputManager() = default;
		~InputManager();
		bool ProcessInput();
		void Update();

		int AddPlayer();

		bool IsPressed(Xbox360Controller::Button button, int playerIdx) const;
		bool IsDownThisFrame(Xbox360Controller::Button button, int playeIdx) const;
		bool IsUpThisFrame(Xbox360Controller::Button button, int playerIdx) const;
		glm::ivec2 GetMousePos()const { return m_MousePos; };
		bool IsMousePressed() const { return m_isMousePressed; };

		void AddCommand(Xbox360Controller::Button button, SDL_Scancode keyboardButton, std::shared_ptr<Command> command, int playerIdx, KeyState state = KeyState::Down);

	private:

		const Uint8* m_pCurrentState{};
		Uint8* m_pPreviousState{};

		std::vector<std::unique_ptr<Xbox360Controller>> m_pControllers{};
		std::vector<KeyAction*> m_KeyCommands{};

		glm::ivec2 m_MousePos{};
		bool m_isMousePressed{ false };
	};

}
