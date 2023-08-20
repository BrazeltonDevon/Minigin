#pragma once
#include "FoodComponent.h"
#include "Subject.h"

namespace dae
{
	class TextComponent;
}

class AvatarComponent;

class ScoreDisplayComponent final : public dae::Component, public dae::Observer<FoodComponent::FoodType>
{
public:
	ScoreDisplayComponent() = default;
	~ScoreDisplayComponent() override;

	ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
	ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

	void Initialize() override;
	void SetPlayer(AvatarComponent* player);

	int GetScore() const;

private:

	void OnNotify(FoodComponent::FoodType type) override;
	void OnSubjectDestroy() override;
	void UpdateScoreText();

	int m_score{};
	AvatarComponent* m_Player{};

	dae::TextComponent* m_pText{};
};

