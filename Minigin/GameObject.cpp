#include <string>
#include "GameObject.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "Texture2D.h"
#include <algorithm>
#include "Component.h"


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto& component : m_pComponents)
	{
		component.second->Update();
	}

	for (size_t i = 0; i < m_pChildren.size(); ++i)
	{
		m_pChildren[i]->Update();
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
		component.second->Render();
	}

	for (size_t i = 0; i < m_pChildren.size(); ++i)
	{
		m_pChildren[i]->Render();
	}
}


void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	auto transform = GetComponent<Transform>();
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
		auto transformParent = parent == nullptr ? nullptr : parent->GetComponent<Transform>();
		if (keepWorldPosition && transformParent != nullptr)
		{
			transform->SetLocalPosition(transform->GetLocalPosition() - transformParent->GetWorldPosition());
		}
		if (transform)
		{
			transform->SetPositionDirty(true);
			for (auto& child : m_pChildren)
			{
				if (auto childTransform = child->GetComponent<Transform>())
				{
					childTransform->SetPositionDirty(true);
				}
			}
		}
	}

	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}
	m_pParent = parent;
	if (m_pParent)
	{
		m_pParent->AddChild(this);
	}
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	auto childToFind = std::find(m_pChildren.begin(), m_pChildren.end(), child);
	if (childToFind != m_pChildren.end())
	{
		m_pChildren.erase(childToFind);
	}
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_pChildren.emplace_back(child);
}
