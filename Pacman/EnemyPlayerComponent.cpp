#include "EnemyPlayerComponent.h"

#include "BubbleComponent.h"
#include "ColliderComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "Rock.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "SpriteComponent.h"
#include "GTime.h"

float EnemyPlayerComponent::m_SpriteScale{ 4 };
dae::SpritePreset EnemyPlayerComponent::m_Damaged{ false, 4, 8, 0.1f, 24, 28 };
dae::SpritePreset EnemyPlayerComponent::m_Walking{ false, 4, 8, 0.3f, 8, 13 };
dae::SpritePreset EnemyPlayerComponent::m_ThrowBoulder{ false, 4, 4, 0.2f, 7, 12 };

void EnemyPlayerComponent::Initialize()
{
	//Set up enemy hit detection
	dae::ColliderComponent* myColl = m_pOwner->GetComponent<dae::ColliderComponent>();
	if (myColl)
	{
		myColl->SetOverlapFunction([this](dae::GameObject* overlappingActor)
			{
				//if the player isnt invulnerable
				if (m_Invulnerable == false && m_CurrentState == EnemyPlayerState::Moving)
				{
					//if its a bubble
					BubbleComponent* bubbleComp = overlappingActor->GetComponent<BubbleComponent>();
					if (bubbleComp && bubbleComp->GetState() == BubbleComponent::BubbleState::Shooting)
					{
						bubbleComp->Pop(false);
						{
							m_CurrentState = EnemyPlayerState::Hit;
							dae::ServiceLocator::GetSoundSystem().PlaySound("../Data/Sound/Damaged.wav", 100, 0);
							dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
							if (spriteComp)
							{
								spriteComp->SetAnimVariables(m_Damaged);
								spriteComp->Scale(m_SpriteScale);
								spriteComp->Pause(false);
							}
						}
					}
					else if (bubbleComp && (bubbleComp->GetState() == BubbleComponent::BubbleState::Hovering || bubbleComp->GetState() == BubbleComponent::BubbleState::ReachedTop))
					{
						bubbleComp->Pop(false);
					}
				}
			});
	}
}

void EnemyPlayerComponent::Update()
{
	switch (m_CurrentState)
	{
	case EnemyPlayerState::Moving:
	{
		UpdateAnimVariablesMoving();

		float elapsedSec = dae::GTime::GetInstance().GetDeltaTime();

		//If they are invulnerable, count down
		if (m_Invulnerable)
		{
			m_Timer += elapsedSec;

			if (m_Timer >= m_MaxInvulnerableTime)
			{
				m_Timer = 0.f;
				m_Invulnerable = false;
			}
		}

		auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
		spriteComp->SetRenderOffset(glm::vec2{ 0, 0 });
		if (m_Throwing)
		{

			m_RockThrowingTimer += elapsedSec;

			if (m_RockThrowingTimer >= 0.2f * 3.9f)
			{
				Rock::CreateRock(dae::SceneManager::GetInstance().GetCurrentScene(), m_pOwner, m_pOwner->GetTransform()->GetIsFacingRight());
				spriteComp->SetAnimVariables(m_Walking);
				spriteComp->Scale(m_SpriteScale);
				m_Throwing = false;
				m_RockThrowingTimer = 0.f;
				break;
			}

			//Do sprite offset
			if (m_pOwner->GetTransform()->GetIsFacingRight() == false)
				spriteComp->SetRenderOffset(glm::vec2{ -spriteComp->GetSize().x / 2, 0 });

		}
		break;
	}
	case EnemyPlayerState::Hit:
	{
		DoRespawnLogic();

		auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
		spriteComp->SetRenderOffset(glm::vec2(0, 0));
		break;
	}
	}
}

void EnemyPlayerComponent::ThrowRock()
{
	if (m_CurrentState == EnemyPlayerState::Moving)
	{
		auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
		spriteComp->SetAnimVariables(m_ThrowBoulder);
		m_RockThrowingTimer = 0.f;
		spriteComp->Scale(m_SpriteScale);
		m_Throwing = true;

	}
}

EnemyPlayerComponent::EnemyPlayerState EnemyPlayerComponent::GetCurrState() const
{
	return m_CurrentState;
}


void EnemyPlayerComponent::UpdateAnimVariablesMoving()
{
	dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (spriteComp)
	{
		//Check if the sprite should be paused or not depending on if it moved
		dae::Transform* transform = m_pOwner->GetTransform();

		glm::vec2 currPos = transform->GetLocalPosition();

		if (m_LastPos == currPos && m_Throwing == false)
			spriteComp->Pause(true);
		else
		{
			spriteComp->Pause(false);
			//Check if it should be flipped
			if (currPos.x > m_LastPos.x)
			{
				spriteComp->FlipTexture(true);
			}
			else if (currPos.x < m_LastPos.x)
			{
				spriteComp->FlipTexture(false);
			}
		}
		m_LastPos = currPos;


		//If its unvulnerable make it flicker
		if (m_Invulnerable)
		{
			//flicker on and off 3 times per second
			int shouldFlicker = int(m_Timer * 6) % 2;
			spriteComp->ToggleVisuals(shouldFlicker);
		}
	}
}

void EnemyPlayerComponent::DoRespawnLogic()
{
	float elapsedSec = dae::GTime::GetInstance().GetDeltaTime();
	m_Timer += elapsedSec;

	if (m_Timer >= m_MaxRespawmTimer)
	{
		//Respawn
		dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
		if (spriteComp)
		{
			spriteComp->SetAnimVariables(m_Walking);
			spriteComp->Scale(m_SpriteScale);
			spriteComp->Pause(false);
		}


		m_pOwner->GetTransform()->SetWorldPosition(850, 700);

		m_Timer = 0.f;
		m_CurrentState = EnemyPlayerState::Moving;
		m_HealthChange.Notify(-1);

		m_Invulnerable = true;
	}
}
