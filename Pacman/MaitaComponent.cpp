#include "MaitaComponent.h"

#include "EnemyComponent.h"
#include "GameObject.h"
#include "Rock.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "GTime.h"

float MaitaComponent::m_SpriteScale{4};
dae::SpritePreset MaitaComponent::m_WalkingPreset{false, 4, 8, 0.3f, 8, 13};
dae::SpritePreset MaitaComponent::m_AttackingPreset{false, 4, 4, 0.2f, 7, 12};

MaitaComponent::MaitaComponent()
	: m_RockThrowingTimer{ static_cast<float>(rand() % 3 + 5) }
{
}

void MaitaComponent::Initialize()
{
	dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (spriteComp)
	{
		spriteComp->SetAnimVariables(m_WalkingPreset);
		spriteComp->Scale(m_SpriteScale);
	}
}

void MaitaComponent::Update()
{
	m_RockThrowingTimer -= dae::GTime::GetInstance().GetDeltaTime();

	auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();

	if (m_RockThrowingTimer < 0.f && spriteComp)
	{
		if (!m_Throwing)
		{
			spriteComp->SetAnimVariables(m_AttackingPreset);
			m_RockThrowingTimer = 0.2f * 3.9f;
		}
		else
		{
			Rock::CreateRock(dae::SceneManager::GetInstance().GetCurrentScene(), m_pOwner, m_pOwner->GetComponent<EnemyComponent>()->GetMoveRight());
			spriteComp->SetAnimVariables(m_WalkingPreset);
			m_RockThrowingTimer = static_cast<float>(rand() % 3 + 5);
		}
		spriteComp->Scale(m_SpriteScale);

		m_Throwing = !m_Throwing;
	}

	//Do sprite offset
	spriteComp->SetRenderOffset(glm::vec2{ 0, 0 });
	if (m_Throwing)
	{
		if (m_pOwner->GetComponent<EnemyComponent>()->GetMoveRight() == false)
			spriteComp->SetRenderOffset(glm::vec2{ -spriteComp->GetSize().x / 2, 0 });
	}
}