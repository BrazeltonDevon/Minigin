#pragma once
#include "Component.h"
#include "Transform.h"
#include <string>

namespace dae
{
	class Texture2D;

	class RenderComponent : public Component
	{
	public:
		RenderComponent() : Component() {};
		RenderComponent(std::shared_ptr<Texture2D>texture);
		RenderComponent(const std::string& filename);

		~RenderComponent() override;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		virtual void SetTexture(const std::string& filename);
		virtual void SetTexture(const std::shared_ptr<Texture2D> tex);

		void SetPosition(float x, float y);
		void SetWidthHeight(float w, float h);
		std::shared_ptr<Texture2D> GetTexture() const { return m_Texture; }

		void Render() const override;
		void Update() override {};
	private:
		std::shared_ptr<Texture2D> m_Texture{};
		float m_Width{};
		float m_Height{};
	};
}
