#include "PlayerComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "GTime.h"
#include "InputManager.h"

dae::PlayerComponent::PlayerComponent(GameObject* owner, bool isGhost, int playerNr)
	: Component{owner}, m_IsGhost{isGhost}
{
	m_PlayerSubject = std::make_unique<Subject>();
}

dae::PlayerComponent::~PlayerComponent()
{

}

void dae::PlayerComponent::Update()
{
	//auto deltaTime = GTime::GetInstance().GetDeltaTime();
}

void dae::PlayerComponent::Initialize()
{
	m_PlayerSubject->Notify(Event::PlayerStart, this->GetOwner());
}

void dae::PlayerComponent::SetDirection(Direction direction)
{

}

void dae::PlayerComponent::AddObserver(Observer* obs)
{
	m_PlayerSubject->AddObserver(obs);
}

void dae::PlayerComponent::Start()
{
	m_PlayerSubject->Notify(Event::PlayerStart, this->GetOwner());
}

void dae::PlayerComponent::Die()
{
	if (m_Lives > 0)
	{
		--m_Lives;
	}
	m_PlayerSubject->Notify(Event::PlayerDied, this->GetOwner());

}
