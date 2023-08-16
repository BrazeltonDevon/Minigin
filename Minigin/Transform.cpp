#include "Transform.h"
#include <algorithm>
#include "GameObject.h"

const glm::vec2& dae::Transform::GetWorldPosition()
{
	if (m_IsPosDirty)
	{
		UpdateWorldPosition();
	}
	return m_WorldPos;
}

void dae::Transform::SetLocalPosition(float x, float y)
{
	if (m_LocalPos.x != x)
	{
		if (m_LocalPos.x < x)
			m_IsFacingRight = true;
		else
			m_IsFacingRight = false;
	}

	m_LocalPos.x = x;
	m_LocalPos.y = y;

	SetPositionDirty();
}

void dae::Transform::SetLocalPosition(const glm::vec2& pos)
{
	SetLocalPosition(pos.x, pos.y);
}

const glm::vec2& dae::Transform::GetLocalPosition() const
{
	return m_LocalPos;
}

void dae::Transform::SetWorldPosition(float x, float y)
{
	const glm::vec2& worldPos{ GetWorldPosition() };

	SetLocalPosition(m_LocalPos.x + (x - worldPos.x),
		m_LocalPos.y + (y - worldPos.y));
}

void dae::Transform::SetWorldPosition(const glm::vec2& pos)
{
	SetWorldPosition(pos.x, pos.y);
}

void dae::Transform::Translate(float x, float y)
{
	SetLocalPosition(m_LocalPos.x + x,
		m_LocalPos.y + y);
}

void dae::Transform::Translate(glm::vec2 vec)
{
	Translate(vec.x, vec.y);
}


bool dae::Transform::GetIsFacingRight() const
{
	return m_IsFacingRight;
}

void dae::Transform::SetPositionDirty()
{
	
	m_IsPosDirty = true;

	const auto pParent{ GetOwner() };

	// if has no parent, no need to enable dirty flag for children
	if (!pParent) return;

	// enable dirty flag of all children if has parent
	const auto& pChildren{ pParent->GetChildren() };
	for (const auto& pChild : pChildren)
	{
		// make sure child has a transform
		const auto pTransform{ pChild->GetTransform() };
		if (!pTransform) continue;

		// if has transform, set dirty flag
		pTransform->SetPositionDirty();
	}
	
}

void dae::Transform::UpdateWorldPosition()
{
	m_IsPosDirty = false;

	// if has no parent or parent has no transform, use local pos for world pos

	auto parent{ GetOwner()->GetParent()};
	if (parent == nullptr)
	{
		m_WorldPos = m_LocalPos;
		return;
	}
	
	auto transform = parent->GetTransform();

	if(transform == nullptr)
	{
		m_WorldPos = m_LocalPos;
		return;
	}
	
	// otherwise use world pos of the parent transform to calculate world position of this object
	// aka world pos of parent transform + this local pos

	m_WorldPos = transform->GetWorldPosition() + m_LocalPos;
}

