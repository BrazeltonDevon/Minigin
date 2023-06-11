#include "ScoreDisplayComponent.h"
#include "TextComponent.h"
#include "PlayerComponent.h"

dae::ScoreDisplayComponent::ScoreDisplayComponent(dae::GameObject* go)
	: Component(go), pTextComponent{ GetOwner()->GetComponent<dae::TextComponent>() }, m_Text{ "HIGH SCORE: " }
{
}

dae::ScoreDisplayComponent::~ScoreDisplayComponent()
{

}


void dae::ScoreDisplayComponent::Update()
{
}

void dae::ScoreDisplayComponent::Render() const
{
}


void dae::ScoreDisplayComponent::OnNotify(Event event, GameObject* go)
{
	switch (event)
	{
	case dae::Event::AddPoints:
		m_Text = "HIGH SCORE: " + std::to_string(go->GetComponent<dae::PlayerComponent>()->GetScore());
		pTextComponent->SetText(m_Text);
		break;
	case dae::Event::PlayerStart:
		m_Text = "HIGH SCORE: " + std::to_string(go->GetComponent<dae::PlayerComponent>()->GetScore());
		pTextComponent->SetText(m_Text);
	default:
		break;
	}
}
