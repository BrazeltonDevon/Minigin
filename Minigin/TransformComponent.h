#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent(GameObject* owner) : Component(owner) {};
		const glm::vec3 GetLocalPosition() const { return m_LocalPos; }
		const glm::vec3& GetWorldPosition();
		void UpdateWorldPosition();

		void SetLocalPosition(const glm::vec3& pos);
		void SetWorldPosition(const glm::vec3& pos) { m_WorldPos = pos; }
		
		void SetPositionDirty();

		virtual void Render() const override {};
		virtual void Update() override {};
	private:
		bool m_PosIsDirty{ false };
		glm::vec3 m_LocalPos{};
		glm::vec3 m_WorldPos{};

	};
}
