#include "LivesDisplayComponent.h"
#include "TextComponent.h"
#include "PlayerComponent.h"

dae::LivesDisplayComponent::LivesDisplayComponent()
	: Component(), pTextComponent{ GetOwner()->GetComponent<dae::TextComponent>()}, m_Text{ "Lives: " }
{
}

dae::LivesDisplayComponent::~LivesDisplayComponent()
{

}


void dae::LivesDisplayComponent::Update()
{
}

void dae::LivesDisplayComponent::Render() const
{
}


void dae::LivesDisplayComponent::OnNotify(Event event, GameObject* go)
{
	switch (event)
	{
	case dae::Event::PlayerStart:
		m_Text = "LIVES: " + std::to_string(go->GetComponent<dae::PlayerComponent>()->GetLives());
		pTextComponent->SetText(m_Text);
		break;
	case dae::Event::PlayerDied:
		m_Text = "LIVES: " + std::to_string(go->GetComponent<dae::PlayerComponent>()->GetLives());
		pTextComponent->SetText(m_Text);
		break;
	default:
		break;
	}
}
