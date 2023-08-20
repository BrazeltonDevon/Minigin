#pragma region _oldcode
//#include <iostream>
//#include <vector>
//#include <SDL.h>
//#include "InputManager.h"
//#include "Scene.h"
//#include "SceneManager.h"
//
//dae::InputManager::~InputManager()
//{
//	for (auto element : m_KeyCommands)
//	{
//		delete element;
//		element = nullptr;
//	}
//}
//
//bool dae::InputManager::ProcessInput()
//{
//	SDL_Event e;
//	while (SDL_PollEvent(&e)) {
//		SDL_GetMouseState(&m_MousePos.x, &m_MousePos.y);
//
//		if (e.type == SDL_QUIT) {
//			return false;
//		}
//		if (e.type == SDL_KEYDOWN) {
//			for (const auto& controller : m_KeyCommands)
//			{
//				if (controller->state == KeyState::Down)
//				{
//					if (e.key.keysym.scancode == controller->key)
//						controller->command.get()->Execute();
//				}
//			}
//		}
//		if (e.type == SDL_KEYUP)
//		{
//			for (const auto& controller : m_KeyCommands)
//			{
//				if (controller->state == KeyState::Up)
//				{
//					if (e.key.keysym.scancode == controller->key)
//						controller->command.get()->Execute();
//				}
//			}
//		}
//		if (e.type == SDL_MOUSEBUTTONDOWN && m_isMousePressed == false)
//		{
//			if (e.button.button == SDL_BUTTON_LEFT)
//				m_isMousePressed = true;
//		}
//		if (e.type == SDL_MOUSEBUTTONUP)
//		{
//			if (e.button.button == SDL_BUTTON_LEFT)
//				m_isMousePressed = false;
//		}
//	}
//
//	Update();
//
//	for (const auto& controller : m_KeyCommands)
//	{
//		switch (controller->state)
//		{
//		case KeyState::Down:
//			if (IsDownThisFrame(controller->controllerButton, controller->playerIdx))
//				controller->command->Execute();
//			break;
//		case KeyState::Pressed:
//			if (IsPressed(controller->controllerButton, controller->playerIdx))
//				controller->command->Execute();
//			break;
//		case KeyState::Up:
//			if (IsUpThisFrame(controller->controllerButton, controller->playerIdx))
//				controller->command->Execute();
//			break;
//		default:
//			break;
//		}
//	}
//
//	return true;
//}
//
//void dae::InputManager::Update()
//{
//	for (const auto& controller : m_pControllers)
//	{
//		controller->Update();
//	}
//}
//
//// returns size of m_pControllers aka the last added player what
//// their number is
//int dae::InputManager::AddPlayer()
//{
//	int idx = static_cast<int>(m_pControllers.size());
//	m_pControllers.push_back(std::make_unique<Xbox360Controller>(idx));
//	return idx;
//}
//
//bool dae::InputManager::IsKeyboardKeyDown(unsigned int key)
//{
//	return std::ranges::find(m_PressedKeys, key) != m_PressedKeys.end();
//}
//
//// returns a player, if the idx is out-of-range it takes the last added player
//dae::Xbox360Controller& dae::InputManager::GetPlayer(int idx)
//{
//	if (idx <= m_pControllers.size())
//	{
//		return *m_pControllers.at(idx);
//	}
//	else return *m_pControllers.back();
//
//}
//
//
//bool dae::InputManager::IsPressed(Xbox360Controller::Button button, int  playerIdx) const
//{
//	return m_pControllers[playerIdx]->IsPressedThisFrame(button);
//}
//
//bool dae::InputManager::IsDownThisFrame(Xbox360Controller::Button button, int playerIdx) const
//{
//	return m_pControllers[playerIdx]->IsDownThisFrame(button);
//}
//
//bool dae::InputManager::IsUpThisFrame(Xbox360Controller::Button button, int playerIdx) const
//{
//	return m_pControllers[playerIdx]->IsUpThisFrame(button);
//}
//
//void dae::InputManager::AddCommand(Xbox360Controller::Button controllerButton, SDL_Scancode keyboardButton, std::shared_ptr<Command> command, int playerIdx, KeyState state)
//{
//	if (playerIdx > m_pControllers.size())
//	{
//		std::cout << "Player not found, cannot add command\n" << std::endl;
//		return;
//	}
//	KeyAction* action = new KeyAction();
//	action->command = command;
//	action->controllerButton = controllerButton;
//	action->state = state;
//	action->playerIdx = playerIdx;
//	action->key = keyboardButton;
//	m_KeyCommands.emplace_back(action);
//}
//
//
//
#pragma endregion _oldcode

#include <SDL.h>
#include "InputManager.h"
#include "EventQueue.h"

using namespace dae;

bool InputManager::ProcessInput()
{

	//Keyboard part
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}

		//Keyboard OnDown and OnRelease
		size_t previousSize = m_KeyboardActionMap.size();
		for (auto& mapPair : m_KeyboardActionMap)
		{
			if (static_cast<unsigned int>(e.key.keysym.sym) == mapPair.first.key)
			{
				//DOWN
				if (mapPair.first.type == InputType::OnDown && e.type == SDL_KEYDOWN)
				{
					//Check if it isnt being held down
					if (std::ranges::find(m_PressedKeys, mapPair.first.key) != m_PressedKeys.end())
						continue;

					mapPair.second->Execute();
				}

				//RELEASE
				else if (mapPair.first.type == InputType::OnRelease && e.type == SDL_KEYUP)
					mapPair.second->Execute();

				//if a command changed the input map
				if (m_KeyboardActionMap.size() != previousSize)
				{
					//stop the loop
					break;
				}
			}
		}

		if (e.type == SDL_KEYDOWN)
		{
			//broadcast event of onkeydown
			if ((e.key.keysym.sym >= 'a' && e.key.keysym.sym <= 'z') || e.key.keysym.sym == SDLK_BACKSPACE)
			{
				//check if the key isnt being held down
				if (std::ranges::find(m_PressedKeys, static_cast<unsigned>(e.key.keysym.sym)) != m_PressedKeys.end())
					continue;

				EventQueue::GetInstance().AddEvent(Event{ std::string{char(e.key.keysym.sym)} });
			}
		}
	}

	m_PressedKeys.clear();

	//Keyboard Pressed continuously
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	for (auto& mapPair : m_KeyboardActionMap)
	{
		if (state[SDL_GetScancodeFromKey(static_cast<int>(mapPair.first.key))])
		{
			m_PressedKeys.push_back(mapPair.first.key);

			if (mapPair.first.type == InputType::Pressed)
			{
				mapPair.second->Execute();
			}
		}
	}


	//Controller part
	for (auto& controller : m_ControllerPtrs)
	{
		controller->Update();

		for (auto& mapPair : m_ControllerActionMap)
		{
			if (mapPair.first.controllerID == controller->GetControllerNr())
			{
				if ((mapPair.first.type == InputType::OnDown && controller->IsDownThisFrame(mapPair.first.button)) ||
					(mapPair.first.type == InputType::Pressed && controller->IsPressedThisFrame(mapPair.first.button)) ||
					(mapPair.first.type == InputType::OnRelease && controller->IsUpThisFrame(mapPair.first.button)))
					mapPair.second->Execute();
			}
		}
	}

	return true;
}

Xbox360Controller* InputManager::GetController(unsigned int controllerIdx)
{
	for (auto& controller : m_ControllerPtrs)
	{
		if (controller->GetControllerNr() == controllerIdx)
		{
			return controller.get();
		}
	}
	return nullptr;
}


void InputManager::AddControllerCommand(Xbox360Controller::Button button, unsigned int controllerID, InputType type, std::unique_ptr<Command> pCommand)
{
	//does controller exist yet?
	bool doesControllerExist{ false };
	for (const auto& controller : m_ControllerPtrs)
	{
		if (controller->GetControllerNr() == controllerID)
		{
			doesControllerExist = true;
			break;
		}
	}

	if (doesControllerExist == false)
	{
		//make new controller
		m_ControllerPtrs.push_back(std::make_unique<Xbox360Controller>(controllerID));
	}

	//make the action and add it to the map
	InputDataController inputData{ controllerID, button, type };
	m_ControllerActionMap.insert(std::pair(inputData, std::move(pCommand)));
}

void InputManager::AddKeyboardCommand(unsigned int keyboardKey, InputType type, std::unique_ptr<Command> pCommand)
{
	//make the action and add it to the map
	InputDataKeyboard inputData{ keyboardKey, type };
	m_KeyboardActionMap.insert(std::pair(inputData, std::move(pCommand)));
}

bool InputManager::IsKeyboardKeyDown(unsigned int keyboardKey)
{
	return std::ranges::find(m_PressedKeys, keyboardKey) != m_PressedKeys.end();
}

void InputManager::RemoveAllInputs()
{
	m_KeyboardActionMap.clear();
	m_ControllerActionMap.clear();
}
