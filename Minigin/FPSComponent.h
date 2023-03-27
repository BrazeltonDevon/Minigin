#pragma once
#include "Component.h"
#include "Transform.h"
#include <memory>
#include <string>

namespace dae
{
	class GameObject;
	class TextComponent;

	class FPSComponent final : public Component
	{
	public:
		FPSComponent(GameObject* object);
		void Init();
		void Render() const override;
		void Update() override;
	private:
		bool m_NeedsUpdate;
		int m_FPSCount{};
		float m_AccumulatedTime{};
		float sec{ 1.0f };
		std::string m_FPSValue{ "0 FPS" };
		TextComponent* m_TextRenderComp{ nullptr };
	};
}


