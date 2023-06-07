#include "ColliderComponent.h"

dae::ColliderComponent::ColliderComponent(GameObject* go)
	: Component(go)
{

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

	if (m_ColliderBox.xMin <= otherBox.xMin + otherBox.width && xMax >= m_ColliderBox.xMin)
	{
		if (m_ColliderBox.yMin <= otherBox.yMin + otherBox.height && yMax >= otherBox.yMin)
		{
			return false;
		}
	}
		
	return true;
}

void dae::ColliderComponent::Update()
{
	const auto myPosition = GetOwner()->GetComponent<Transform>()->GetLocalPosition();

}

// Sets the dimensions of the bounding box aka collider

void dae::ColliderComponent::SetDimensions(float xMin, float yMin, float width, float height)
{	
	m_ColliderBox.xMin = xMin;
	m_ColliderBox.yMin = yMin;
	m_ColliderBox.width = width;
	m_ColliderBox.height = height;
}
