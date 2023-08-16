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

	// If has a parent already, remove it from list of children from that parent
	if (pPreviousParent)
	{
		if (pPreviousParent == parent) return;

		// Remove this from list of previous parent's children
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
	// if has no parent but the new parent == nullptr RETURN
	else if (!parent)
	{
		return;
	}

	// Set parent to new parent pointer (if is nullptr, just won't have a parent)
	m_pParent = parent;

	// if new parent is NOT nullptr, set this as a child to that parent
	if (parent)
	{
		parent->m_pChildren.push_back(std::unique_ptr<GameObject>(this));
	}
	

	auto pTransform{ GetTransform() };
	if (!pTransform)
		return;

	// If new parent is valid,
	if (parent)
	{
		// Set local pos relative to new parent
		auto pParentTransform{ parent->GetTransform() };
		if (pParentTransform)
			pTransform->SetLocalPosition(pTransform->GetWorldPosition() - pParentTransform->GetWorldPosition());
	}
	else
	{
		// Set local position to world position (reset)
		pTransform->SetLocalPosition(pTransform->GetWorldPosition());
	}
}

void dae::GameObject::MarkForDelete()
{
	m_IsMarkedForDelete = true;

	// mark all children for delete
	for (const auto& child : m_pChildren)
	{
		child->MarkForDelete();
	}
}
