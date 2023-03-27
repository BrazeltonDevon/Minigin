#pragma once
#include <string>
#include <memory>
#include <SDL_ttf.h>
#include "Transform.h"
#include "Component.h"

namespace dae
{
	class Font;
	class RenderComponent;

	class TextComponent final : public Component
	{
	public:
		TextComponent(GameObject* pOwner, const std::string& text, std::shared_ptr<Font> font, SDL_Color& color);

		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update() override;
		void Render() const override {};

		void Init();

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		RenderComponent* m_pRenderComponent{};
		SDL_Color m_Color{255,255,255};
	};
}
