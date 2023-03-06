#pragma once
#include <memory>

namespace dae
{
	class GameObject;
}

class Component
{
public:
	//explicit Component(std::shared_ptr<dae::GameObject> pOwner) : m_pOwner{ std::move(pOwner) };
	//explicit Component(dae::GameObject* pOwner) : m_pOwner{ pOwner } {};
	Component(std::shared_ptr<dae::GameObject> pOwner);
	
	virtual ~Component() = default;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Update() = 0;
	virtual void FixedUpdate() {};
	virtual void Render() const {};

	const std::weak_ptr<dae::GameObject> GetOwner() const { return m_pOwner; };
	//const dae::GameObject* GetOwner() const { return m_pOwner; }
	//const std::shared_ptr<dae::GameObject*> GetOwner() const { return m_pOwner; }

private:
	//std::shared_ptr<dae::GameObject*> m_pOwner;
	//dae::GameObject* m_pOwner;
	std::weak_ptr<dae::GameObject> m_pOwner;
};
