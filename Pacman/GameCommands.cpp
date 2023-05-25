#include "GameCommands.h"
#include "GameObject.h"
#include <glm/fwd.hpp>
#include "GTime.h"
#include "PlayerComponent.h"

void dae::MoveCommand::Execute()
{
	Execute(m_Dir);
}

void dae::MoveCommand::Execute(glm::vec3 dir)
{
	GameObject* pOwner = GetOwner();
	if (!pOwner)
	{
		return;
	}
	Transform* pTransform = pOwner->GetComponent<Transform>();
	if (!pTransform)
	{
		return;
	}

	auto deltaTime = GTime::GetInstance().GetDeltaTime();

	glm::vec3 pos = pTransform->GetLocalPosition();
	pos.x += (dir.x * m_Speed) * deltaTime;
	pos.y += (dir.y * m_Speed) * deltaTime;
	pos.z += (dir.z * m_Speed) * deltaTime;

	pTransform->SetLocalPosition(pos);
}

void dae::DieCommand::Execute()
{
	GameObject* pOwner = GetOwner();
	if (!pOwner)
	{
		return;
	}
	PlayerComponent* pPlayer = pOwner->GetComponent<PlayerComponent>();
	if (!pPlayer)
	{
		return;
	}

	pPlayer->Die();

}
