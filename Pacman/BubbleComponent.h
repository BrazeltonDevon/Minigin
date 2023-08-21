#pragma once
#include <glm/vec2.hpp>

#include "Component.h"
#include "SpritePreset.h"

class BubbleComponent final : public dae::Component
{
public:
	enum class BubbleState
	{
		Shooting,
		Hovering,
		ReachedTop,
		Popping,
		EnemyDying
	};

	BubbleComponent() = default;
	~BubbleComponent() override = default;

	BubbleComponent(const BubbleComponent& other) = delete;
	BubbleComponent(BubbleComponent&& other) = delete;
	BubbleComponent& operator=(const BubbleComponent& other) = delete;
	BubbleComponent& operator=(BubbleComponent&& other) = delete;

	void Initialize() override;
	void Update() override;
	void SetShootDirection(bool right);

	BubbleState GetState() const;
	bool HasEnemyInside() const;

	void Pop(bool byPlayer);

	void SetBlue(bool value);


private:
	BubbleState m_CurrentState{ BubbleState::Shooting };

	void PickUpEnemy(dae::GameObject* go);

	float m_Timer{};
	bool m_DirectionRight{};
	bool m_HasEnemyInside{};
	bool m_ZenChan{ true };

	glm::vec2 m_RandomGoToPos{};

	bool m_Blue{ false };

	static float m_SpriteScale;
	static dae::SpritePreset m_GreenZenChan;
	static dae::SpritePreset m_BlueZenChan;
	static dae::SpritePreset m_GreenMaita;
	static dae::SpritePreset m_BlueMaita;
	static dae::SpritePreset m_GreenHover;
	static dae::SpritePreset m_BlueHover;
	static dae::SpritePreset m_Pop;
	static dae::SpritePreset m_DeadZenChan;
	static dae::SpritePreset m_DeadMaita;
};
