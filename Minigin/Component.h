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
	virtual void FixedUpdate() = 0;
	virtual void Render() const = 0;

	const dae::GameObject* GetOwner() const { return m_pGameObject; }
	//std::weak_ptr<dae::GameObject> GetOwner() const { return m_pGameObject; };
	//void SetOwner(std::shared_ptr<dae::GameObject> go);
protected:
	//std::weak_ptr<dae::GameObject> m_pGameObject;
	dae::GameObject* m_pGameObject;
};
