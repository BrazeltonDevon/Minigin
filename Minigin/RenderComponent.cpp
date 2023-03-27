#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include <string>
#include "Texture2D.h"
#include "GameObject.h"


dae::RenderComponent::RenderComponent(GameObject* pOwner, const std::string& filename) : Component(pOwner)
{
	SetTexture(filename);
}

dae::RenderComponent::RenderComponent(GameObject* pOwner, std::shared_ptr<Texture2D> texture) : Component{ pOwner }
{
	m_Texture = texture;
}

dae::RenderComponent::~RenderComponent() = default;

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	auto pTexture = ResourceManager::GetInstance().LoadTexture(filename);
	SetTexture(pTexture);
}

void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D> tex)
{
	m_Texture = tex;
	glm::ivec2 size = m_Texture->GetSize();
	SetWidthHeight(static_cast<float>(size.x), static_cast<float>(size.y));
}

void dae::RenderComponent::SetPosition(float x, float y)
{
	const auto owner = GetOwner();
	if (owner == nullptr)
	{
		return;
	}
	auto transform = owner->GetComponent<Transform>();
	if (transform == nullptr)
	{
		return;
	}

	glm::vec3 pos{ x,y,0.f };
	transform->SetLocalPosition(pos);
}

void dae::RenderComponent::SetWidthHeight(float w, float h)
{
	m_Width = w;
	m_Height = h;
}

void dae::RenderComponent::Render() const
{
	auto owner = GetOwner();
	if (owner == nullptr)
	{
		return;
	}
	auto transform = owner->GetComponent<Transform>();
	if (transform == nullptr)
	{
		return;
	}
	glm::vec3 pos = transform->GetWorldPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_Texture,pos.x,pos.y,m_Width,m_Height);
}



