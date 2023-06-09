#include "ColliderComponent.h"
#include "CollisionManager.h"
#include <iostream>

dae::ColliderComponent::ColliderComponent(GameObject* go, std::string tag)
	: Component(go), m_Tag{tag}
{
	CollisionManager::GetInstance().AddCollider(this);
	//std::cout << "Added collider to manager!\n";
}

// Checks for overlapping collider
// https://stackoverflow.com/questions/20925818/algorithm-to-check-if-two-boxes-overlap

bool dae::ColliderComponent::IsColliding(ColliderComponent* otherCollider)
{
	// if has the same tag, do not compare! ignore collision
	std::string otherTag = otherCollider->GetTag();
	if (m_Tag == otherTag)
		return false;

	float xMax = m_ColliderBox.xMin + m_ColliderBox.width;
	float yMax = m_ColliderBox.yMin + m_ColliderBox.height;
	
	Collider otherBox = otherCollider->m_ColliderBox;

	if ( xMax < otherBox.xMin || (otherBox.xMin + otherBox.width) < m_ColliderBox.xMin)
	{
		return false;
	}

	if ( (m_ColliderBox.yMin > otherBox.yMin + otherBox.height) || otherBox.yMin > yMax)
	{
		return false;
	}

	return true;
}

void dae::ColliderComponent::Update()
{
	const auto myPosition = GetOwner()->GetComponent<Transform>()->GetLocalPosition();

	m_ColliderBox.xMin = myPosition.x;
	m_ColliderBox.yMin = myPosition.y;

	//auto collisions = CollisionManager::GetInstance().GetColliders();

	//for (auto collision : collisions)
	//{
	//	//skipping same collision
	//	if (collision == this)
	//		continue;

	//	if (IsColliding(collision))
	//	{
	//		m_Info->gameObject = collision->GetGameObject();
	//		OnTrigger(m_Info);
	//	}

	//}

}

// Sets the dimensions of the bounding box aka collider

void dae::ColliderComponent::SetDimensions(float xMin, float yMin, float width, float height)
{	
	m_ColliderBox.xMin = xMin;
	m_ColliderBox.yMin = yMin;
	m_ColliderBox.width = width;
	m_ColliderBox.height = height;
}

void dae::ColliderComponent::SetPosition(float xPos, float yPos)
{
	m_ColliderBox.xMin = xPos;
	m_ColliderBox.yMin = yPos;
}