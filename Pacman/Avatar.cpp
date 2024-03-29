#include "Avatar.h"

#include "AvatarComponent.h"
#include "ColliderComponent.h"
#include "InputManager.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "GameCommands.h"

using namespace dae;

GameObject* Avatar::CreateAvatar(Scene* pScene, const glm::vec2& spawnPos, bool green, bool coop)
{
	GameObject* pAvatar{ pScene->CreateGameObject() };
	pAvatar->GetComponent<Transform>()->SetWorldPosition(spawnPos.x, spawnPos.y);

	auto spriteComp = pAvatar->AddComponent<SpriteComponent>();
	spriteComp->SetTexture("Avatar.png");
	if (green)
		spriteComp->SetAnimVariables(6, 7, 0.1f, 0, 7);
	else
		spriteComp->SetAnimVariables(6, 7, 0.1f, 21, 28);
	spriteComp->Scale(4);

	auto colliderComp = pAvatar->AddComponent<ColliderComponent>();
	colliderComp->SetSize(spriteComp->GetSize());

	auto physicsComp = pAvatar->AddComponent<PhysicsComponent>();
	physicsComp->SetPhysicsSettings(true, false, false);

	if (coop == false)
	{
		InputManager::GetInstance().AddKeyboardCommand('a', InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pAvatar, 200.f));
		InputManager::GetInstance().AddKeyboardCommand('d', InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pAvatar, 200.f));
		InputManager::GetInstance().AddKeyboardCommand('w', InputManager::InputType::Pressed, std::make_unique<JumpCommand>(pAvatar, -450.f));
		InputManager::GetInstance().AddKeyboardCommand(' ', InputManager::InputType::OnDown, std::make_unique<ShootBubbleCommand>(pAvatar));
		InputManager::GetInstance().AddControllerCommand(Xbox360Controller::Button::DPadLeft, 0, InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pAvatar, 200.f));
		InputManager::GetInstance().AddControllerCommand(Xbox360Controller::Button::DPadRight, 0, InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pAvatar, 200.f));
		InputManager::GetInstance().AddControllerCommand(Xbox360Controller::Button::ButtonA, 0, InputManager::InputType::Pressed, std::make_unique<JumpCommand>(pAvatar, -450.f));
		InputManager::GetInstance().AddControllerCommand(Xbox360Controller::Button::ButtonB, 0, InputManager::InputType::OnDown, std::make_unique<ShootBubbleCommand>(pAvatar));
	}
	else
	{
		if (green)
		{
			InputManager::GetInstance().AddKeyboardCommand('a', InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pAvatar, 200.f));
			InputManager::GetInstance().AddKeyboardCommand('d', InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pAvatar, 200.f));
			InputManager::GetInstance().AddKeyboardCommand('w', InputManager::InputType::Pressed, std::make_unique<JumpCommand>(pAvatar, -450.f));
			InputManager::GetInstance().AddKeyboardCommand(' ', InputManager::InputType::OnDown, std::make_unique<ShootBubbleCommand>(pAvatar));
			InputManager::GetInstance().AddControllerCommand(Xbox360Controller::Button::DPadLeft, 1, InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pAvatar, 200.f));
			InputManager::GetInstance().AddControllerCommand(Xbox360Controller::Button::DPadRight, 1, InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pAvatar, 200.f));
			InputManager::GetInstance().AddControllerCommand(Xbox360Controller::Button::ButtonA, 1, InputManager::InputType::Pressed, std::make_unique<JumpCommand>(pAvatar, -450.f));
			InputManager::GetInstance().AddControllerCommand(Xbox360Controller::Button::ButtonB, 1, InputManager::InputType::OnDown, std::make_unique<ShootBubbleCommand>(pAvatar));
		}
		else
		{
			InputManager::GetInstance().AddControllerCommand(Xbox360Controller::Button::DPadLeft, 0, InputManager::InputType::Pressed, std::make_unique<MoveLeftCommand>(pAvatar, 200.f));
			InputManager::GetInstance().AddControllerCommand(Xbox360Controller::Button::DPadRight, 0, InputManager::InputType::Pressed, std::make_unique<MoveRightCommand>(pAvatar, 200.f));
			InputManager::GetInstance().AddControllerCommand(Xbox360Controller::Button::ButtonA, 0, InputManager::InputType::Pressed, std::make_unique<JumpCommand>(pAvatar, -450.f));
			InputManager::GetInstance().AddControllerCommand(Xbox360Controller::Button::ButtonB, 0, InputManager::InputType::OnDown, std::make_unique<ShootBubbleCommand>(pAvatar));
		}

	}


	auto avatarComp = pAvatar->AddComponent<AvatarComponent>();
	if (green)
		avatarComp->SetColor(AvatarComponent::AvatarColor::green);
	else
		avatarComp->SetColor(AvatarComponent::AvatarColor::blue);

	return pAvatar;
}
