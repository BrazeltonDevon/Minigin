#pragma once
#include "Component.h"
#include <vector>
#include <string>
#include "Transform.h"

#include <unordered_map>
#include <memory>

#include <iostream>

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

		void SetParent(GameObject* parent);

		GameObject* GetParent() const { return m_pParent; };
		Transform* GetTransform() const { return m_pTransform; }
		//void RemoveChild(GameObject* child);
		//void AddChild(GameObject* child);

		const std::vector<std::unique_ptr<GameObject>>& GetChildren() const { return m_pChildren; }

		void MarkForDelete();

		bool IsMarkedForDelete() const 
		{
			return m_IsMarkedForDelete;
		};

		void Init();
		void Update();
		void FixedUpdate();
		void Render() const;

		// Template component functions

		template <class T>
		inline bool HasComponent() const
		{
			static_assert(std::is_base_of<Component, T>());

			for (const auto& component : m_pComponents)
			{
				if (dynamic_cast<T*>(component.get()))
					return true;
			}
			return false;
		}

		template <typename T, typename... Args>
		inline T* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");

			if (HasComponent<T>())
			{
				std::cout << "Trying to add an already existing component\n";
				return nullptr;
			}

			std::unique_ptr<T> pComponent = std::make_unique<T>();
			pComponent->SetOwner(this);

			pComponent->Initialize();

			T* rawPtr = pComponent.get();
			m_pComponents.emplace_back(std::move(pComponent));

			return rawPtr;
		}



		template<class T>
		inline T* GetComponent() const
		{
			static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");

			for (const auto& component : m_pComponents)
			{
				if (dynamic_cast<T*>(component.get()))
					return dynamic_cast<T*>(component.get());
			}

			return nullptr;
		}

		template <typename T>
		inline bool RemoveComponent()
		{
			static_assert(std::is_base_of<Component, T>());

			for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
			{
				if (dynamic_cast<T*>(it->get()) != nullptr)
				{
					m_pComponents.erase(it);
					return true;
				}
			}
			return false;
		}

		

	private:
		// Parent-child variables
		GameObject* m_pParent{ nullptr };
		//std::vector<GameObject*> m_pChildren{};

		std::vector<std::unique_ptr<GameObject>> m_pChildren{};
		
		// Components
		std::vector<std::unique_ptr<Component>> m_pComponents{};

		Transform* m_pTransform{};

		bool m_IsMarkedForDelete{false};
	};


}

