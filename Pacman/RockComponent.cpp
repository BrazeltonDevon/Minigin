#include "RockComponent.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "GTime.h"

float RockComponent::m_SpriteScale{ 4 };
dae::SpritePreset RockComponent::m_CrashAnim{ false, 2, 4, 0.2f, 4, 7 };

void RockComponent::Initialize()
{
	m_HorMoveSpeed = 300.f;
	m_CurrState = RockState::Rolling;
}

void RockComponent::Update()
{
	float elapsedSec = dae::GTime::GetInstance().GetDeltaTime();
	auto physComp = m_pOwner->GetComponent<dae::PhysicsComponent>();
	auto collisionData = physComp->GetCollisionState();

	switch (m_CurrState)
	{
	case RockState::Rolling:
	{

		//break if it hits wall
		if (collisionData.LeftCollision || collisionData.RightCollision)
		{
			Crash();
			break;
		}

		//set horizontal movespeed
		int moveDir = m_MoveRight ? 1 : -1;
		m_pOwner->GetTransform()->Translate(static_cast<float>(moveDir) * m_HorMoveSpeed * elapsedSec, 0);
		break;
	}
	case RockState::Crashing:
	{
		m_CrashingTimer += elapsedSec;
		if (m_CrashingTimer > m_CrashAnim.AnimTimer * 3 - 0.01f)
		{
			m_pOwner->MarkForDelete();
		}
		break;
	}
	}

}

void RockComponent::SetMoveRight(bool right)
{
	m_MoveRight = right;
}

void RockComponent::Crash()
{
	m_CurrState = RockState::Crashing;
	auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	spriteComp->SetAnimVariables(m_CrashAnim);
	spriteComp->Scale(m_SpriteScale);
}

bool RockComponent::CanDamage() const
{
	return m_CurrState == RockState::Rolling;
}
