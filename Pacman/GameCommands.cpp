#include "GameCommands.h"

#include "AvatarComponent.h"
#include "ServiceLocator.h"
#include "PhysicsComponent.h"
#include "EnemyPlayerComponent.h"
#include "SoundSystem.h"
#include "Bubble.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include <iostream>


void JumpCommand::Execute()
{
	AvatarComponent* avatarComp = m_pGo->GetComponent<AvatarComponent>();
	EnemyPlayerComponent* maitaComp = m_pGo->GetComponent<EnemyPlayerComponent>();
	if (avatarComp && avatarComp->GetCurrState() != AvatarComponent::AvatarState::Moving)
		return;
	if (maitaComp && maitaComp->GetCurrState() != EnemyPlayerComponent::EnemyPlayerState::Moving)
		return;

	auto physicsComp = m_pGo->GetComponent<dae::PhysicsComponent>();

	if (physicsComp == nullptr)
		return;

	if (physicsComp->GetCollisionState().BottomCollision)
	{
		physicsComp->Jump(m_Speed);
		dae::ServiceLocator::GetSoundSystem().PlaySound("../Data/Sound/JumpEffect.wav", 100, 0);
	}
}

void MoveLeftCommand::Execute()
{
	AvatarComponent* avatarComp = m_pGo->GetComponent<AvatarComponent>();
	EnemyPlayerComponent* maitaComp = m_pGo->GetComponent<EnemyPlayerComponent>();
	if (avatarComp)
	{
		if (avatarComp->GetCurrState() == AvatarComponent::AvatarState::Moving)
		{
			Move();
		}
	}
	else if (maitaComp)
	{
		if (maitaComp->GetCurrState() == EnemyPlayerComponent::EnemyPlayerState::Moving)
		{
			Move();
		}
	}

}

void MoveLeftCommand::Move()
{
	//Add movespeed and make frame independent movement
	float horMovement = dae::GTime::GetInstance().GetDeltaTime() * m_Speed;

	//Invert x-axis
	horMovement *= -1;

	//Transform GO
	auto transform = m_pGo->GetComponent<dae::Transform>();
	if (transform)
		transform->Translate(horMovement, 0);
}

void MoveRightCommand::Execute()
{
	AvatarComponent* avatarComp = m_pGo->GetComponent<AvatarComponent>();
	EnemyPlayerComponent* maitaComp = m_pGo->GetComponent<EnemyPlayerComponent>();
	if (avatarComp)
	{
		if (avatarComp->GetCurrState() == AvatarComponent::AvatarState::Moving)
		{
			Move();
		}
	}
	else if (maitaComp)
	{
		if (maitaComp->GetCurrState() == EnemyPlayerComponent::EnemyPlayerState::Moving)
		{
			Move();
		}
	}
}

void MoveRightCommand::Move()
{
	//Add movespeed and make frame independent movement
	float horMovement = dae::GTime::GetInstance().GetDeltaTime() * m_Speed;

	//Transform GO
	auto transform = m_pGo->GetComponent<dae::Transform>();
	if (transform)
		transform->Translate(horMovement, 0);
}

void ShootBubbleCommand::Execute()
{
	AvatarComponent* avatarComp = m_pGo->GetComponent<AvatarComponent>();
	dae::SpriteComponent* spriteComp = m_pGo->GetComponent<dae::SpriteComponent>();

	if (avatarComp && spriteComp)
	{
		//Dont shoot if he is already shooting / doing something else
		if (spriteComp->IsDoingOnce())
			return;

		if (avatarComp->GetCurrState() == AvatarComponent::AvatarState::Moving)
		{
			dae::Scene* scene = dae::SceneManager::GetInstance().GetCurrentScene();
			Bubble::CreateBubble(scene, m_pGo);
			dae::ServiceLocator::GetSoundSystem().PlaySound("../Data/Sound/ShootBubbleEffect.wav", 100, 0);


			if (avatarComp->GetColor() == AvatarComponent::AvatarColor::green)
				spriteComp->DoOnceAnim(0.1f, 7, 12);
			else
				spriteComp->DoOnceAnim(0.1f, 28, 33);
		}
	}
}

void ThrowRockCommand::Execute()
{
	EnemyPlayerComponent* maitaComp = m_pGo->GetComponent<EnemyPlayerComponent>();

	float totalGameTime = dae::GTime::GetInstance().GetTotal();

	//Attack cooldonw
	if (maitaComp && totalGameTime - m_LastTimeThrew > 1.5f)
	{
		maitaComp->ThrowRock();
		m_LastTimeThrew = totalGameTime;
	}
}
