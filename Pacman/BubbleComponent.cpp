#include "BubbleComponent.h"
#include <SDL_stdinc.h>

#include "AvatarComponent.h"
#include "ColliderComponent.h"
#include "EnemyComponent.h"
#include "Food.h"
#include "GTime.h"
#include "Transform.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Maita.h"
#include "PhysicsComponent.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "SpriteComponent.h"
#include "ZenChan.h"
#include "ZenChanComponent.h"

float BubbleComponent::m_SpriteScale{ 4 };
dae::SpritePreset BubbleComponent::m_GreenZenChan{ false, 9, 4, 0.3f, 0, 4 };
dae::SpritePreset BubbleComponent::m_BlueZenChan{ false, 9, 4, 0.3f, 4, 8 };
dae::SpritePreset BubbleComponent::m_GreenMaita{ false, 9, 4, 0.3f, 8, 12 };
dae::SpritePreset BubbleComponent::m_BlueMaita{ false, 9, 4, 0.3f, 12, 16 };
dae::SpritePreset BubbleComponent::m_Pop{ true, 9, 4, 0.15f, 24, 26 };
dae::SpritePreset BubbleComponent::m_DeadZenChan{ false, 9, 4, 0.1f, 28, 32 };
dae::SpritePreset BubbleComponent::m_DeadMaita{ false, 9, 4, 0.1f, 32, 36 };

void BubbleComponent::Initialize()
{
	dae::ColliderComponent* myColl = m_pOwner->GetComponent<dae::ColliderComponent>();
	if (myColl)
	{
		myColl->SetOverlapFunction([this](dae::GameObject* overlappingActor)
			{
				switch (m_CurrentState)
				{
				case BubbleState::Shooting:
				{
					if (m_HasEnemyInside == false)
					{
						EnemyComponent* enemyComp = overlappingActor->GetComponent<EnemyComponent>();
						if (enemyComp)
						{
							PickUpEnemy(overlappingActor);
						}
					}
					break;
				}
				case BubbleState::Hovering:
				case BubbleState::ReachedTop:
				{
					AvatarComponent* avatarComp = overlappingActor->GetComponent<AvatarComponent>();
					dae::ColliderComponent* playerColl = overlappingActor->GetComponent<dae::ColliderComponent>();
					dae::ColliderComponent* myColl = m_pOwner->GetComponent<dae::ColliderComponent>();
					if (avatarComp && playerColl && myColl)
					{
						if (myColl->IsOverlappingWithDirectional(playerColl).first == dae::ColliderComponent::OverlapData::Top
							&& dae::InputManager::GetInstance().IsKeyboardKeyDown('w'))
						{
							dae::PhysicsComponent* playerPhysics = overlappingActor->GetComponent<dae::PhysicsComponent>(); \
								playerPhysics->SetGrounded(true);
						}
						else
							Pop(true);
					}
					break;
				}
				default:
					break;
				}
			});
	}
}

void BubbleComponent::Update()
{
	float deltaTime = dae::GTime::GetInstance().GetDeltaTime();
	m_Timer += deltaTime;

	dae::Transform* pTransform{ m_pOwner->GetTransform() };
	const glm::vec2 currPos = pTransform->GetWorldPosition();

	glm::vec2 posDelta{};

	switch (m_CurrentState)
	{
	case BubbleState::Shooting:
	{
		constexpr float horMoveSpeed{ 450 };
		posDelta.x = (m_DirectionRight ? horMoveSpeed * deltaTime : -horMoveSpeed * deltaTime);

		if (currPos.x <= 70 || currPos.x >= 890)
		{
			posDelta.x = 0;
			m_Timer = 1.f;
		}

		if (m_Timer >= 0.5f)
		{
			m_CurrentState = BubbleState::Hovering;
		}

		break;
	}
	case BubbleState::Hovering:
	{
		constexpr float vertMoveSpeed{ 100 };
		posDelta.y = -vertMoveSpeed * deltaTime;

		if (currPos.y <= 70)
		{
			m_CurrentState = BubbleState::ReachedTop;
			posDelta.y = 0;
			m_Timer = 0.f;
		}

		break;
	}
	case BubbleState::ReachedTop:
	{
		if (m_Timer >= 3.f)
		{
			if (m_HasEnemyInside)
			{
				if (m_ZenChan)
					ZenChan::CreateZenChan(dae::SceneManager::GetInstance().GetCurrentScene(),
						m_pOwner->GetTransform()->GetWorldPosition());
				else
					Maita::CreateMaita(dae::SceneManager::GetInstance().GetCurrentScene(),
						m_pOwner->GetTransform()->GetWorldPosition());
			}

			Pop(false);
		}
		break;
	}
	case BubbleState::Popping:
	{
		auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
		if (spriteComp)
			if (spriteComp->IsDoingOnce() == false)
				m_pOwner->MarkForDelete();
		break;
	}
	case BubbleState::EnemyDying:
	{
		if (abs(currPos.x - m_RandomGoToPos.x) <= 1.f && abs(currPos.y - m_RandomGoToPos.y) <= 1.f)
		{
			auto scene = dae::SceneManager::GetInstance().GetCurrentScene();
			if (m_ZenChan)
				Food::CreateFood(scene, m_pOwner, FoodComponent::FoodType::Melon);
			else
				Food::CreateFood(scene, m_pOwner, FoodComponent::FoodType::Fries);
			m_pOwner->MarkForDelete();
		}

		if (abs(currPos.x - m_RandomGoToPos.x) <= 1.f == false)
			posDelta.x = m_RandomGoToPos.x - currPos.x < 0 ? -1.f : 1.f;
		if (abs(currPos.y - m_RandomGoToPos.y) <= 1.f == false)
			posDelta.y = m_RandomGoToPos.y - currPos.y < 0 ? -1.f : 1.f;

		posDelta *= 250 * deltaTime;

		break;
	}
	}

	pTransform->Translate(posDelta);

}

void BubbleComponent::SetShootDirection(bool right)
{
	m_DirectionRight = right;
}

BubbleComponent::BubbleState BubbleComponent::GetState() const
{
	return m_CurrentState;
}

bool BubbleComponent::HasEnemyInside() const
{
	return m_HasEnemyInside;
}

void BubbleComponent::PickUpEnemy(dae::GameObject* go)
{
	m_HasEnemyInside = true;

	m_ZenChan = go->GetComponent<ZenChanComponent>();

	go->MarkForDelete();
	dae::SpriteComponent* spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (spriteComp)
	{
		if (m_Blue)
		{
			if (m_ZenChan)
				spriteComp->SetAnimVariables(m_BlueZenChan);
			else
				spriteComp->SetAnimVariables(m_BlueMaita);
		}
		else
		{
			if (m_ZenChan)
				spriteComp->SetAnimVariables(m_GreenZenChan);
			else
				spriteComp->SetAnimVariables(m_GreenMaita);
		}
		spriteComp->Scale(m_SpriteScale);
	}
}

void BubbleComponent::Pop(bool byPlayer)
{
	auto spriteComp = m_pOwner->GetComponent<dae::SpriteComponent>();
	if (m_HasEnemyInside && byPlayer)
	{
		m_CurrentState = BubbleState::EnemyDying;
		dae::ServiceLocator::GetSoundSystem().PlaySound("../Data/Sound/PopBubbleWithEnemy.wav", 100, 0);

		if (spriteComp)
		{
			if (m_ZenChan)
				spriteComp->SetAnimVariables(m_DeadZenChan);
			else
				spriteComp->SetAnimVariables(m_DeadMaita);
			spriteComp->Scale(m_SpriteScale);
			m_Timer = 0.f;
			m_RandomGoToPos = glm::vec2{ 100 + rand() % 600, 100 + rand() % 600 };
		}
	}
	else
	{
		m_CurrentState = BubbleState::Popping;
		if (spriteComp)
			spriteComp->SetAnimVariables(m_Pop);
	}
}

void BubbleComponent::SetBlue(bool value)
{
	m_Blue = value;
}
