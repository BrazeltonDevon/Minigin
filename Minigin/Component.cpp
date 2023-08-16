#include "Component.h"
#include "GameObject.h"


void dae::Component::SetOwner(GameObject* pParent)
{
	m_pOwner = pParent;
}

dae::GameObject* dae::Component::GetOwner() const
{
	return m_pOwner;
}