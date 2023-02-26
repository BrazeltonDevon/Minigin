#include "GameObject.h"
#include <algorithm>
#include "ResourceManager.h"
#include "Renderer.h"


dae::GameObject::GameObject(std::string tag, const std::vector<Component*>& pComponents)
	: m_pComponents{pComponents},
	m_Transform{}
{

}

dae::GameObject::~GameObject()
{
	for (auto& elem : m_pChildren)
	{
		delete elem;
		elem = nullptr;
	}

	for (auto& elem : m_pComponents)
	{
		delete elem;
		elem = nullptr;
	}
}

void dae::GameObject::Update()
{
	for (auto& comp : m_pComponents)
	{
		// for each component update
		comp->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (auto& comp : m_pComponents)
	{
		// for each component do a fixed update
		comp->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (auto& comp : m_pComponents)
	{
		comp->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::SetParent(GameObject* parent)
{
	m_pParent = parent;
	parent->AddChild(this);
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	return m_pChildren.at(index);
}

void dae::GameObject::RemoveChild(GameObject* obj)
{
	// get fetus number
	const int idx{ GetChildIndex(obj) };
	if (idx != -1)
	{
		// fetus deletus
		m_pChildren.erase(m_pChildren.begin() + idx);
		// remove parent from deletus del fetus
		obj->SetParent(nullptr);
	}

}

void dae::GameObject::AddChild(GameObject* obj)
{
	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}
	m_pChildren.push_back(obj);

}

int dae::GameObject::GetChildIndex(const GameObject* obj) const
{
	// loop through all children
	for (size_t it = 0; it < m_pChildren.size(); ++it)
	{
		if (m_pChildren[it] == obj)
		{
			return static_cast<int>(it);
		}
	}

	// if not in m_pChildren, return invalid index aka failure
	return -1;
}
