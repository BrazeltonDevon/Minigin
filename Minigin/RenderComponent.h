#pragma once
#include <memory>
#include <glm/vec2.hpp>

#include "Component.h"

namespace dae
{
	class Texture2D;

	class RenderComponent final : public Component
	{
	public:
		RenderComponent() = default;
		~RenderComponent() override = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void SetTexture(const std::shared_ptr<Texture2D>& pTexture);

		void Render() const override;

		glm::vec2 GetTextureSize() const;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};

	};
}
