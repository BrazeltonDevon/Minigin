//#pragma once
//#include "Component.h"
//#include "Observer.h"
//
//namespace dae {
//	class GameObject;
//	class TextComponent;
//
//	class LivesDisplayComponent final : public  Component, public Observer<int>
//	{
//	public:
//		LivesDisplayComponent();
//
//		~LivesDisplayComponent();
//
//		LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
//		LivesDisplayComponent(LivesDisplayComponent&& other) noexcept = delete;
//		LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
//		LivesDisplayComponent& operator=(LivesDisplayComponent&& other) noexcept = delete;
//
//		void Update() override;
//		void Render() const override;
//		void OnNotify(int Event) override;
//
//	private:
//		TextComponent* pTextComponent;
//		std::string m_Text;
//	};
//
//}

#pragma once
#include "FoodComponent.h"
#include "Subject.h"

namespace dae
{
	class TextComponent;
}

class AvatarComponent;

class HealthDisplay final : public dae::Component, public dae::Observer<int>
{
public:
	HealthDisplay() = default;
	~HealthDisplay() override;

	HealthDisplay(const HealthDisplay& other) = delete;
	HealthDisplay(HealthDisplay&& other) = delete;
	HealthDisplay& operator=(const HealthDisplay& other) = delete;
	HealthDisplay& operator=(HealthDisplay&& other) = delete;

	void Initialize() override;
	void SetSubject(dae::Subject<int>* healthSubj);

	int GetHP() const;

private:

	void HandleEvent(int healthDelta) override;
	void OnSubjectDestroy() override;
	void UpdateText();

	int m_HP{};
	dae::Subject<int>* m_pSubject{};

	dae::TextComponent* m_pText{};
};

