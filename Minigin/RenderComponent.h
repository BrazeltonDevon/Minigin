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
		// Params: std::shared_ptr<GameObject> pOwner, std::shared_ptr<Texture2D> tex
		RenderComponent(GameObject* pOwner);
		~RenderComponent() override;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		virtual void SetTexture(const std::string& filename);
		virtual void SetTexture(const std::shared_ptr<Texture2D> tex) { m_Texture = tex; };
		void SetPosition(float x, float y);

		void Render() const override;
		void Update() override;

	protected:
		dae::Transform m_Transform{};
		std::shared_ptr<Texture2D> m_Texture{};
		bool m_NeedsUpdate{ false };
		std::string m_filePath{};
	};
}
