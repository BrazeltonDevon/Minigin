#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae {
	class GameObject;
	class TextComponent;

	class LivesDisplayComponent final : public  Component, public Observer
	{
	public:
		LivesDisplayComponent(dae::GameObject* go);

		~LivesDisplayComponent();

		LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent(LivesDisplayComponent&& other) noexcept = delete;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
		LivesDisplayComponent& operator=(LivesDisplayComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const override;
		void OnNotify(Event event, GameObject* go) override;

	private:
		TextComponent* pTextComponent;
		std::string m_Text;
	};

}