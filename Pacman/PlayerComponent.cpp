#include "PlayerComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "GTime.h"
#include "InputManager.h"

dae::PlayerComponent::PlayerComponent(bool isGhost, int playerNr, GameObject* owner)
	: Component{owner}, m_IsGhost{isGhost}
{

}

dae::PlayerComponent::~PlayerComponent()
{

}

void dae::PlayerComponent::Update()
{
	auto deltaTime = GTime::GetInstance().GetDeltaTime();
}

void dae::PlayerComponent::SetDirection(Direction direction)
{

}
