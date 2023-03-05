#pragma once
#include <memory>

namespace dae
{
	class GameObject;
}

class Component
{
public:
	//Component(std::shared_ptr<dae::GameObject> pOwner);
	Component(dae::GameObject* pOwner);
	virtual ~Component() = default;

	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Update() = 0;
	virtual void FixedUpdate() {};
	virtual void Render() const {};

	explicit Component(dae::GameObject* owner) : m_pOwner{ owner } {};
	const dae::GameObject* GetOwner() const { return m_pOwner; }

private:
	dae::GameObject* m_pOwner;
};
