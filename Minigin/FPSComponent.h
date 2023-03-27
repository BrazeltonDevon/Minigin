#pragma once
#include "Component.h"
#include "Transform.h"
#include <memory>
#include <string>

namespace dae
{
	class GameObject;
	class TextComponent;
	//class 2DTexture;

	class FPSComponent final : public Component
	{
	public:
		FPSComponent(GameObject* pOwner);
		virtual ~FPSComponent() override;

		uint32_t GetFPS() const;
		void Update() override;
	private:
		float m_ElapsedSec{};
		uint32_t m_FPS{};
		//std::string m_FPSValue{ "0" };

		float m_AccumulatedTime{0.1f};
		float m_Seconds{ 0.1f };

		float m_UpdateTimer{};
		const float m_UpdateInterval{ 0.5f };
		TextComponent* m_pText = nullptr;
		bool m_NeedsUpdate{};
	};
}


