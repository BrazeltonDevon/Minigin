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

void dae::PlayerComponent::Start()
{
	m_PlayerSubject->Notify(Event::PlayerStart, this->GetOwner());
}

void dae::PlayerComponent::Update()
{
	auto deltaTime = GTime::GetInstance().GetDeltaTime();

	if (m_TargetDirection != m_Direction)
	{
		m_Direction = m_TargetDirection;
	}

	UpdateMovement(deltaTime);


}

void dae::PlayerComponent::Initialize()
{
	m_PlayerSubject->Notify(Event::PlayerStart, this->GetOwner());
}

void dae::PlayerComponent::SetDirection(Direction direction)
{
	m_TargetDirection = direction;
}

void dae::PlayerComponent::AddObserver(Observer* obs)
{
	m_PlayerSubject->AddObserver(obs);
}

void dae::PlayerComponent::UpdateMovement(float deltaTime)
{
	// get current position of the PlayerComponent's GameObject aka owner
	auto pTransform = GetOwner()->GetComponent<Transform>();

	glm::vec3 curPos = pTransform->GetLocalPosition();
	glm::vec3 newPos = curPos;

	// the amount the player should move independent of framerate aka multiplied
	// by deltaTime
	float moveSpeedDeltaTime = m_MovementSpeed * deltaTime;

	switch (m_Direction)
	{
		// move to the right
	case Direction::RIGHT:
		newPos.x += moveSpeedDeltaTime;
		pTransform->SetLocalPosition(newPos);
		break;
		// move to the left
	case Direction::LEFT:
		newPos.x -= moveSpeedDeltaTime;
		pTransform->SetLocalPosition(newPos);
		break;
		// move down
	case Direction::DOWN:
		newPos.y += moveSpeedDeltaTime;
		pTransform->SetLocalPosition(newPos);
		break;
		// move up
	case Direction::UP:
		newPos.y -= moveSpeedDeltaTime;
		pTransform->SetLocalPosition(newPos);
		break;

	default:
		break;
	}


}

void dae::PlayerComponent::Respawn()
{

}

void dae::PlayerComponent::Die()
{
	if (m_Lives > 0)
	{
		--m_Lives;
	}
	m_PlayerSubject->Notify(Event::PlayerDied, this->GetOwner());

}

