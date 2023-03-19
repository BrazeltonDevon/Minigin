#include <string>
#include "GameObject.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include <algorithm>
#include "Component.h"


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto& component : m_pComponents)
	{
		component->Update();
	}
}

//void dae::GameObject::FixedUpdate()
//{
//	for (auto& component : m_pComponents)
//	{
//		component->FixedUpdate();
//	}
//}

void dae::GameObject::Render() const
{
	for (auto& component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (m_pParent)
	{
		auto it = std::find(m_pParent->m_pChildren.begin(), m_pParent->m_pChildren.end(), this);
		if (it != m_pParent->m_pChildren.end())
		{
			m_pChildren.erase(it);
		}

	}
	m_pParent = parent;

	if (m_pParent)
	{
		m_pParent->m_pChildren.emplace_back(this);
	}

	// if has a transform component,...
	auto transform = GetComponent<TransformComponent>();
	if (transform == nullptr)
	{
		return;
	}
	if (m_pParent == nullptr)
	{
		transform->SetLocalPosition(transform->GetWorldPosition());
	}
	else
	{
		auto transformParent = parent->GetComponent<TransformComponent>();
		if (keepWorldPosition && transformParent != nullptr)
		{
			transform->SetLocalPosition(transform->GetLocalPosition() - transformParent->GetWorldPosition());
		}
		if (transform)
		{
			transform->SetPositionDirty();
		}
	}


}
