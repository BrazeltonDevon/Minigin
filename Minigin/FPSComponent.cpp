#include "FPSComponent.h"
#include "TextComponent.h"
#include "Time.h"

dae::FPSComponent::FPSComponent(GameObject* pOwner)
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
	if (!m_pText)
	{
		m_pText = m_pGameObject->GetComponent<TextComponent>();
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


