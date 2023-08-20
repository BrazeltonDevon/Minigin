#pragma once
#include <glm/vec2.hpp>

#include "FoodComponent.h"
#include "Subject.h"
#include "SpritePreset.h"

class EnemyPlayerComponent final : public dae::Component
{
public:
	enum class EnemyPlayerState
	{
		Moving,
		Hit
	};

	EnemyPlayerComponent() = default;
	~EnemyPlayerComponent() override = default;

	EnemyPlayerComponent(const EnemyPlayerComponent& other) = delete;
	EnemyPlayerComponent(EnemyPlayerComponent&& other) = delete;
	EnemyPlayerComponent& operator=(const EnemyPlayerComponent& other) = delete;
	EnemyPlayerComponent& operator=(EnemyPlayerComponent&& other) = delete;

	void Initialize() override;
	void Update() override;

	void ThrowRock();

	EnemyPlayerState GetCurrState() const;

	dae::Subject<int> m_HealthChange;
private:
	void UpdateAnimVariablesMoving();
	void DoRespawnLogic();

	EnemyPlayerState m_CurrentState{ EnemyPlayerState::Moving };

	glm::vec2 m_LastPos{};

	float m_Timer{};

	float m_MaxRespawmTimer{ 3.f };

	//using a bool for this state since it can be active in multiple states
	bool m_Invulnerable{};
	float m_MaxInvulnerableTime{ 3.f };

	bool m_Throwing{};
	float m_RockThrowingTimer{};


	static float m_SpriteScale;
	static dae::SpritePreset m_Damaged;
	static dae::SpritePreset m_Walking;
	static dae::SpritePreset m_ThrowBoulder;
};


