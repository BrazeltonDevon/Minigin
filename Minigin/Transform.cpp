#include "Transform.h"
#include <algorithm>
#include "GameObject.h"

dae::Transform::Transform(GameObject* gameObject) : Component(gameObject)
{
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	if (m_IsPosDirty)
	{
		UpdateWorldPosition();
	}
	return m_WorldPos;
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPos = pos;
	SetPositionDirty(true);
}

void dae::Transform::SetLocalPosition(float x, float y, float z)
{
	m_LocalPos.x = x;
	m_LocalPos.y = y;
	m_LocalPos.z = z;

	SetPositionDirty(true);
}

const glm::vec3& dae::Transform::GetLocalPosition() const
{
	return m_LocalPos;
}

void dae::Transform::SetPositionDirty(bool val)
{
	m_IsPosDirty = val;
}

void dae::Transform::UpdateWorldPosition()
{
	if (m_IsPosDirty)
	{
		auto owner = GetOwner();
		if (owner == nullptr)
		{
			return;
		}
		auto parent{ owner->GetParent() };
		if (parent == nullptr)
		{
			m_WorldPos = m_LocalPos;
		}
		else
		{
			auto transform = parent->GetComponent<Transform>();
			if (transform)
			{
				m_WorldPos = transform->GetWorldPosition() + m_LocalPos;
			}
		}

		SetPositionDirty(false);
	}
}

