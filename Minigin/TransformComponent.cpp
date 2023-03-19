#include "TransformComponent.h"
#include <algorithm>
#include "GameObject.h"

const glm::vec3& dae::TransformComponent::GetWorldPosition()
{
	if (m_PosIsDirty)
	{
		UpdateWorldPosition();
	}
	return m_WorldPos;
}

void dae::TransformComponent::SetPositionDirty()
{
	m_PosIsDirty = true;
}

void dae::TransformComponent::UpdateWorldPosition()
{
	if (m_PosIsDirty)
	{
		auto owner = GetOwner();
		if (owner)
		{
			return;
		}

		auto parent{ owner->GetParent()};
		if (parent == nullptr)
		{
			m_WorldPos = m_LocalPos;
		}
		else
		{
			auto transform = parent->GetComponent<TransformComponent>();
			if (transform)
			{
				m_WorldPos = transform->GetWorldPosition() + m_LocalPos;
			}
		}
		m_PosIsDirty = false;
	}
}

void dae::TransformComponent::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPos = pos;
	SetPositionDirty();
}
