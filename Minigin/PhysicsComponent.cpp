#include "PhysicsComponent.h"

#include "ColliderComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GTime.h"
#include "GameObject.h"

using namespace dae;

void PhysicsComponent::FixedUpdate()
{
	//reset collision state
	m_CollisionState = CollisionState{};
	//do logic
	DoGravityLogic();
	DoCollisionLogic();
}

void PhysicsComponent::SetPhysicsSettings(bool gravity, bool collision, bool isStatic)
{
	m_Gravity = gravity;
	m_Collision = collision;
	m_Static = isStatic;
}

void PhysicsComponent::Jump(float speed)
{
	m_VerticalSpeed = speed;
}

void PhysicsComponent::SetGrounded(bool val)
{
	m_CollisionState.BottomCollision = val;
}

//Collision is going to happen if one of the objects has m_Collision to true,
//They will only overlap if both have m_Collision to false
void PhysicsComponent::DoCollisionLogic()
{
	// dont do calculations if it is static or collision is off
	if (m_Static == true)
		return;

	//only continue of you have a collider
	auto myCollider = m_pOwner->GetComponent<ColliderComponent>();
	if (myCollider == nullptr)
		return;

	Scene* scene = SceneManager::GetInstance().GetCurrentScene();

	//For all objects
	for (auto& object : scene->GetAllObjects())
	{
		if (object.get() == m_pOwner)
			continue;

		//if they have physics and colliders
		auto otherPhysicsComp = object->GetComponent<PhysicsComponent>();
		auto otherColliderComp = object->GetComponent<ColliderComponent>();
		if (otherPhysicsComp && otherColliderComp)
		{
			//only go on if the other has collision on
			if (otherPhysicsComp->m_Collision == false)
				continue;

			//if you are overlapping
			const auto overlapData = myCollider->IsOverlappingWithDirectional(otherColliderComp);

			//Platforms only collide from top
			if (otherPhysicsComp->m_Platform && overlapData.first != ColliderComponent::OverlapData::Bottom)
				continue;

			switch (overlapData.first)
			{
			case ColliderComponent::OverlapData::Top:
			{
				m_pOwner->GetTransform()->Translate(0, overlapData.second);
				myCollider->UpdatePos();
				m_CollisionState.TopCollision = true;
				m_VerticalSpeed = 0.f;
				break;
			}
			case ColliderComponent::OverlapData::Bottom:
			{
				if (m_VerticalSpeed > -1.f)
				{
					m_pOwner->GetTransform()->Translate(0, -overlapData.second);
					myCollider->UpdatePos();
					m_CollisionState.BottomCollision = true;
					m_VerticalSpeed = 0.f;
				}
				break;
			}
			case ColliderComponent::OverlapData::Left:
			{
				m_pOwner->GetTransform()->Translate(overlapData.second, 0);
				myCollider->UpdatePos();
				m_CollisionState.LeftCollision = true;
				break;
			}
			case ColliderComponent::OverlapData::Right:
			{
				m_pOwner->GetTransform()->Translate(-overlapData.second, 0);
				myCollider->UpdatePos();
				m_CollisionState.RightCollision = true;
				break;
			}
			case ColliderComponent::OverlapData::Not:
				break;
			}
		}
	}
}

void PhysicsComponent::DoGravityLogic()
{
	if (m_Gravity == false || m_Static == true)
		return;

	const float deltaT{ GTime::GetInstance().GetDeltaTime() };

	m_VerticalSpeed += m_GravityAccel * deltaT;
	m_VerticalSpeed = std::min(m_MaxFallSpeed, m_VerticalSpeed);

	// put player at top of level if out of bounds below
	// and put them at bottom if out of bounds top
	auto myCollider = m_pOwner->GetComponent<ColliderComponent>();
	if (myCollider)
	{
		glm::vec2 worldPos = m_pOwner->GetTransform()->GetWorldPosition();
		if (worldPos.y > 800)
		{
			m_pOwner->GetTransform()->SetWorldPosition(worldPos.x, 0 - myCollider->GetSize().y);
		}
		else if (worldPos.y < -myCollider->GetSize().y)
		{
			m_pOwner->GetTransform()->SetWorldPosition(worldPos.x, 800);
		}
	}

	m_pOwner->GetTransform()->Translate(0, deltaT * m_VerticalSpeed);
}
