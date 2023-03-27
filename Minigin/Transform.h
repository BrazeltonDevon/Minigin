#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class Transform : public Component
	{
	public:
		Transform(GameObject* gameObject);
		//~Transform();

		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		const glm::vec3& GetWorldPosition();
		void SetLocalPosition(const glm::vec3& pos);
		void SetLocalPosition(float x, float y, float z);
		const glm::vec3& GetLocalPosition() const;

		//void SetWorldPosition(const glm::vec3& pos) { m_WorldPos = pos; }

		virtual void Render() const override {};
		virtual void Update() override {};
		
		// public so can be called in GameObject for SetParent
		void SetPositionDirty(bool val);
	private:
		void UpdateWorldPosition();


		bool m_IsPosDirty{ false };

		glm::vec3 m_LocalPos{};
		glm::vec3 m_WorldPos{};
	};
}
