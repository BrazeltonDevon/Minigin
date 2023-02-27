#pragma once
#include "Component.h"
#include "Transform.h"
#include <vector>
#include <string>

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		// Rule of five
		GameObject(std::string tag, const std::vector<Component*>& pComponents = {});

		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void FixedUpdate();
		void Render() const;

		std::string GetTag() { return m_Tag; }

		void SetPosition(float x, float y);

		//Template component funtions
		template<typename Component>
		Component* GetComponent() const;
		template<typename Component>
		Component* AddComponent(Component* pComponent);
		template<typename Component>
		void RemoveComponent(Component* pComponent);

		void SetParent(GameObject* parent);
		GameObject* GetParent() const;

		size_t GetChildCount() const;
		GameObject* GetChildAt(int index) const;
	private:
		Transform m_Transform;

		std::string m_Tag{};

		// Parent-child variables
		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*>m_pChildren{};

		// Components
		// 
		// TODO: change from regular pointer to unique_ptr
		// std::vector<std::unique_ptr<Component>> m_pComponents{};
		// ALSO TODO:
		// Set mark for delete system

		std::vector<Component*>m_pComponents{};

		void RemoveChild(GameObject* obj);
		void AddChild(GameObject* obj);

		int GetChildIndex(const GameObject* obj) const;
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
	inline void GameObject::RemoveComponent(Component* pComponent)
	{
		// remove if dynamic cast to Component succeeds, otherwise don't
		std::remove_if(m_pComponents.begin, m_pComponents.end(), []<bool>(auto * component) { dynamic_cast<Component*>(component) != nullptr; });
	}

}

