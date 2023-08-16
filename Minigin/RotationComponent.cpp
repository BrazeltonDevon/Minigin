#include "RotationComponent.h"
#include "GameObject.h"

#include "GTime.h"

dae::RotationComponent::RotationComponent(float radius, float speedInRad) : Component(), m_Radius{radius}, m_RotSpeed{speedInRad}
{
	if (m_pOwner)
	{
		m_Transform = GetOwner()->GetTransform();
		if (m_Transform)
		{
			m_Center = m_Transform->GetLocalPosition();
		}
	}
}

void dae::RotationComponent::Render() const
{
}

void dae::RotationComponent::Update()
{
	m_CurrentRadians += m_RotSpeed * GTime::GetInstance().GetDeltaTime();

	const float x_pos_rot{ sinf(m_CurrentRadians) * m_Radius };
	const float y_pos_rot{ cosf(m_CurrentRadians) * m_Radius };

	glm::vec2 newPos{ y_pos_rot + m_Center.x, x_pos_rot + m_Center.y };

	m_Transform->SetLocalPosition(newPos);

}
