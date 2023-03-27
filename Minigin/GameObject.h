#pragma once
#include "Component.h"
#include <vector>
#include <string>
#include "Transform.h"
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <memory>

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

		void SetParent(GameObject* parent, bool keepWorldPosition);

		GameObject* GetParent() const { return m_pParent; };
		void RemoveChild(GameObject* child);
		void AddChild(GameObject* child);

		void Update();
		//void FixedUpdate();
		void Render() const;

		// Template component functions

		template <typename T, typename... Args> T* AddComponent(Args&&... args) {
			if (IsComponentAdded<T>()) {
				return GetComponent<T>();
			}

			const std::type_index typeIndex = std::type_index(typeid(T));
			auto component = std::make_unique<T>(this, std::forward<Args>(args)...);
			auto pointer = component.get();

			m_pComponents.emplace(typeIndex, std::move(component));

			return pointer;
		};

		template<typename T>
		T* GetComponent() const
		{
			const std::type_index typeIndex = std::type_index(typeid(T));
			if (!IsComponentAdded<T>())
			{
				return nullptr;
			}
			auto component = dynamic_cast<T*>(m_pComponents.at(typeIndex).get());
			return component;
		}

		template<typename T>
		inline void RemoveComponent(T* pComp)
		{
			auto t = m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), pComp));

			delete pComp;
			pComp = nullptr;
		}

		template<typename Component>
		bool IsComponentAdded() const
		{
			const std::type_index typeIndex = std::type_index(typeid(Component));

			return m_pComponents.contains(typeIndex);
		}
	private:
		// Parent-child variables
		GameObject* m_pParent{ nullptr };
		std::vector<GameObject*> m_pChildren{};

		// Components
		
		//std::vector<std::unique_ptr<Component>> m_pComponents{};
		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_pComponents{};
	};


}

