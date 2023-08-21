#include <string>
#include "GameObject.h"
#include "Renderer.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "Texture2D.h"
#include <algorithm>
#include "Component.h"


dae::GameObject::~GameObject() = default;

void dae::GameObject::Init()
{
	m_pTransform = AddComponent<Transform>();
}

void dae::GameObject::Update()
{
	for (auto& component : m_pComponents)
	{
		component->Update();
	}

	for (size_t i = 0; i < m_pChildren.size(); ++i)
	{
		m_pChildren[i]->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (auto& component : m_pComponents)
	{
		component->FixedUpdate();
	}

	for (size_t i = 0; i < m_pChildren.size(); ++i)
	{
		m_pChildren[i]->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (auto& component : m_pComponents)
	{
		component->Render();
	}

	for (size_t i = 0; i < m_pChildren.size(); ++i)
	{
		m_pChildren[i]->Render();
	}
}


void dae::GameObject::SetParent(GameObject* parent)
{
	GameObject* pPreviousParent{m_pParent};

	if (pPreviousParent)
	{
		if (pPreviousParent == parent) return;

		for (int i{ static_cast<int>(pPreviousParent->m_pChildren.size() - 1) }; i >= 0; --i)
		{
			const auto& pChild{ pPreviousParent->m_pChildren[i] };

			if (pChild.get() == this)
			{
				pPreviousParent->m_pChildren[i] = std::move(pPreviousParent->m_pChildren[pPreviousParent->m_pChildren.size() - 1]);
				pPreviousParent->m_pChildren.pop_back();
				break;
			}
		}

	}
	else if (!parent)
	{
		return;
	}

	m_pParent = parent;

	if (parent)
	{
		parent->m_pChildren.push_back(std::unique_ptr<GameObject>(this));
	}
	

	auto pTransform{ GetTransform() };
	if (!pTransform)
		return;

	if (parent)
	{
		auto pParentTransform{ parent->GetTransform() };
		if (pParentTransform)
			pTransform->SetLocalPosition(pTransform->GetWorldPosition() - pParentTransform->GetWorldPosition());
	}
	else
	{
		pTransform->SetLocalPosition(pTransform->GetWorldPosition());
	}
}

void dae::GameObject::MarkForDelete()
{
	m_IsMarkedForDelete = true;
	//std::cout << "marked object for delete\n";

	for (const auto& child : m_pChildren)
	{
		child->MarkForDelete();
	}
}
