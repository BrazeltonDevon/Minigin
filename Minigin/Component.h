#pragma once
#include <memory>

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Initialize() {}
		virtual void Update() {};
		virtual void Render() const {};
		virtual void FixedUpdate() {}
		GameObject* GetOwner() const;

		void SetOwner(GameObject* pParent);
	protected:
		// (depreciated, setting of owner is handled in AddComponent now)
		//explicit Component(GameObject* owner) : m_pOwner{ owner } {};

		GameObject* m_pOwner = nullptr;
	};
}


