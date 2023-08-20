#pragma region _oldcode
//#pragma once
//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//
//#include <XInput.h>
//#include "Singleton.h"
//#include <map>
//#include <memory>
//#include "Command.h"
//#include "Xbox360Controller.h"
//#include <SDL_scancode.h>
//
//namespace dae
//{
//
//	class InputManager final : public Singleton<InputManager>
//	{
//	public:
//		enum class MouseButton
//		{
//			Left, Middle, Right
//		};
//
//		enum class KeyState
//		{
//			Down,
//			Pressed,
//			Up
//		};
//
//		struct KeyAction
//		{
//			KeyState state{};
//			std::shared_ptr<Command> command{};
//			int playerIdx{};
//
//			Xbox360Controller::Button controllerButton{};
//			SDL_Scancode key{};
//		};
//
//
//		InputManager() = default;
//		~InputManager();
//		bool ProcessInput();
//		void Update();
//
//		int AddPlayer();
//
//		bool IsKeyboardKeyDown(unsigned int key);
//
//		bool IsPressed(Xbox360Controller::Button button, int playerIdx) const;
//		bool IsDownThisFrame(Xbox360Controller::Button button, int playeIdx) const;
//		bool IsUpThisFrame(Xbox360Controller::Button button, int playerIdx) const;
//		glm::ivec2 GetMousePos()const { return m_MousePos; };
//		bool IsMousePressed() const { return m_isMousePressed; };
//
//		void AddCommand(Xbox360Controller::Button button, SDL_Scancode keyboardButton, std::shared_ptr<Command> command, int playerIdx, KeyState state = KeyState::Down);
//
//		Xbox360Controller& GetPlayer(int idx);
//
//	private:
//
//		const Uint8* m_pCurrentState{};
//		Uint8* m_pPreviousState{};
//
//		std::vector<std::unique_ptr<Xbox360Controller>> m_pControllers{};
//		std::vector<KeyAction*> m_KeyCommands{};
//
//		glm::ivec2 m_MousePos{};
//		bool m_isMousePressed{ false };
//
//		std::vector<unsigned int> m_PressedKeys{};
//	};
//
//}
//
#pragma endregion _oldcode

#pragma once
#include <map>
#include <memory>
#include <vector>

#include "Singleton.h"
#include "Xbox360Controller.h"
#include "Command.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		Xbox360Controller* GetController(unsigned int controllerIdx);

		enum class InputType
		{
			OnDown,
			Pressed,
			OnRelease
		};

		void AddControllerCommand(Xbox360Controller::Button button, unsigned int controllerID, InputType type, std::unique_ptr<Command> pCommand);
		void AddKeyboardCommand(unsigned int keyboardKey, InputType type, std::unique_ptr<Command> pCommand);

		bool IsKeyboardKeyDown(unsigned int keyboardKey);

		void RemoveAllInputs();

	private:
		struct InputDataController
		{
			unsigned int controllerID{};
			Xbox360Controller::Button button{};
			InputType type{};

			// Custom less-than operator for std::map
			bool operator<(const InputDataController& other) const
			{
				if (controllerID < other.controllerID) return true;
				if (controllerID > other.controllerID) return false;

				if (button < other.button) return true;
				if (button > other.button) return false;

				return type < other.type;
			}
		};

		struct InputDataKeyboard
		{
			unsigned int key{};
			InputType type{};

			// Custom less-than operator for std::map
			bool operator<(const InputDataKeyboard& other) const
			{
				if (key < other.key) return true;
				if (key > other.key) return false;

				return type < other.type;
			}
		};

		friend class Singleton<InputManager>;
		InputManager() = default;

		std::map<InputDataController, std::unique_ptr<Command>> m_ControllerActionMap{};
		std::vector<std::unique_ptr<Xbox360Controller>> m_ControllerPtrs{};

		std::map<InputDataKeyboard, std::unique_ptr<Command>> m_KeyboardActionMap{};

		std::vector<unsigned int> m_PressedKeys{};
	};
}
