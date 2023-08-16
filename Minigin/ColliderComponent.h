#pragma region _oldcode
//#pragma once
//#include "Component.h"
//#include "Observer.h"
//#include "Subject.h"
//#include <string>
//
//namespace dae
//{
//	struct Collider
//	{
//		float xMin, yMin, width, height;
//	};
//
//	class ColliderComponent : public Component
//	{
//	public:
//		ColliderComponent(std::string tag = "");
//
//		bool IsColliding(ColliderComponent* otherCollider);
//		void Update() override;
//		void SetDimensions(float xMin, float yMin, float width, float height);
//		void SetPosition(float xPos, float yPos);
//		Collider GetColliderBox() { return m_ColliderBox; }
//		std::string GetTag() { return m_Tag; };
//
//	private:
//		Collider m_ColliderBox{};
//		//Subject m_CollisionSubject{};
//		std::string m_Tag{ "ALL" };
//	};
//}
//

#pragma endregion _oldcode

#pragma once
#include <functional>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

#include "Component.h"

namespace dae
{
	class ColliderComponent final : public Component
	{
	public:
		enum class OverlapData
		{
			Bottom,
			Top,
			Left,
			Right,
			Not
		};

		ColliderComponent() = default;
		~ColliderComponent() override = default;
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent operator=(const ColliderComponent& rhs) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent operator=(ColliderComponent&& rhs) = delete;

		void FixedUpdate() override;
		void Render() const override;

		void SetRendering(bool value) { m_DrawDebug = value; }
		bool IsOverlappingWith(const ColliderComponent* other);
		std::pair<OverlapData, float> IsOverlappingWithDirectional(const ColliderComponent* other);

		void SetSize(const glm::vec2& val);
		void UpdatePos();

		const glm::vec2& GetSize() const { return m_Size; }
		const glm::vec2& GetPos() const { return m_Pos; }

		void SetOverlapFunction(std::function<void(GameObject*)> overlapFunction);

	private:
		void CheckForOverlaps();

		glm::vec2 m_Pos{};
		glm::vec2 m_Size{};

		bool m_DrawDebug{ false };
		glm::vec4 m_Color{ 255, 0, 0, 255 };

		std::function<void(GameObject*)> m_OverlapFunction;
	};
}

