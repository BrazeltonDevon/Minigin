#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae {
	class GameObject;
	class TextComponent;

	class ScoreDisplayComponent final : public  Component, public Observer
	{
	public:
		ScoreDisplayComponent(dae::GameObject* go);

		~ScoreDisplayComponent();

		ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& other) noexcept = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const override;
		void OnNotify(Event event, GameObject* go) override;

	private:
		TextComponent* pTextComponent;
		std::string m_Text;
	};

}