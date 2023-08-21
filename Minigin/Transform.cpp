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

	if (!pParent) return;

	const auto& pChildren{ pParent->GetChildren() };
	for (const auto& pChild : pChildren)
	{
		const auto pTransform{ pChild->GetTransform() };
		if (!pTransform) continue;

		pTransform->SetPositionDirty();
	}
	
}

void dae::Transform::UpdateWorldPosition()
{
	m_IsPosDirty = false;

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

	m_WorldPos = transform->GetWorldPosition() + m_LocalPos;
}

