#include "ScoreDisplayComponent.h"
#include "AvatarComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <sstream>

void ScoreDisplayComponent::Initialize()
{
	UpdateScoreText();
}

void ScoreDisplayComponent::SetPlayer(AvatarComponent* player)
{
	m_Player = player;
	if (m_Player)
	{
		m_Player->m_FoodPickup.AddObserver(this);
	}
}

int ScoreDisplayComponent::GetScore() const
{
	return m_score;
}

void ScoreDisplayComponent::OnNotify(FoodComponent::FoodType type)
{
	switch (type)
	{
	case FoodComponent::FoodType::Melon:
		m_score += 100;
		break;
	case FoodComponent::FoodType::Fries:
		m_score += 200;
		break;
	}
	UpdateScoreText();
}

void ScoreDisplayComponent::OnSubjectDestroy()
{
	m_Player = nullptr;
}

void ScoreDisplayComponent::UpdateScoreText()
{
	// Get text component if its not there
	if (m_pText == nullptr)
	{
		m_pText = GetOwner()->GetComponent<dae::TextComponent>();

		if (m_pText == nullptr) return;
	}

	// Update text component
	std::stringstream scoreText{};

	scoreText << "Score: ";
	scoreText << m_score;

	m_pText->SetText(scoreText.str());
}

ScoreDisplayComponent::~ScoreDisplayComponent()
{
	if (m_Player)
	{
		m_Player->m_FoodPickup.RemoveObserver(this);
	}
}
