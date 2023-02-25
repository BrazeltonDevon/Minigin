#pragma once
#include "Component.h"
#include "Transform.h"
#include <vector>

namespace dae
{
	//class Texture2D;

	class GameObject
	{
	public:
		void Update();
		void FixedUpdate();
		void Render() const;

		template <typename T> T* GetComponent() const
		{
			T* result = nullptr;
			const auto count = m_Components.size();
			for (int i = 0; i < count && !result; ++i)
			{
				result = dynamic_cast<T*>(m_Components[i]);
			}
			return result;
		}

		template <typename T> void RemoveComponent()
		{
			T* result = nullptr;
			const auto count = m_Components.size();

			auto i = m_Components.begin();
			for (; i != m_Components.end() && !result; ++i)
			{
				result = dynamic_cast<T*>(m_Components[i]);
			}
			if (result && i != m_Components.end())
			{
				// if exists type in vector, delete it from the components
				m_Components.erase(i);
			}
		};

		//template <typename... Args>
		template <typename T, typename...Args>
		T* AddComponent(Args... args)
		{
			T* result = nullptr;
			const auto count = m_Components.size();
			for (int i = 0; i < count && !result; ++i)
			{
				result = dynamic_cast<T*>(m_Components[i]);
			}
			if (!result)
			{
				m_Components.push_back(new T(args...));
				//m_Components.back()->SetOwner(std::make_shared<dae::GameObject>(this));
				return dynamic_cast<T*>(m_Components.back());
			}

			return result;
		};

		void SetPosition(float x, float y);

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// Parent-child Functions
		void SetParent(GameObject* parent);
		GameObject* GetParent() const;

		size_t GetChildCount() const;
		GameObject* GetChildAt(int index) const;
		std::vector<GameObject*>& GetChildren() { return m_Children; };
		void RemoveChild(int index);
		void AddChild(GameObject* object);

	private:
		Transform m_Transform;

		// Parent-child variables
		GameObject* m_Parent{ nullptr };
		std::vector<GameObject*>m_Children{};

		// Components
		std::vector<Component*>m_Components{};
	};
}

