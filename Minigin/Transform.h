#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class Transform : public Component
	{
	public:
		Transform() = default;
		~Transform() override = default;

		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		const glm::vec2& GetWorldPosition();
		void SetLocalPosition(const glm::vec2& pos);
		void SetLocalPosition(float x, float y);
		const glm::vec2& GetLocalPosition() const;

		void SetWorldPosition(const glm::vec2& pos);
		void SetWorldPosition(float x, float y);

		void Translate(float x, float y);
		void Translate(glm::vec2 vec);

		bool GetIsFacingRight() const;

		virtual void Render() const override {};
		virtual void Update() override {};
		
	private:
		void UpdateWorldPosition();
		void SetPositionDirty();

		bool m_IsPosDirty{ false };

		glm::vec2 m_LocalPos{};
		glm::vec2 m_WorldPos{};

		bool m_IsFacingRight{ true };
	};
}
