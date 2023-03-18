#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include <glm/glm.hpp>
#include "Texture2D.h"
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
	m_ElapsedSec = Time::GetInstance().GetDeltaTime();
	m_FPS = static_cast<int>(1.f / m_ElapsedSec);

	m_UpdateTimer += m_ElapsedSec;
	if (m_UpdateTimer >= m_UpdateInterval)
	{
		m_NeedsUpdate = true;
		m_UpdateTimer = 0.f;
	}

	if (m_pText)
	{
		if (m_NeedsUpdate)
		{
			m_pText->SetText("FPS: " + std::to_string(m_FPS));
		}

		m_pText->Update();
		m_NeedsUpdate = false;
	}

}



