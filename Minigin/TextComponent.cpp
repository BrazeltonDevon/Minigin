#include <stdexcept>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "RenderComponent.h"

dae::TextComponent::TextComponent(std::shared_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> font, SDL_Color& color) 
	: Component(pOwner),
	m_NeedsUpdate(true),
	m_Text(text),
	m_Font(std::move(font)),
	m_Color(color)
{

}

void dae::TextComponent::Init()
{
	auto owner = GetOwner();
	if (owner.expired())
	{
		m_RenderComponent = owner.lock()->GetComponent<dae::RenderComponent>();
	}
}


void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		//const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		if (m_RenderComponent)
		{
			m_RenderComponent->SetTexture(std::make_shared<Texture2D>(texture));
		}

		m_NeedsUpdate = false;
	}

}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetPosition(const float x, const float y)
{
	m_RenderComponent->SetPosition(x, y);
}



