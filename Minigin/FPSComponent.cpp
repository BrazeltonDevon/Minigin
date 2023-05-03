#include "FPSComponent.h"
#include "TextComponent.h"
<<<<<<< Updated upstream
#include "Time.h"
=======
#include "GameObject.h"
#include "Texture2D.h"
#include "GTime.h"
>>>>>>> Stashed changes

dae::FPSComponent::FPSComponent(std::shared_ptr<GameObject> pOwner)
	: Component{pOwner}
{
}

dae::FPSComponent::~FPSComponent()
{
}

uint32_t dae::FPSComponent::GetFPS() const
{
	return m_FPS;
}

void dae::FPSComponent::Update()
{
<<<<<<< Updated upstream
	if (!m_pText)
=======
	m_AccumulatedTime += GTime::GetInstance().GetDeltaTime();
	++m_FPSCount;
	if (m_AccumulatedTime > sec)
>>>>>>> Stashed changes
	{
		m_pText = GetOwner().lock()->GetComponent<TextComponent>();
	}

	m_ElapsedSec = Time::GetInstance().GetDeltaTime();
	m_FPS = static_cast<int>(1.f / m_ElapsedSec);

	m_UpdateTimer += m_ElapsedSec;
	if (m_UpdateTimer >= m_UpdateInterval)
	{
		if (m_pText)
		{
			m_pText->SetText("FPS: " + std::to_string(m_FPS));
		}
		m_UpdateTimer = 0.f;
	}
}

void dae::FPSComponent::FixedUpdate()
{

}


