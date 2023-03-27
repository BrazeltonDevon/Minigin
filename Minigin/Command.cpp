#include "Command.h"
#include "GameObject.h"
#include <glm/fwd.hpp>
#include "Time.h"

dae::Command::Command(GameObject* actor) :
	m_pOwner{ actor }
{
}


void dae::MoveCommand::Execute()
{
	Execute(m_Dir);
}

void dae::MoveCommand::Execute(glm::vec3& dir)
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

	auto deltaTime = Time::GetInstance().GetDeltaTime();

	glm::vec3 pos = pTransform->GetLocalPosition();
	pos.x += (dir.x * m_Speed) * deltaTime;
	pos.y += (dir.y * m_Speed) * deltaTime;
	pos.z += (dir.z * m_Speed) * deltaTime;

	pTransform->SetLocalPosition(pos);
}
