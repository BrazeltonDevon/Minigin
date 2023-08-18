#pragma region _oldcode
//#include "LivesDisplayComponent.h"
//#include "TextComponent.h"
//#include "PlayerComponent.h"
//
//dae::LivesDisplayComponent::LivesDisplayComponent()
//	: Component(), pTextComponent{ GetOwner()->GetComponent<dae::TextComponent>()}, m_Text{ "Lives: " }
//{
//}
//
//dae::LivesDisplayComponent::~LivesDisplayComponent()
//{
//
//}
//
//
//void dae::LivesDisplayComponent::Update()
//{
//}
//
//void dae::LivesDisplayComponent::Render() const
//{
//}
//
//
//void dae::LivesDisplayComponent::OnNotify(Event event, GameObject* go)
//{
//	switch (event)
//	{
//	case dae::Event::PlayerStart:
//		m_Text = "LIVES: " + std::to_string(go->GetComponent<dae::PlayerComponent>()->GetLives());
//		pTextComponent->SetText(m_Text);
//		break;
//	case dae::Event::PlayerDied:
//		m_Text = "LIVES: " + std::to_string(go->GetComponent<dae::PlayerComponent>()->GetLives());
//		pTextComponent->SetText(m_Text);
//		break;
//	default:
//		break;
//	}
//}

#pragma endregion _oldcode

#include "LivesDisplayComponent.h"

#include "AvatarComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include <sstream>

#include "EventQueue.h"

void LivesDisplayComponent::Initialize()
{
	m_HP = 3;
	UpdateText();
}

void LivesDisplayComponent::SetSubject(dae::Subject<int>* healthSubj)
{
	m_pSubject = healthSubj;
	if (m_pSubject)
	{
		m_pSubject->AddObserver(this);
	}
}

int LivesDisplayComponent::GetHP() const
{
	return m_HP;
}

void LivesDisplayComponent::OnNotify(int healthDelta)
{
	m_HP += healthDelta;

	if (m_HP < 0)
		dae::EventQueue::GetInstance().AddEvent(dae::Event{ "PlayerDied" });
	else
		UpdateText();
}

void LivesDisplayComponent::OnSubjectDestroy()
{
	m_pSubject = nullptr;
}

void LivesDisplayComponent::UpdateText()
{

	// Get text component if its not there
	if (m_pText == nullptr)
	{
		m_pText = GetOwner()->GetComponent<dae::TextComponent>();

		if (m_pText == nullptr) return;
	}

	// Update text component
	std::stringstream healthText{};

	healthText << "Lives: ";
	healthText << m_HP;

	m_pText->SetText(healthText.str());
}

LivesDisplayComponent::~LivesDisplayComponent()
{
	if (m_pSubject)
	{
		m_pSubject->RemoveObserver(this);
	}
}
