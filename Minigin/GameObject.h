#pragma once
#include "Component.h"
#include <vector>
#include <string>

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		// Rule of five
		GameObject() = default;

		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		//void FixedUpdate();
		void Render() const;

		//Template component funtions
		template<typename Component>
		Component* GetComponent() const;
		template<typename Component>
		Component* AddComponent(Component* pComponent);
		template<typename Component>
		void RemoveComponent();

		void SetParent(GameObject* parent, bool keepWorldPosition);
		GameObject* GetParent() const { return m_pParent; };

	private:
		// Parent-child variables
		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*>m_pChildren{};

		std::vector<Component*>m_pComponents{};
	};

	// Template component function definitions
	template<typename Component>
	inline Component* GameObject::GetComponent() const
	{
		for (auto* component : m_pComponents)
		{
			Component* curr = dynamic_cast<Component*>(component);
			if (curr)
			{
				return curr;
			}
		}
		return nullptr;
	}

	template<typename Component>
	inline Component* GameObject::AddComponent(Component* component)
	{
		m_pComponents.push_back(component);
		return component;
	}

	template <typename Component>
	inline void GameObject::RemoveComponent()
	{
		// filter through components and find one of matching type,
		// once found, remove it
		std::remove_if(m_pComponents.begin, m_pComponents.end(),
		[]<bool>(auto * component) { dynamic_cast<Component*>(component) != nullptr; });

	}

}

