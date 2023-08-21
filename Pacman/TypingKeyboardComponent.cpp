#include "TypingKeyboardComponent.h"

#include "EventQueue.h"
#include "GameObject.h"
#include "GTime.h"
#include "TextComponent.h"

TypingKeyboardComponent::TypingKeyboardComponent()
{
	dae::EventQueue::GetInstance().AddListener(this);
}

TypingKeyboardComponent::~TypingKeyboardComponent()
{
	dae::EventQueue::GetInstance().RemoveListener(GetID());
}

void TypingKeyboardComponent::OnEvent(const dae::Event& event)
{
	if (event.name.length() == 1)
	{
		if (event.name == std::string("\b"))
		{
			if (!m_TextString.empty())
				m_TextString.pop_back(); 
		}
		else
		{
			if (m_TextString.length() < 10)
				m_TextString.append(event.name);
		}

		if (m_pText == nullptr)
		{
			m_pText = GetOwner()->GetComponent<dae::TextComponent>();

			if (m_pText == nullptr) return;
		}

		m_pText->SetText(m_TextString);
	}
}

const std::string& TypingKeyboardComponent::GetInput() const
{
	return m_TextString;
}
