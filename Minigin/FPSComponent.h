#pragma once
#include "Component.h"
#include "GameObject.h"

namespace dae
{
	class TextComponent;

	class FPSComponent final : public Component
	{
	public:
		FPSComponent(std::shared_ptr<GameObject> pOwner);
		virtual ~FPSComponent() override;

		uint32_t GetFPS() const;
		void Update() override;
		void FixedUpdate() override;
	private:
		float m_ElapsedSec{};
		uint32_t m_FPS{};
		float m_UpdateTimer{};
		const float m_UpdateInterval{ 0.5f };
		TextComponent* m_pText = nullptr;
	};
}


