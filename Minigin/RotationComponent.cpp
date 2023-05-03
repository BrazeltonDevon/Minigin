#include "RotationComponent.h"
#include "GameObject.h"
#include "GTime.h"

dae::RotationComponent::RotationComponent(std::shared_ptr<dae::GameObject> owner, float radius, float speedInRad) : Component(owner), m_Radius{ radius }, m_RotSpeed{ speedInRad }
{
	if (owner)
	{
		m_Transform = owner->GetComponent<TransformComponent>();
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
<<<<<<< Updated upstream
	if (!m_Transform)
	{
		return;
	}

	m_CurrentRadians += m_RotSpeed * Time::GetInstance().GetDeltaTime();
=======
	m_CurrentRadians += m_RotSpeed * GTime::GetInstance().GetDeltaTime();
>>>>>>> Stashed changes

	const float x_pos_rot{ sinf(m_CurrentRadians) * m_Radius };
	const float y_pos_rot{ cosf(m_CurrentRadians) * m_Radius };

	glm::vec3 newPos{ y_pos_rot + m_Center.x, x_pos_rot + m_Center.y, 0 };

	m_Transform->SetLocalPosition(newPos);
}
