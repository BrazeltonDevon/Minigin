#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae {
	class GameObject;
	class TransformComponent;

	class RotationComponent : public Component
	{
	public:
		RotationComponent(float radius = 0, float rotSpeed = 0);
		virtual void Render() const override;
		virtual void Update() override;

		void SetRotSpeed(float speed) { m_RotSpeed = speed; }
		float GetRotSpeed() const { return m_RotSpeed; }

		void SetRadius(float radius) { m_Radius = radius; }
		float GetRadius() const { return m_Radius; }
	private:

		glm::vec2 m_Center{};
		float m_RotSpeed{};
		float m_Radius{};

		float m_CurrentRadians{};
		Transform* m_Transform{ nullptr };
	};

}
