#pragma once
#include <string>
#include <memory>
#include <SDL_ttf.h>
#include "GameObject.h"
#include "TransformComponent.h"
#include "Component.h"

namespace dae
{
	class Font;
	class RenderComponent;

	class TextComponent final : public Component
	{
	public:
		TextComponent(std::shared_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> font, SDL_Color& color);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update() override;

		void Init();
		void SetText(const std::string& text);
		void SetPosition(float x, float y);
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		RenderComponent* m_RenderComponent{};
		SDL_Color m_Color{255,255,255};
	};
}
