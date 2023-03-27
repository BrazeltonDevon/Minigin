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
		//RenderComponent(std::shared_ptr<GameObject> pOwner);
		//RenderComponent(std::shared_ptr<GameObject> pOwner, std::shared_ptr<Texture2D>texture);
		//RenderComponent(std::shared_ptr<GameObject> pOwner, const std::string& filename);

		RenderComponent(GameObject* pOwner) : Component(pOwner) {};
		RenderComponent(GameObject* pOwner, std::shared_ptr<Texture2D>texture);
		RenderComponent(GameObject* pOwner, const std::string& filename);

		~RenderComponent() override;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		virtual void SetTexture(const std::string& filename);
		virtual void SetTexture(const std::shared_ptr<Texture2D> tex) { m_Texture = tex; };
		void SetPosition(float x, float y);
		std::shared_ptr<Texture2D> GetTexture() const { return m_Texture; }
		void Render() const override;
		void Update() override {};

	protected:
		std::shared_ptr<Texture2D> m_Texture{};
	};
}
