#include "ZenChanComponent.h"

#include "EnemyComponent.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "GTime.h"

float ZenChanComponent::m_SpriteScale{ 4 };
dae::SpritePreset ZenChanComponent::m_WalkingPreset{ false, 4, 8, 0.3f, 0, 4 };
dae::SpritePreset ZenChanComponent::m_ChargingPreset{ false, 4, 8, 0.1f, 4, 8 };

ZenChanComponent::ZenChanComponent()
	: m_ChargingTimer{ static_cast<float>(rand() % 20 + 10) }
{
}

void ZenChanComponent::Initialize()
{
	dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (spriteComp)
	{
		spriteComp->SetAnimVariables(m_WalkingPreset);
		spriteComp->Scale(m_SpriteScale);
	}
}

void ZenChanComponent::Update()
{
	float deltaTime = dae::GTime::GetInstance().GetDeltaTime();

	auto enemyComp = m_pOwner->GetComponent<EnemyComponent>();
	if (enemyComp == nullptr)
		return;


	//Charging logic happens independent of state, it is outside of the switch
	m_ChargingTimer -= deltaTime;
	auto spriteComponent = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (m_Charging)
	{
		enemyComp->MultiplyMoveSpeed(2.3f);
		if (m_ChargingTimer < 0.f)
		{
			//stop charging
			m_Charging = false;
			m_ChargingTimer = static_cast<float>(rand() % 10 + 7); //random time between 7-17 sec before charging again
			spriteComponent->SetAnimVariables(m_WalkingPreset);
			spriteComponent->Scale(m_SpriteScale);
		}
	}
	else
	{
		enemyComp->ResetMoveSpeed();
		if (m_ChargingTimer < 0.f)
		{
			//start charging
			m_Charging = true;
			m_ChargingTimer = static_cast<float>(rand() % 5 + 4); //random time between 4-9 sec before stopping
			spriteComponent->SetAnimVariables(m_ChargingPreset);
			spriteComponent->Scale(m_SpriteScale);
		}
	}

}
