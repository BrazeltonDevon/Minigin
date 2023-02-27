#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Time.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner)
	: Component(pOwner)
{
}

dae::RenderComponent::~RenderComponent()
= default;

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_filePath = filename;
	m_NeedsUpdate = true;
}

void dae::RenderComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::RenderComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos = m_Transform.GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::RenderComponent::Update()
{
	if (m_NeedsUpdate)
	{
		m_Texture = dae::ResourceManager::GetInstance().LoadTexture(m_filePath);
		m_NeedsUpdate = false;
	}
}



