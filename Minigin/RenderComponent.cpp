#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Time.h"
#include "GameObject.h"
#include "Transform.h"


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
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
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
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}



