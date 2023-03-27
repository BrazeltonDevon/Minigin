#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "RenderComponent.h"

dae::TextComponent::TextComponent(GameObject* pOwner, const std::string& text, std::shared_ptr<Font> font, SDL_Color& color) 
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
	if (owner)
	{
		m_pRenderComponent = owner->GetComponent<dae::RenderComponent>();

		if (m_pRenderComponent == nullptr)
		{
			throw std::runtime_error(std::string("Render component missing, text component failed"));
		}
	}
}


void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
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
		if (m_pRenderComponent)
		{
			m_pRenderComponent->SetTexture(std::make_shared<Texture2D>(texture));
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
	m_pRenderComponent->SetPosition(x, y);
}



