#include "RotationComponent.h"
#include "GameObject.h"

#include "Time.h"

dae::RotationComponent::RotationComponent(GameObject* pOwner, float radius, float speedInRad) : Component(pOwner), m_Radius{radius}, m_RotSpeed{speedInRad}
{
	/*if (pOwner)
	{
		m_CurrentRadians = pOwner->GetRotation();
	}*/
}

void dae::RotationComponent::Render() const
{
}

void dae::RotationComponent::Update()
{
	m_CurrentRadians += m_RotSpeed * Time::GetInstance().GetDeltaTime();

	const float x_pos_rot{ sinf(m_CurrentRadians) * m_Radius };
	const float y_pos_rot{ cosf(m_CurrentRadians) * m_Radius };

	glm::vec3 newPos{ y_pos_rot + m_Center.x, x_pos_rot + m_Center.y, 0 };

	//GetOwner()->SetPosition(newPos.x, newPos.y);
}
