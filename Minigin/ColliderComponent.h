#pragma once
#include "Component.h"
#include "Observer.h"
#include "Subject.h"
#include <string>

namespace dae
{
	struct Collider
	{
		float xMin, yMin, width, height;
	};

	class ColliderComponent : public Component
	{
	public:
		ColliderComponent(GameObject* go, std::string tag);

		bool IsColliding(ColliderComponent* otherCollider);
		void Update() override;
		void SetDimensions(float xMin, float yMin, float width, float height);
		void SetPosition(float xPos, float yPos);
		Collider GetColliderBox() { return m_ColliderBox; }
		std::string GetTag() { return m_Tag; };

	private:
		Collider m_ColliderBox{};
		Subject m_CollisionSubject{};
		std::string m_Tag{ "ALL" };
	};
}


