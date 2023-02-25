#include "GameObject.h"
#include <algorithm>
#include "ResourceManager.h"
#include "Renderer.h"


dae::GameObject::~GameObject()
{
	for (auto& elem : m_Children)
	{
		delete elem;
		elem = nullptr;
	}

	for (auto& elem : m_Components)
	{
		delete elem;
		elem = nullptr;
	}
}

void dae::GameObject::Update()
{
	for (auto& comp : m_Components)
	{
		// for each component update
		comp->Update();
	}
}

void dae::GameObject::FixedUpdate()
{

}

void dae::GameObject::Render() const
{
	for (auto& comp : m_Components)
	{
		// for each component update
		comp->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::SetParent(GameObject* parent)
{
	// if already has a parent
	if (parent)
	{
		auto& myPChildren = m_Parent->GetChildren();

		// if has a parent
		// remove this from the parent

		for (auto i = myPChildren.begin(); i != myPChildren.end(); ++i)
		{
			// check for *this
			if (*i == this)
			{
				// remove child
				m_Parent->RemoveChild(static_cast<int>(std::distance(myPChildren.begin(), i)));
			}
		}
	}

	m_Parent = parent;
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_Parent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_Children.size();
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	return m_Children.at(index);
}

void dae::GameObject::RemoveChild(int index)
{
	m_Children.erase(m_Children.begin() + index);
}

void dae::GameObject::AddChild(GameObject* object)
{
	m_Children.push_back(object);
}
