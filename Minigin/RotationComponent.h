#pragma once
#include "Component.h"
#include "TransformComponent.h"

namespace dae {
	class GameObject;
	// TransformComponent;

	class RotationComponent : public Component
	{
	public:
		RotationComponent(GameObject* owner, float radius, float rotSpeed);
		virtual void Render() const override;
		virtual void Update() override;

		void SetRotSpeed(float speed) { m_RotSpeed = speed; }
		float GetRotSpeed() const { return m_RotSpeed; }

		void SetRadius(float radius) { m_Radius = radius; }
		float GetRadius() const { return m_Radius; }
	private:
		glm::vec3 m_Center{};
		float m_RotSpeed{};
		float m_Radius{};

		float m_CurrentRadians{};

		TransformComponent* m_Transform{ nullptr };
	};

}
